#include "UpldFrame.h"
#include "Logger.h"

#include <opencv2\opencv.hpp>

UpldFrame::UpldFrame()
{
	videoCapture_ = new cv::VideoCapture();
	currentImg_ = new cv::Mat();

	videoCapture_->set(CV_CAP_PROP_FRAME_WIDTH, CAMERA_WIDHT);
	videoCapture_->set(CV_CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT);
	videoCapture_->set(CV_CAP_PROP_FPS, CAMERA_FPS);
}

UpldFrame::~UpldFrame()
{
	if (videoCapture_)
	{
		delete videoCapture_;
	}
}

bool UpldFrame::openCamera()
{
	// Use 0 to use default camera of OS
	return videoCapture_->open(0);
}

bool UpldFrame::isOpen()
{
	return videoCapture_->isOpened();
}

cv::Mat UpldFrame::fromFile(std::string filename)		//open an filename image 
{
	cv::Mat img;
	img = cv::imread(filename);

	return img;
}

bool UpldFrame::acquireImage()
{
	bool ret = true;

	if (isOpen())
	{
		cv::Mat frame;
		// get a new frame from camera
		videoCapture_->read(frame);

		if (!frame.empty())
		{
			frame.copyTo(*currentImg_);
		}
		else
		{
			ret = false;
		}
	}


	return ret;
}