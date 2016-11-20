#include "UpldFrame.h"

cv::Mat UpldFrame::fromFile(std::string filename)		//open an filename image 
{
	cv::Mat img;
	img = cv::imread(filename);
	return img;
}

cv::Mat UpldFrame::fromCamera()
{
	cv::VideoCapture cap(0); // open the default camera
	cv::Mat frame;
	cap >> frame; // get a new frame from camera
	return frame;
}