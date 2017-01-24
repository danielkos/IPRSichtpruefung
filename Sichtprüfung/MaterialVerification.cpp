#include "MaterialVerification.h"
#include "Logger.h"
#include "Configs.h"

#include <QVariant>
#include <opencv2\imgproc.hpp>

MaterialVerification::MaterialVerification()
{
	minBrightness_ = 243;
	ratio_ = 2.5;
	materialMetal_ = false;
	pixelAmount_ = 400000;
	minPixelAmount_ = 8000;
	minWidth_ = 10;
	minHeight_ = 10;
}

MaterialVerification::~MaterialVerification()
{
}

void MaterialVerification::setParameters(std::vector<Parameter>parameters)
{
	//Check if the size of the returned paramers is right
	//The order is determined by parameters()
	if (parameters.size() == parametersSize_)
	{
		minBrightness_ = parameters[0].value_.toInt();
		ratio_ = parameters[1].value_.toDouble();
		pixelAmount_ = parameters[2].value_.toInt();
		minPixelAmount_ = parameters[3].value_.toInt();
		minWidth_ = parameters[4].value_.toInt();
		minHeight_ = parameters[5].value_.toInt();
	}
}


std::vector<Parameter> MaterialVerification::parameters()
{
	std::vector<Parameter>parameters;
	Parameter param;

	//Setup parameter, name will be displayed on gui
	param.setUp("Minimal Brightness", QVariant(minBrightness_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Side ratio", QVariant(ratio_), QMetaType::Double);
	parameters.push_back(param);

	param.setUp("Amount of pixels", QVariant(pixelAmount_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Minimal amount of pixels", QVariant(minPixelAmount_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Minimal width", QVariant(minWidth_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Minimal height", QVariant(minHeight_), QMetaType::Int);
	parameters.push_back(param);

	parametersSize_ = parameters.size();


	return parameters;
}

ResultGenerator::ResultMap MaterialVerification::results()
{
	ResultGenerator::ResultMap results;

	Parameter param;
	param.setUp(" Metal", materialMetal_, QMetaType::Bool);
	results.insert(ResultGenerator::ResultPair(ResultGenerator::Results::RES_MATERIAL, param));

	LOGGER.log("Metal" + materialMetal_);

	return results;
}



bool MaterialVerification::run(const cv::Mat* img)
{
	bool res = true;

	//Check if img is empty
	if (!img->empty())
	{
		initializeResultImage(img);
		// remove noise
		cv::GaussianBlur(*img, *processedImg_, cv::Size(), 2, 2);

		cv::Mat src_hsv, brightness, saturation;
		std::vector<cv::Mat> hsv_planes;

		cv::cvtColor(*processedImg_, src_hsv, cv::COLOR_BGR2HSV);
		cv::split(src_hsv, hsv_planes);
		brightness = hsv_planes[2];

		std::vector<std::vector<cv::Point>> contoursReflection;
		cv::Mat mask;
		//get the mask
		cv::threshold(brightness, mask, minBrightness_, 255, cv::THRESH_BINARY);
		//morphologyEx(mask, mask, cv::MORPH_CLOSE, cv::noArray(), cv::Point(-1, -1), 2);
		//get contours of Reflection field
		findContours(mask, contoursReflection, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);


		int max = 0;		// area of current contour with maximum area
		int i_cont = -1;	// index of current contour with maximum area
		float temp;
		// Draw all contours and search for the contour with the maximum area
		for (int i = 0; i< contoursReflection.size(); i++)
		{
			//draw all contours
			drawContour(contoursReflection, i, colors::contourColor);

			if (abs(cv::contourArea(cv::Mat(contoursReflection[i]))) > max)
			{
				max = abs(cv::contourArea(cv::Mat(contoursReflection[i])));
				i_cont = i;
			}
		}
		cv::Rect boundRect;
		float maxRatio = 0;
		int RatioIndex;
		for (int i = 0; i < contoursReflection.size(); i++)
		{
			//creating bounding rectangle of every contour
			boundRect = cv::boundingRect(cv::Mat(contoursReflection[i]));

			if (abs(cv::contourArea(cv::Mat(contoursReflection[i]))) > minPixelAmount_ && boundRect.width>minWidth_ && boundRect.height>minHeight_)
			{
				//	drawRectangle(boundRect.tl(), boundRect.br(), colors::contourColor);
				if (boundRect.width >= boundRect.height)
				{
					temp = float(boundRect.width) / float(boundRect.height);
				}
				else
				{
					temp = float(boundRect.height) / float(boundRect.width);
				}
				if (temp > maxRatio)
				{
					maxRatio = temp;
					RatioIndex = i;
				}
			}
		}
		//check if metal properties have been found
		if (maxRatio > ratio_)
		{
			boundRect = cv::boundingRect(cv::Mat(contoursReflection[RatioIndex]));
			drawRectangle(boundRect.tl(), boundRect.br(), colors::resultColor);
			materialMetal_ = true;
		}
		else
		{
			if (cv::contourArea(cv::Mat(contoursReflection[i_cont])) > pixelAmount_)
			{
				boundRect = cv::boundingRect(cv::Mat(contoursReflection[i_cont]));
				drawRectangle(boundRect.tl(), boundRect.br(), colors::resultColor);
				materialMetal_ = true;
			}
			else
			{
				materialMetal_ = false;
			}
		}

	}
	else
	{
		res = false;
	}

	return res;
}














