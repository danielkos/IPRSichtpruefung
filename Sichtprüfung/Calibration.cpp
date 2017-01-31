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

Calibration::Calibration()
{
	numImgs_ = 11;
	numCornersH_ = 4;
	numConrersV_ = 5;
	numSquares_ = numCornersH_ * numConrersV_;
	sizeSquare_ = 11;
	boardSize_ = cv::Size(numCornersH_, numConrersV_);
	calibSuccess_ = false;
	
	bool exists;
	bool ret;
	std::string path = paths::getExecutablePath() + paths::configFolder + paths::cameraFolder;
	ret = paths::createDir(path, exists);
	
	if (!ret && exists)
	{
		LOGGER.log("Reusing directory: " + path);
	}
	else if(ret)
	{
		LOGGER.log("Directory: " + path + "  created");
	}
	else if (!ret && !exists)
	{
		LOGGER.log("Unknown error while creating directory: " + path);
	}
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
		numSquares_ = numCornersH_ * numConrersV_;
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
	/*Parameter param;
	QSize size(boundingBox_.size.width, boundingBox_.size.height);

	param.setUp("Pixel ratio", size, QMetaType::QSize);

	//Set a paramter definied for the generator
	results.insert(ResultGenerator::ResultPair(ResultGenerator::Results::RES_CALIBRATION, param));*/

	return results;
}

bool Calibration::run(const cv::Mat* img)
{
	bool found = false;
	int counter = 0;
	int pressedKey = 0;
	std::string inputWindowName = "Input Image";
	std::string calibWindowName = "Input Image";
	std::vector<cv::Point3f> obj;
	std::vector<cv::Mat> rvecs, tvecs;
	cv::Mat K;
	cv::Mat D;
	cv::Mat* input = new cv::Mat();

	//Open default cam
	if (cam_.OpenCamera())
	{
		cam_.AppendParameters();
		//Generate 3D Points of the corners
		for (int i = 0; i < numCornersH_; i++)
		{
			for (int j = 0; j < numConrersV_; j++)
			{
				obj.push_back(cv::Point3f((float)i * sizeSquare_, (float)j * sizeSquare_, 0));
			}
		}

		//Run corner aquisition as long as needed
		while (counter <= numImgs_)
		{
			cam_.AcquireImage();
			//Get image
			cam_.currentImage()->copyTo(*input);

			if (!input->empty())
			{
				initializeResultImage(input);
				cv::cvtColor(*resImg_, *processedImg_, CV_BGR2GRAY);

				//Find chessboard
				found = cv::findChessboardCorners(*resImg_, boardSize_, corners_, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

				if (found)
				{
					cv::cornerSubPix(*processedImg_, corners_, cv::Size(5, 5), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
					cv::drawChessboardCorners(*processedImg_, boardSize_, corners_, found);
				}

				//Show input img and chessboard corners
				cv::namedWindow(inputWindowName, cv::WINDOW_NORMAL);
				cv::namedWindow(calibWindowName, cv::WINDOW_NORMAL);
				cv::resizeWindow(inputWindowName, 600, 500);
				cv::resizeWindow(calibWindowName, 600, 500);
				cv::imshow(inputWindowName, *resImg_);
				cv::imshow(calibWindowName, *processedImg_);
				//Wait for input
				pressedKey = cv::waitKey(1);

				//ESC-> abort, Space-> store this run, Else-> skip run
				if (found)
				{
					switch (pressedKey)
					{
					case 27:
						calibSuccess_ = false;
						break;
					case ' ':
						imagePoints_.push_back(corners_);
						objectPoints_.push_back(obj);
						counter++;
						break;
					default:
						break;
					}
				}
			}
			else
			{
				calibSuccess_ = false;
			}

			if (!calibSuccess_)
			{
				break;
			}
		}
	}
	
	//Calibrate if possible
	if (calibSuccess_ && !imagePoints_.empty())
	{
		calibrateCamera(objectPoints_, imagePoints_, resImg_->size(), K, D, rvecs, tvecs);

		cv::undistort(*resImg_, *resImg_, K, D);

		std::string path = paths::getExecutablePath() + paths::configFolder + paths::profilesFolder + typeid(Calibration).name() + extensions::calibrationExt;

		//Write results
		if (!ConfigurationStorage::instance().write(path, "K", K))
		{
			LOGGER.log("Can not write K to " + path);
		}
		if (!ConfigurationStorage::instance().write(path, "D", D))
		{
			LOGGER.log("Can not write D to " + path);
		}
		if (!ConfigurationStorage::instance().write(path, "square_size", sizeSquare_))
		{
			LOGGER.log("Can not write square_size to " + path);
		}
		if (ConfigurationStorage::instance().write(path, "num_hor_corners", numCornersH_))
		{
			LOGGER.log("Can not write num_hor_corners to " + path);
		}
		if (!ConfigurationStorage::instance().write(path, "num_ver_corners", numConrersV_))
		{
			LOGGER.log("Can not write num_ver_corners to " + path);
		}
		ConfigurationStorage::instance().realease();
	}

	return calibSuccess_;
}
