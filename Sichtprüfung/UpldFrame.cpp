#include "UpldFrame.h"

cv::Mat UpldFrame::fromFile(std::string filename)		//open an filename image 
{
	cv::Mat img;
	img = cv::imread(filename);

	return img;
}

cv::Mat UpldFrame::fromCamera()
{
	// open the default camera
	cv::VideoCapture cap(0);
	cv::Mat frame;

	if (cap.isOpened())
	{
		// get a new frame from camera
		cap >> frame;
	}
	
	return frame;
}