#include "AngleVerification.h"
#include "Configs.h"

#include <QVariant>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>

AngleVerification::AngleVerification()
{
	cannyLowerThresh_ = 50;
	cannyUpperThresh_ = 100;
	minHough_dominantOrientation_ = 200;
	minHough_angleLine_ = 60;
	angleTolerance_ = 10.0;
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
		cannyLowerThresh_ = parameters[0].value_.toDouble();
		cannyUpperThresh_ = parameters[1].value_.toDouble();
		minHough_dominantOrientation_ = parameters[2].value_.toInt();
		minHough_angleLine_ = parameters[3].value_.toInt();
		angleTolerance_ = parameters[4].value_.toDouble();
	}
}


std::vector<Parameter> AngleVerification::parameters()
{
	std::vector<Parameter>parameters;
	Parameter param;

	//Setup parameter, name will be displayed on gui
	param.setUp("Canny Lower Threshold", QVariant(cannyLowerThresh_), QMetaType::Double);
	parameters.push_back(param);

	param.setUp("Canny Upper Threshold", QVariant(cannyUpperThresh_), QMetaType::Double);
	parameters.push_back(param);

	param.setUp("Min Hough: Object Orientation", QVariant(minHough_dominantOrientation_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Min Hough: Angle", QVariant(minHough_angleLine_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Angle Equal Tolerance", QVariant(angleTolerance_), QMetaType::Double);
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
		// Generating a white contour of the object on a black background
		// Filter surrounding lights, optimum: only object contours are visible with straight thin lines
		cv::cvtColor(*img, *processedImg_, cv::COLOR_BGR2GRAY);
		cv::medianBlur(*img, *resImg_, 5);
		inRange(*processedImg_, 50, 60, *processedImg_);
		cv::Canny(*processedImg_, *processedImg_, cannyLowerThresh_, cannyUpperThresh_);
		cv::morphologyEx(*processedImg_, *processedImg_, cv::MORPH_CLOSE, cv::noArray(), cv::Point(-1, -1), 2);
		cv::dilate(*processedImg_, *processedImg_, cv::getStructuringElement(cv::MORPH_DILATE, cv::Size(3, 3)));
		

		// Hough-Transformation to find the dominant orientation of the object => only consider
		// lines with big length
		std::vector<cv::Vec4i> lines;
		cv::HoughLinesP(*processedImg_, lines, 1, CV_PI / 180, 40, minHough_dominantOrientation_, 0);
		
		double rotationAngle = 0.0;		// Angle between the dominant orientation of the object
										// and the horizontal x axis
		if (lines.size() > 0) 
		{
			// It is assumed that only a few, very long lines are found, so just use the first one
			// (because object has a dominant size in one direction) 
			cv::Vec4i l = lines[0];

			rotationAngle = getAngleBtwLineAndXAxis(l);

			// Draw the line that was used for the orientation correction with a blue color
			drawLine(cv::Point2f(l[0], l[1]), cv::Point2f(l[2], l[3]), colors::infoColor);
		}
		

		// Rotate images by the calculated angle. Object should be horizontal in all images now
		cv::Mat rotation = cv::getRotationMatrix2D(cv::Point(processedImg_->cols / 2, processedImg_->rows / 2), rotationAngle, 1);
		cv::warpAffine(*processedImg_, *processedImg_, rotation, cv::Size(processedImg_->cols, processedImg_->rows));
		cv::warpAffine(*resImg_, *resImg_, rotation, cv::Size(resImg_->cols, resImg_->rows));
		

		// Use Hough-Transformation again to approximate the contour of the object with straight lines.
		// Use small minimum line length parameter now to approximate the contour of the object as good
		// as possible
		cv::HoughLinesP(*processedImg_, lines, 1, CV_PI / 180, 40, minHough_angleLine_, 0);
			
		// Calculate the angle between the detected Hough-Lines and the horizontal x axis.
		// Because the object should be parallel to the x-axis in the image, only the Hough-Lines that
		// make up the "Schwalbenschwanznut" of the object should have an angular orientation now. All other lines
		// are parallel to the x or y axis (by considering a small tolerance angleTolerance_).
		std::vector<HoughLine> linesOfLeftNut;
		std::vector<HoughLine> linesOfRightNut;

		for (size_t i = 0; i < lines.size(); i++)
		{
			cv::Vec4i l = lines[i];
			double angle = getAngleBtwLineAndXAxis(l);
			
			if ( /* line not parallel to x axis */
				!(abs(angle) >= -angleTolerance_ && abs(angle) <= angleTolerance_)
				/* line not parallel to y axis */
				&& !(abs(angle) >= 90.0 - angleTolerance_ && abs(angle) <= 90.0 + angleTolerance_))
			{
				// Line has an angular orientation. Check if it belongs to the left or 
				// right "Schwalbenschwanznut" of the object
				HoughLine houghLine;
				houghLine.setUp(l, angle);

				if (angle < 0.0)
				{
					linesOfRightNut.push_back(houghLine);
				}
				else
				{
					linesOfLeftNut.push_back(houghLine);
				}

				// Draw the Hough-Lines that have been detected for the "Schwalbenschwanznut"
				drawLine(cv::Point2f(l[0], l[1]), cv::Point2f(l[2], l[3]), colors::resultColor);
			}
		}


		// Usually more than one Hough-Line is detected for the "Schwalbenschwanznut", so calculate the
		// median of the angles of each line to get a good overall result
		angleLeft_ = abs(calculateMedianAngle(&linesOfLeftNut));
		angleRight_ = abs(calculateMedianAngle(&linesOfRightNut));
	}
	else
	{
		res = false;
	}

	return res;
}


double AngleVerification::getAngleBtwLineAndXAxis(cv::Vec4i line)
{
	return std::atan2f(double(line[3] - line[1]), double(line[2] - line[0])) * 180.0 / CV_PI;
}


double AngleVerification::calculateMedianAngle(std::vector<HoughLine> *lines)
{
	double medianAngle = 0.0;

	if (lines != 0 && lines->size() > 0)
	{
		for (size_t i = 0; i < lines->size(); i++)
		{
			medianAngle += lines->at(i).angle_;
		}

		medianAngle /= lines->size();
	}

	return medianAngle;
}
