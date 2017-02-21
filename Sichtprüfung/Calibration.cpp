#include "Calibration.h"
#include "Configs.h"
#include "ConfigurationStorage.h"
#include "Logger.h"

#include <QVariant>
#include <QSize>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

#include <utility>
#include <thread>
#include <typeinfo>

Calibration::Calibration()
{
	numImgs_ = 18;
	numCornersH_ = 9;
	numConrersV_ = 6;
	sizeSquare_ = 3.5;
	boardSize_ = cv::Size(numCornersH_, numConrersV_);
	calibSuccess_ = false;
	calibrationError_ = 100;
}

Calibration::~Calibration()
{

}

void Calibration::setParameters(std::vector<Parameter> parameters)
{
	//Check if the size of the returned paramers is right
	//The order is determined by parameters()
	if (parameters.size() == parametersSize_)
	{
		numImgs_ = parameters[0].value_.toInt();
		numCornersH_ = parameters[1].value_.toInt();
		numConrersV_ = parameters[2].value_.toInt();
		sizeSquare_ = parameters[3].value_.toDouble();
		boardSize_ = cv::Size(numCornersH_, numConrersV_);
	}
}

std::vector<Parameter> Calibration::parameters()
{
	std::vector<Parameter> parameters;
	Parameter param;

	//Setup parameter, name will be displayed on gui
	param.setUp("Number of images", QVariant(numImgs_), QMetaType::Int);
	parameters.push_back(param);
	
	param.setUp("Horizontal Corners", QVariant(numCornersH_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Vertical Corners", QVariant(numConrersV_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Square Size", QVariant(sizeSquare_), QMetaType::Double);	// mm
	parameters.push_back(param);

	parametersSize_ = parameters.size();

	return parameters;
}

ResultGenerator::ResultMap Calibration::results()
{
	ResultGenerator::ResultMap results;
	Parameter param;

	param.setUp("Calibration error", calibrationError_, QMetaType::Double);
	results.insert(ResultGenerator::ResultPair(ResultGenerator::Results::RES_CALIBRATION, param));

	return results;
}

bool Calibration::run(const cv::Mat* img)
{

	bool found = false;		// If a cheesboard pattern could be detected
	int counter = 0;		// The number of used/saved images for calibration
	int pressedKey = 0;		// The key that has been pressed by the user
	
	// Creating two matrices that will contain the calibration results
	std::vector<cv::Mat> rvecs, tvecs;					// Extrinsic parameters (translation and rotation) 
	cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);	// Intrinsic parameters
	
	if (CV_CALIB_FIX_ASPECT_RATIO)
	{
		cameraMatrix.at<double>(0, 0) = 1.0;
	}
	
	// Output matrix with distortion coefficients. Has 4, 5 or 8 values.
	// See: http://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html
	cv::Mat distCoefficients = cv::Mat::zeros(8, 1, CV_64F);
	

	// Configuring the window that will display the certain calibration images
	cv::namedWindow(CALIB_WINDOW_NAME, cv::WINDOW_NORMAL);
	cv::resizeWindow(CALIB_WINDOW_NAME, 600, 500);
	
	
	// Run corner aquisition as long as needed
	// THIS IMPLEMENTATION IS BAD BECAUS OPENCV HANDLES ITS OWN WINDOW--> Different Execution flow
	while (counter < numImgs_)
	{
		if (!img->empty())
		{
			initializeResultImage(img);
			cv::cvtColor(*resImg_, *processedImg_, CV_BGR2GRAY);

			// Find chessboard calibration pattern in current camera frame
			found = cv::findChessboardCorners(*resImg_, boardSize_, corners_, CV_CALIB_CB_ADAPTIVE_THRESH 
						| CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE | CV_CALIB_CB_FILTER_QUADS);

			if (found)
			{
				cv::cornerSubPix(*processedImg_, corners_, cv::Size(5, 5), cv::Size(-1, -1), 
									cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
				cv::drawChessboardCorners(*processedImg_, boardSize_, cv::Mat(corners_), found);
			}


			// Show input image and detected chessboard corners
			cv::imshow(CALIB_WINDOW_NAME, *processedImg_);
			pressedKey = cv::waitKey(0);	// 0 = window should stay open for an infinite
											// amount of time until the user presses a key

			switch (pressedKey)
			{
			case 27:
				// ESC pressed: abort calibration process completely
				imagePoints_.clear();
				counter = INT32_MAX;	// Leave the loop
				break;
			case ' ':
				// Space pressed: store results of current calibration run
				if (!corners_.empty() && found)
				{
					imagePoints_.push_back(corners_);
					counter++;
				}
				break;
			default:
				// Other key pressed: skip current calibration image and try a new one,
				// if number of images not already reached
				break;
			}
		}
	}

	// Calibration loop completed so close calibration window
	cv::destroyWindow(CALIB_WINDOW_NAME);

	// Check if calibration was successfull: Calibration is only successfull if
	// the set amount of images have been recoreded and considered for the calculation
	if (counter == numImgs_)
	{
		calibSuccess_ = true;
	}
	else
	{
		calibSuccess_ = false;
	}
	
	
	// Calculate calibration results if possible
	if (calibSuccess_ && !imagePoints_.empty())
	{
		// Generate 3D points of the corners
		std::vector<std::vector<cv::Point3f> > objectPoints(1);

		for (int i = 0; i < numConrersV_; i++)
		{
			for (int j = 0; j < numCornersH_; j++)
			{
				objectPoints[0].push_back(cv::Point3f((float)j * sizeSquare_, (float)i * sizeSquare_, 0));
			}
		}

		// Realign points so that the following operation can work correctly
		objectPoints.resize(imagePoints_.size(), objectPoints[0]);

		// Calculate the actual calibration results
		calibrationError_ = calibrateCamera(objectPoints, imagePoints_, resImg_->size(), cameraMatrix, 
									distCoefficients, rvecs, tvecs, CV_CALIB_FIX_ASPECT_RATIO | CV_CALIB_FIX_K4 | CV_CALIB_FIX_K5);
		
		LOGGER.log("Calibration error: " + QVariant(calibrationError_).toString());		// Calibration error should be as close to 0 as possible

		// Show undistorted image after calibration
		cv::Mat tmp = resImg_->clone();		// Next line causes an exception otherwise 
		cv::undistort(tmp, *resImg_, cameraMatrix, distCoefficients);	

		std::string path = paths::getExecutablePath() + paths::configFolder + paths::cameraFolder 
								+ filenames::calibrationName + extensions::calibrationExt;

		// Write calibration results to file
		if (!ConfigurationStorage::instance().write(path, "camera_matrix", cameraMatrix))
		{
			LOGGER.log("Can not write K to " + path);
		}

		for (int i = 0; i < tvecs.size(); i++)
		{
			if (!ConfigurationStorage::instance().write(path, "tvec" + std::to_string(i), tvecs[i]))
			{
				LOGGER.log("Can not write tvecs to " + path);
			}
		}

		for (int i = 0; i < rvecs.size(); i++)
		{
			if (!ConfigurationStorage::instance().write(path, "rvec" + std::to_string(i), rvecs[i]))
			{
				LOGGER.log("Can not write rvecs to " + path);
			}
		}

		if (!ConfigurationStorage::instance().write(path, "distortion_coefficients", distCoefficients))
		{
			LOGGER.log("Can not write D to " + path);
		}
		if (!ConfigurationStorage::instance().write(path, "square_size", sizeSquare_))
		{
			LOGGER.log("Can not write square_size to " + path);
		}
		if (!ConfigurationStorage::instance().write(path, "num_hor_corners", numCornersH_))
		{
			LOGGER.log("Can not write num_hor_corners to " + path);
		}
		if (!ConfigurationStorage::instance().write(path, "num_ver_corners", numConrersV_))
		{
			LOGGER.log("Can not write num_ver_corners to " + path);
		}
	}
	else if (imagePoints_.empty())
	{
		LOGGER.log("No image points supplied. Please recalibrate!");
		calibSuccess_ = false;
	}
	else
	{
		LOGGER.log("Calibration canceled!");
	}

	return calibSuccess_;
}

