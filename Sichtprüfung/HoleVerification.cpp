#include "HoleVerification.h"
#include "Logger.h"
#include "Configs.h"

#include <QVariant>
#include <opencv2\imgproc.hpp>

HoleVerification::HoleVerification()
{
	minRadius_ = 20;
	maxRadius_ = 110;
	houghUpperCannyThresh_ = 80;
	centerThresh_ = 40;
	cannyLowerThresh_ = 50;
	cannyUpperThresh_ = 100;
	morphIterations_ = 2;
}

HoleVerification::~HoleVerification()
{
}

void HoleVerification::setParameters(std::vector<Parameter>parameters)
{
	//Check if the size of the returned paramers is right
	//The order is determined by parameters()
	if (parameters.size() == parametersSize_)
	{
		minRadius_ = parameters[0].value_.toInt();
		maxRadius_ = parameters[1].value_.toInt();
		cannyLowerThresh_ = parameters[2].value_.toInt();
		cannyUpperThresh_ = parameters[3].value_.toInt();
		morphIterations_ = parameters[4].value_.toInt();
		houghUpperCannyThresh_ = parameters[5].value_.toDouble();
		centerThresh_ = parameters[6].value_.toDouble();
		centerEqualTolerance_ = parameters[7].value_.toDouble();
	}
}


std::vector<Parameter> HoleVerification::parameters()
{
	std::vector<Parameter>parameters;
	Parameter param;

	//Setup parameter, name will be displayed on gui
	param.setUp("Minimal radius", QVariant(minRadius_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Maximal radius", QVariant(maxRadius_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Canny: Lower Threshold", QVariant(cannyLowerThresh_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Canny: Upper Threshold", QVariant(cannyUpperThresh_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Morph Close Iteration", QVariant(morphIterations_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Hough: Upper Threshold", QVariant(houghUpperCannyThresh_), QMetaType::Double);
	parameters.push_back(param);

	param.setUp("Hough: Center Threshold", QVariant(centerThresh_), QMetaType::Double);
	parameters.push_back(param);

	param.setUp("Object Center tolerance", QVariant(centerEqualTolerance_), QMetaType::Double);
	parameters.push_back(param);

	parametersSize_ = parameters.size();

	return parameters;
}

ResultGenerator::ResultMap HoleVerification::results()
{
	ResultGenerator::ResultMap results;

	for (size_t i = 0; i < circles_.size(); i++)
	{
		QString name = QString("Hole %1").arg(i);
		Parameter param;

		cv::Vec3i circle = circles_[i];
		param.setUp(name + " radius", circle[2], QMetaType::Double);
		results.insert(ResultGenerator::ResultPair(ResultGenerator::Results::RES_CIRCLE_RADIUS, param));

		bool centered = circlesCentered_[i];
		param.setUp(name + " centered", centered, QMetaType::Bool);
		results.insert(ResultGenerator::ResultPair(ResultGenerator::Results::RES_CIRCLE_MIDDLE, param));

		LOGGER.log("Hole " + QString::number(i) + ": radius = " + QString::number(circle[2]) + ", centered = " + centered);
	}

	return results;
}

bool HoleVerification::run(const cv::Mat* img)
{
	bool res = true;

	//Check if img is empty
	if (!img->empty())
	{
		//Found contours
		std::vector<std::vector<cv::Point> > contours;
		//Center of bounding box
		int objectCenterX = 0;
		int objectCenterY = 0;
		//Bounding box of the largest contour
		cv::RotatedRect boundingBox;
		//Image to find contours
		cv::Mat contourTemp;
		//Grayscale image
		cv::Mat gray;

		initializeResultImage(img);
		// blure image
		cv::medianBlur(*img, *processedImg_, 7);
		// change image to gray scale
		cv::cvtColor(*processedImg_, *processedImg_, cv::COLOR_BGR2GRAY);
		//Following operations alter the image and the Hough
		// Transformation should work on the gray image, so copy it
		processedImg_->copyTo(gray);
		//Process image for robust contour detection
		cv::Canny(*processedImg_, *processedImg_, cannyLowerThresh_, cannyUpperThresh_);
		//Close structures
		cv::morphologyEx(*processedImg_, *processedImg_, cv::MORPH_CLOSE, cv::noArray(), cv::Point(-1, -1), morphIterations_);
		//Reinforce the edges to build a contour
		cv::dilate(*processedImg_, *processedImg_, cv::getStructuringElement(cv::MORPH_DILATE, cv::Size(3, 3)));
		//Copy due to alteration through algorithm
		processedImg_->copyTo(contourTemp);
		//Find all contours
		cv::findContours(contourTemp, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

		if (!contours.empty())
		{
			//Area of current contour with maximum area
			int max = 0;
			//Index of current contour with maximum area
			int i_cont = -1;

			//Searching for the contour with the maximum area
			//If contour is closed the value is large
			for (int i = 0; i< contours.size(); i++)
			{
				if (abs(cv::contourArea(contours[i])) > max)
				{
					max = abs(cv::contourArea(contours[i]));
					i_cont = i;
				}
			}

			// Finding a bounding box for the contour with the maximum area and
			// calculating its center point (= center point of object)
			if (i_cont >= 0)
			{
				boundingBox = cv::minAreaRect(contours[i_cont]);

				objectCenterX = boundingBox.center.x;
				objectCenterY = boundingBox.center.y;

				drawContour(contours, i_cont, colors::contourColor);
			}
		}

		//Reduce the are to search for circles
		gray = gray(boundingBox.boundingRect());
		gray.copyTo(*processedImg_);

		// Detect circles in the given image using Hough Transformation
		HoughCircles(gray, circles_, cv::HOUGH_GRADIENT, 1, gray.rows / 4, houghUpperCannyThresh_, centerThresh_, minRadius_, maxRadius_);

		if (!circles_.empty())
		{
			circlesCentered_.clear();
			for (size_t i = 0; i < circles_.size(); i++)
			{
				cv::Vec3i c = circles_[i];
				// Draw detected circle on the image
				drawCircle(cv::Point2f(c[0] + boundingBox.boundingRect().x, c[1] + boundingBox.boundingRect().y), c[2], colors::resultColor);
				// Draw center of the detected circle on the image
				drawPoint(cv::Point2f(c[0] + boundingBox.boundingRect().x, c[1] + boundingBox.boundingRect().y), colors::resultColor);

				// Compare detected object center with center of detected circles:
				// Difference between the object center and the circle center should be <= centerTolerance_,
				// then they're assumed to be equal
				if (abs(c[0] + boundingBox.boundingRect().x - objectCenterX) <= centerEqualTolerance_
					&& abs(c[1] + boundingBox.boundingRect().y - objectCenterY) <= centerEqualTolerance_)
				{
					circlesCentered_.push_back(true);
				}
				else
				{
					circlesCentered_.push_back(false);
				}
			
			}
		}
		else
		{
			res = false;
		}

	}
	else
	{
		res = false;
	}

	return res;
}
