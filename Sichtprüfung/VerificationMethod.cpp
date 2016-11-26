#include "VerificationMethod.h"
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

cv::Mat* VerificationMethod::result()
{
	return resImg_;
}

cv::Mat* VerificationMethod::processed()
{
	return processedImg_;
}