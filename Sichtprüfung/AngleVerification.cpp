#include "AngleVerification.h"
#include <QVariant>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>

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
	param.setUp("Resolution Width", QVariant(ResolutionWidth_), QMetaType::Double);
	parameters.push_back(param);

	parametersSize_ = parameters.size();

	return parameters;
}

ResultGenerator::ResultMap AngleVerification::results()
{
	ResultGenerator::ResultMap results;
	Parameter param;


	return results;
}

bool AngleVerification::run(const cv::Mat* img)
{
	bool res = true;

	//Check if img is empty
	if (!img->empty())
	{
		cv::Mat mask;
		//change image to gray scale
		cv::cvtColor(*img, *processedImg_, cv::COLOR_BGR2GRAY);
		//blure image
		cv::medianBlur(*img, *resImg_, 5);
		//vektor of all detected corners
		std::vector<cv::Point> corners;
		//vektor of all detected corners on the left side
		std::vector<cv::Point> cornersleft;
		//vektor of all detected corners on the right side
		std::vector<cv::Point> cornersright;
		//detecting 10 best corners,quality level 0.05,min distance 5 pixels,empty mask, block size 3, using harris detection with parameter 0.04
		cv::goodFeaturesToTrack(*processedImg_, corners, 10, 0.05, 5, mask, 3, false, 0.04);

		if (!corners.empty())
		{	//divide verticles for left and right side of the image and draw on result image
			for (size_t i = 0; i < corners.size(); i++)
			{
				cv::Vec2i c = corners[i];
				cv::circle(*resImg_, cv::Point(c[0], c[1]), 2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);

				if (c[0] < ResolutionWidth_ / 2)
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
		//for left side it detect corner with biggest x parameter and a corner with second biggest y parameter 
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
		//calculate angle between two corners from left side, with biggest x and second biggest y 
		float angle = int(atan((c2[1] - c1[1]) / (c1[0] - c2[0])) * 180 / 3.14);



	}
	else
	{
		res = false;
	}

	return res;
}

