#ifndef UPLDFRAME_H
#define UPLDFRAME_H
#include <opencv2/imgproc/imgproc.hpp> 
#include "opencv2/opencv.hpp"
class UpldFrame
{
public:
	cv::Mat fromFile(std::string file_name);
	cv::Mat fromCamera();
};
#endif