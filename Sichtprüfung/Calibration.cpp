#include "Calibration.h"
#include "Configs.h"
#include <QVariant>
#include <QSize>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>

Calibration::Calibration()
{
	cannyLowerThresh_ = 50;
	cannyUpperThresh_ = 100;
	morphIterations_ = 2;
	ignoreContourSize_ = 100;
	contourSize_ = 250;
	drawLines_ = true;
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
		contourSize_ = parameters[4].value_.toInt();
		drawLines_ = parameters[5].value_.toBool();
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

	param.setUp("Contour Size(pixel)", QVariant(contourSize_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Draw bounding rect", QVariant(drawLines_), QMetaType::Bool);
	parameters.push_back(param);

	parametersSize_ = parameters.size();

	return parameters;
}

ResultGenerator::ResultMap Calibration::results()
{
	ResultGenerator::ResultMap results;
	Parameter param;
	QSize size(boundingBox_.size.width, boundingBox_.size.height);

	param.setUp("Pixel ratio", size, QMetaType::QSize);

	//Set a paramter definied for the generator
	results.insert(ResultGenerator::ResultPair(ResultGenerator::Results::RES_CALIBRATION, param));

	return results;
}

cv::RotatedRect* Calibration::boundingBox()
{
	return &boundingBox_;
}

bool Calibration::run(const cv::Mat* img)
{
	bool res = true;

	//Check if img is empty
	if (!img->empty())
	{
		std::vector<std::vector<cv::Point> > contours;
		std::vector<std::vector<cv::Point> > fittedLines;
		cv::Mat tmp;
		
		//Init result image
		initializeResultImage(img);
		//Preprocess
		cv::medianBlur(*img, *processedImg_, 7);
		cv::cvtColor(*processedImg_, *processedImg_, cv::COLOR_BGR2GRAY);
		cv::Canny(*processedImg_, *processedImg_, cannyLowerThresh_, cannyUpperThresh_);
		cv::morphologyEx(*processedImg_, *processedImg_, cv::MORPH_CLOSE, cv::noArray(), cv::Point(-1, -1), morphIterations_);
		cv::dilate(*processedImg_, *processedImg_, cv::getStructuringElement(cv::MORPH_DILATE, cv::Size(3, 3)));

		//Copy processed img because next operations alters it
		processedImg_->copyTo(tmp);
		cv::findContours(tmp, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

		if (!contours.empty())
		{
			for (size_t i = 0; i < contours.size(); i++)
			{
				double inter = cv::contourArea(contours[i]);
				//Ignore all contours without self-intersections
				if (inter < ignoreContourSize_ || contours[i].size() < contourSize_)
				{
					continue;
				}
				drawContour(contours, i, resultColor::contourColor);
				
				boundingBox_ = cv::minAreaRect(contours[i]);
				cv::Point2f vertices[4];
				cv::Point2f midVertices[4];
				
				boundingBox_.points(vertices);
				boundingBox_.size.width;

				if (drawLines_)
				{
					//draw rect lines
					for (size_t i = 0; i < 4; i++)
					{
						cv::Point2f v1 = vertices[i];
						cv::Point2f v2 = vertices[(i + 1) % 4];
						drawLine(v1, v2, resultColor::resultColor);
						midVertices[i].x = (v1.x + v2.x) / 2;
						midVertices[i].y = (v1.y + v2.y) / 2;
					}
					//draw mid lines
					for (size_t i = 0; i < 4; i++)
					{
						drawLine(midVertices[i], midVertices[(i + 2) % 4], resultColor::infoColor);
					}

					//draw points on top of the lines
					for (size_t i = 0; i < 4; i++)
					{
						drawPoint(vertices[i], resultColor::middleColor);
						drawPoint(midVertices[i], resultColor::middleColor);
					}
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