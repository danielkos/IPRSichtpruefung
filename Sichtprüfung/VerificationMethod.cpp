#include "VerificationMethod.h"
#include <opencv2\opencv.hpp>

VerificationMethod::VerificationMethod()
{
	resImg_ = new cv::Mat();
}

VerificationMethod::~VerificationMethod()
{
	delete resImg_;
}

cv::Mat* VerificationMethod::getResult()
{
	return resImg_;
}