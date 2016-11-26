#include "Calibration.h"
#include <QVariant>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>

Calibration::Calibration()
{
	cannyLowerThresh_ = 50;
	cannyUpperThresh_ = 100;
	morphIterations_ = 2;
	ignoreContourSize_ = 1000;
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
		cannyLowerThresh_ = parameters[0].value_.toDouble();
		cannyUpperThresh_ = parameters[1].value_.toDouble();
		morphIterations_ = parameters[2].value_.toInt();
		ignoreContourSize_ = parameters[3].value_.toInt();
	}
}

std::vector<Parameter> Calibration::parameters()
{
	std::vector<Parameter> parameters;
	Parameter param;
	//Setup parameter, name will be displayed on gui
	param.setUp("Lower Threshold", QVariant(cannyLowerThresh_), QMetaType::Double);
	parameters.push_back(param);
	
	param.setUp("Upper Threshold", QVariant(cannyUpperThresh_), QMetaType::Double);
	parameters.push_back(param);

	param.setUp("Morph Close Iterations", QVariant(morphIterations_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Ignore Contour Size", QVariant(ignoreContourSize_), QMetaType::Int);
	parameters.push_back(param);

	parametersSize_ = parameters.size();

	return parameters;
}

bool Calibration::run(const cv::Mat* img)
{
	bool res = true;

	//Check if img is empty
	if (!img->empty())
	{
		std::vector<std::vector<cv::Point> > contours;
		cv::Mat tmp;
		//Preprocess
		cv::medianBlur(*img, *resImg_, 7);
		cv::cvtColor(*resImg_, *processedImg_, cv::COLOR_BGR2GRAY);
		cv::Canny(*processedImg_, *processedImg_, cannyLowerThresh_, cannyUpperThresh_);
		cv::morphologyEx(*processedImg_, *processedImg_, cv::MORPH_CLOSE, cv::noArray(), cv::Point(-1, -1), morphIterations_);

		//Copy processed img because next operations alters it
		processedImg_->copyTo(tmp);
		cv::findContours(tmp, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

		if (!contours.empty())
		{
			for (size_t i = 0; i < contours.size(); i++)
			{
				//Ignore all contours without self-intersections
				if (cv::contourArea(contours[i]) < ignoreContourSize_)
				{
					continue;
				}
				
				cv::drawContours(*resImg_, contours, i, cv::Scalar(0, 255, 0), 3);
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