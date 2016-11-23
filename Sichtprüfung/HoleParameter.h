#ifndef HOLEPARAMETER_H
#define HOLEPARAMETER_H
#include <opencv2/imgproc/imgproc.hpp> 
#include "opencv2/opencv.hpp"

class HoleParameter
{
public:
	std::vector<cv::Vec3f> CheckParameter(cv::Mat img);
};
#endif