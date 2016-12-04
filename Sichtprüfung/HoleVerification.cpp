#include "HoleVerification.h"
#include "CLogger.h"

#include <QVariant>

#include <opencv2\imgproc.hpp>

HoleVerification::HoleVerification()
{
	minRadius_ = 20;
	maxRadius_ = 90;
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

	parametersSize_ = parameters.size();

	return parameters;
}

ResultGenerator::ResultMap HoleVerification::results()
{
	ResultGenerator::ResultMap results;
	Parameter param;

	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Vec3i circle = circles[i];
		param.setUp("Hole radius", circle[2], QMetaType::Double);

		// TODO: Bool zurückgeben ob entdeckter Kreis in der Mitte
		// des Objektes liegt
	}

	results.insert(ResultGenerator::ResultPair(ResultGenerator::Results::RES_CIRCLE_RADIUS, param));
	//results.insert(ResultGenerator::ResultPair(ResultGenerator::Results::RES_CIRCLE_MIDDLE, param));

	return results;
}

bool HoleVerification::run(const cv::Mat* img)
{
	bool res = true;

	//Check if img is empty
	if (!img->empty())
	{
		cv::Mat temp;
		
		// blure image
		cv::medianBlur(*img, *resImg_, 5);
		// change image to gray scale
		cv::cvtColor(*img, *processedImg_, cv::COLOR_BGR2GRAY);
		processedImg_->copyTo(temp);
		// Detect circles using Hough Transformation
		HoughCircles(temp, circles, cv::HOUGH_GRADIENT, 1,
			temp.rows / 8, // change this value to detect circles with different distances to each other
			110, 50, minRadius_, maxRadius_ // change the last two parameters
										  // (minradius & maxradius) to detect larger circles (in pixels)
		);

		if (!circles.empty())
		{
			for (size_t i = 0; i < circles.size(); i++)
			{
				cv::Vec3i c = circles[i];
				// Draw detected circle on the image
				cv::circle(*resImg_, cv::Point(c[0], c[1]), c[2], cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
				// Draw center of the detected circle on the image
				cv::circle(*resImg_, cv::Point(c[0], c[1]), 2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
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
