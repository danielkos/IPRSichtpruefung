#include "HoleVerification.h"
#include "CLogger.h"

#include <QVariant>

#include <opencv2\imgproc.hpp>

HoleVerification::HoleVerification()
{
	minRadius_ = 10;
	maxRadius_ = 90;
	clampLow_ = 60;
	clampHigh_ = 200;
	centerTolerance_ = 5.0;
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
		clampLow_ = parameters[2].value_.toInt();
		clampHigh_ = parameters[3].value_.toInt();
		centerTolerance_ = parameters[4].value_.toDouble();
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

	param.setUp("Clamp low", QVariant(clampLow_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Clamp high", QVariant(clampHigh_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Center tolerance", QVariant(centerTolerance_), QMetaType::Double);
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
	
		LOGGER->Log("Hole %d: radius = %d, centered = %d", i, circle[2], centered);
	}
	
	return results;
}

bool HoleVerification::run(const cv::Mat* img)
{
	bool res = true;

	//Check if img is empty
	if (!img->empty())
	{
		cv::Mat contourTemp;
		cv::Mat gray;

		cv::medianBlur(*img, *resImg_, 5);	// blure image
		cv::cvtColor(*resImg_, *processedImg_, cv::COLOR_BGR2GRAY);		// change image to gray scale
		processedImg_->copyTo(gray);		// Following operations alter the image and the Hough
											// Transformation should work on the gray image, so copy it
		
		// Find contour of object and calculate its center point
		std::vector<std::vector<cv::Point> > contours;
		int objectCenterX = 0;
		int objectCenterY = 0;

		inRange(gray, clampLow_, clampHigh_, contourTemp);
		blur(contourTemp, contourTemp, cv::Size(3, 3));
		erode(contourTemp, contourTemp, cv::Mat());
		findContours(contourTemp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

		if (!contours.empty())
		{
			int max = 0;		// area of current contour with maximum area
			int i_cont = -1;	// index of current contour with maximum area

			// Searching the contour with the maximum area
			for (int i = 0; i< contours.size(); i++)
			{
				if (abs(cv::contourArea(cv::Mat(contours[i]))) > max)
				{
					max = abs(cv::contourArea(cv::Mat(contours[i])));
					i_cont = i;
				}
			}

			// Finding a bounding box for the contour with the maximum area and
			// calculating its center point (= center point of object)
			if (i_cont >= 0)
			{
				std::vector<cv::Point> contours_poly;
				approxPolyDP(cv::Mat(contours[i_cont]), contours_poly, 3, true);
				cv::Rect boundRect = cv::boundingRect(cv::Mat(contours_poly));

				objectCenterX = boundRect.x + boundRect.width / 2;
				objectCenterY = boundRect.y + boundRect.height / 2;

				// Drawing the contour
				cv::Scalar colorContour (0, 255, 0);		// Colour for the contour and its corresponding text
				drawContours(*resImg_, contours, i_cont, colorContour, 2);

				// Drawing the center of the contour and printing the center coordinates
				std::stringstream out;
				out << objectCenterX << "x" << objectCenterY;
				putText(*resImg_, out.str(), cv::Point(objectCenterX + 30, objectCenterY + 30), 
						CV_FONT_HERSHEY_COMPLEX, 1, colorContour, 2, 8);
				cv::circle(*resImg_, cv::Point(objectCenterX, objectCenterY), 2, colorContour, 3, cv::LINE_AA);
			}
		}


		// Detect circles in the given image using Hough Transformation
		HoughCircles(gray, circles_, cv::HOUGH_GRADIENT, 1,
			gray.rows / 4, // change this value to detect circles with different distances to each other
			110, 50, minRadius_, maxRadius_ // change the last two parameters
										  // (minradius & maxradius) to detect larger circles (in pixels)
		);

		if (!circles_.empty())
		{			
			for (size_t i = 0; i < circles_.size(); i++)
			{
				cv::Vec3i c = circles_[i];
				cv::Scalar colorCircle (0, 0, 255);
				// Draw detected circle on the image
				cv::circle(*resImg_, cv::Point(c[0], c[1]), c[2], colorCircle, 2, cv::LINE_AA);
				// Draw center of the detected circle on the image
				cv::circle(*resImg_, cv::Point(c[0], c[1]), 2, colorCircle, 3, cv::LINE_AA);
				
				// Compare detected object center with center of detected circles:
				// Difference between the object center and the circle center should be <= centerTolerance_,
				// then they're assumed to be equal
				if (abs(c[0] - objectCenterX) <= centerTolerance_ 
					&& abs(c[1] - objectCenterY) <= centerTolerance_) 
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
