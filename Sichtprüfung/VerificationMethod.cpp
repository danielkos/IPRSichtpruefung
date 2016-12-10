#include "VerificationMethod.h"
#include "Configs.h"
#include <opencv2\opencv.hpp>

VerificationMethod::VerificationMethod()
{
	resImg_ = new cv::Mat();
	processedImg_ = new cv::Mat();
	parametersSize_ = 0;
}

VerificationMethod::~VerificationMethod()
{
	delete resImg_;
	delete processedImg_;
}

void VerificationMethod::initializeResultImage(const cv::Mat* img)
{
	img->copyTo(*resImg_);
}
void VerificationMethod::drawPoint(cv::Point2f& point, const cv::Scalar& color)
{
	cv::circle(*resImg_, point, colors::pointThickness, color, -1);
}

void VerificationMethod::drawLine(cv::Point2f& start, cv::Point2f& end, const cv::Scalar& color)
{
	cv::line(*resImg_, start, end, color, colors::lineThickness, CV_AA);
}

void VerificationMethod::drawCircle(cv::Point2f& center, size_t radius, const cv::Scalar& color)
{
	cv::circle(*resImg_, center, radius, color, colors::circleThickness);
}

void VerificationMethod::drawContour(cv::InputArrayOfArrays& contours, size_t index, const cv::Scalar& color)
{
	cv::drawContours(*resImg_, contours, index, colors::contourColor, colors::contourThickness);
}

cv::Mat* VerificationMethod::resultImg()
{
	return resImg_;
}

cv::Mat* VerificationMethod::processed()
{
	return processedImg_;
}