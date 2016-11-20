#ifndef UPLDFRAME_H
#define UPLDFRAME_H 

#include <opencv2/opencv.hpp>

class UpldFrame
{
public:
	static cv::Mat fromFile(std::string file_name);
	static cv::Mat fromCamera();
};
#endif