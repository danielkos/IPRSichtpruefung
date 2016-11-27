#include "HoleParameter.h"
#include <QVariant>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>

HoleParameter::HoleParameter()
{
	minRadius = 30;
	maxRadius = 90;
}

HoleParameter::~HoleParameter()
{
}

void HoleParameter::setParameters(std::vector<Parameter>parameters)
{
	//Check if the size of the returned paramers is right
	//The order is determined by parameters()
	if (parameters.size() == parametersSize_)
	{
		minRadius = parameters[0].value_.toInt();
		maxRadius = parameters[1].value_.toInt();
	}
}


std::vector<Parameter> HoleParameter::parameters()
{
	std::vector<Parameter>parameters;
	Parameter param;
	//Setup parameter, name will be displayed on gui
	param.setUp("Minimal radius", QVariant(minRadius), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Maximal radius", QVariant(maxRadius), QMetaType::Int);
	parameters.push_back(param);

	parametersSize_ = parameters.size();

	return parameters;
}

bool HoleParameter::run(const cv::Mat* img)
{
	bool res = true;

	//Check if img is empty
	if (!img->empty())
	{
		//vektor of 3 elements vektors
		std::vector<cv::Vec3f> circles;
		cv::Mat temp;
		//blure image
		cv::medianBlur(*img, *resImg_, 5);
		//change image to gray scale
		cv::cvtColor(*img, *processedImg_, cv::COLOR_BGR2GRAY);

		processedImg_->copyTo(temp);
		//funktion which detects circles
		HoughCircles(temp, circles, cv::HOUGH_GRADIENT, 1,
			temp.rows / 8, // change this value to detect circles with different distances to each other
			100, 30, minRadius, maxRadius // change the last two parameters
										  // (minradius & maxradius) to detect larger circles (in pixels)
		);

		if (!circles.empty())
		{
			for (size_t i = 0; i < circles.size(); i++)
			{
				cv::Vec3i c = circles[i];
				//draws circle on image
				circle(*resImg_, cv::Point(c[0], c[1]), c[2], cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
				//draw middle of the circle on the image
				circle(*resImg_, cv::Point(c[0], c[1]), 2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
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
