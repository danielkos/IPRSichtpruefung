#include "HoleVerification.h"
#include <opencv2\opencv.hpp>

HoleVerification::HoleVerification()
{

}

HoleVerification::~HoleVerification()
{
}

bool HoleVerification::run(const cv::Mat* img)
{
	*resImg_ = *img;
	return true;
}