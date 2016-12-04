#include "AngleVerification.h"

#include <QVariant>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>

#include "CLogger.h"

AngleVerification::AngleVerification()
{
	ResolutionWidth_ = 960;
}

AngleVerification::~AngleVerification()
{
}

void AngleVerification::setParameters(std::vector<Parameter>parameters)
{
	//Check if the size of the returned paramers is right
	//The order is determined by parameters()
	if (parameters.size() == parametersSize_)
	{
		ResolutionWidth_ = parameters[0].value_.toInt();
	}
}


std::vector<Parameter> AngleVerification::parameters()
{
	std::vector<Parameter>parameters;
	Parameter param;

	//Setup parameter, name will be displayed on gui
	param.setUp("Resolution Width", QVariant(ResolutionWidth_), QMetaType::Int);
	parameters.push_back(param);

	parametersSize_ = parameters.size();

	return parameters;
}

ResultGenerator::ResultMap AngleVerification::results()
{
	ResultGenerator::ResultMap results;
	Parameter param;

	param.setUp("Angle left side", angleLeft_, QMetaType::Double);
	results.insert(ResultGenerator::ResultPair(ResultGenerator::Results::RES_OBJ_ANGLE_LEFT, param));

	param.setUp("Angle right side", angleRight_, QMetaType::Double);
	results.insert(ResultGenerator::ResultPair(ResultGenerator::Results::RES_OBJ_ANGLE_RIGHT, param));

	return results;
}

bool AngleVerification::run(const cv::Mat* img)
{
	bool res = true;

	// Check if img is empty
	if (!img->empty())
	{
		cv::Mat tmp;
		std::vector<std::vector<cv::Point> > contours;

		cv::cvtColor(*img, *processedImg_, cv::COLOR_BGR2GRAY);
		cv::medianBlur(*img, *resImg_, 5);
		cv::Canny(*processedImg_, *processedImg_, 50, 600);	// TODO: Parameter durchreichen, falls genutzt später
		processedImg_->copyTo(tmp);
		cv::findContours(tmp, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

		angleLeft_ = 5.0;
		angleRight_ = 10.0;

		// Draw contour
		if (!contours.empty())
		{
			cv::drawContours(*resImg_, contours, -1, cv::Scalar(0, 255, 0), 2);
		}
		
		LOGGER->Log("Number contours: %d", contours.size());

		for (int i = 0; i < contours.size(); i++)
		{
			LOGGER->Log("Size contour %d: %d", i, contours[i].size());

			for (int j = 0; j < contours[i].size(); j+=3) 
			{
				LOGGER->Log("Contour element: %d %d", contours[i].at(j), contours[i].at(j));
				//cv::circle(*resImg_, contours[i].at(j), 2, cv::Scalar(0, 255, 0), 2, cv::LINE_AA);

				char buffer[64] = { 0 };
				sprintf(buffer, "%d", j);
				cv::putText(*resImg_, buffer, contours[i].at(j), cv::FONT_HERSHEY_SIMPLEX, .6, cv::Scalar(0), 1);
			}
		}

		
		/*cv::Mat mask;
		// change image to gray scale
		cv::cvtColor(*img, *processedImg_, cv::COLOR_BGR2GRAY);
		// blure image
		cv::medianBlur(*img, *resImg_, 5);
		// vector of all detected corners
		std::vector<cv::Point> corners;
		// vector of all detected corners on the left side
		std::vector<cv::Point> cornersleft;
		// vector of all detected corners on the right side
		std::vector<cv::Point> cornersright;
		// detecting 10 best corners, quality level 0.05, min distance 5 pixels, empty mask, block size 3,
		// using harris detection with parameter 0.04
		cv::goodFeaturesToTrack(*processedImg_, corners, 10, 0.05, 5, mask, 3, false, 0.04);

		if (!corners.empty())
		{	// divide verticles for left and right side of the image
			for (size_t i = 0; i < corners.size(); i++)
			{
				// Higlight found corner points in the result image by using green dots
				cv::Vec2i c = corners[i];
				cv::circle(*resImg_, cv::Point(c[0], c[1]), 2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
				if (c[0] < processedImg_->cols / 2)
				{
					cornersleft.push_back(c);
				}
				else
				{
					cornersright.push_back(c);
				}
			}
		}
		else
		{
			res = false;
		}

		int maxX = 0;
		int maxY = 0;
		int max2Y = 0;
		int ix;
		int i2y;
		cv::Vec2i c1, c2;

		// for left side it detect corner with biggest x parameter and a corner with second biggest y parameter 
		for (int i = 0; i < cornersleft.size(); i++)
		{
			c1 = cornersleft[i];
			int x1 = c1[0];
			int y1 = c1[1];
			if (x1 > maxX)
			{
				maxX = x1;
				ix = i;
			}

			if (y1 > maxY)
			{
				maxY = y1;
			}
			else
			{
				if (y1 > max2Y)
				{
					max2Y = y1; i2y = i;
				}
			}
		}

		c1 = cornersleft[ix];
		c2 = cornersleft[i2y];

		// Highlight the lines that are used for the angle calculation by drawing blue lines
		cv::Point2f v1 (c1[0], c1[1]);
		cv::Point2f v2 (c2[0], c2[1]);
		cv::line(*resImg_, v1, v2, cv::Scalar(255, 0, 0), 6);
		// TODO: Draw other line
		
		// calculate angle between two corners from left side, with biggest x and second biggest y 
		angleLeft_ = int(atan((c2[1] - c1[1]) / (c1[0] - c2[0])) * 180.0 / 3.14);

		//TODO: Calculate angle also for other side of object => angle calculation in new helper method?
		angleRight_ = 0.0;*/
	}
	else
	{
		res = false;
	}

	return res;
}

