#include "UpldFrame.h"
#include <opencv2\core\core.hpp>

#include <chrono>
#include <thread>

#include "CLogger.h"


UpldFrame::UpldFrame()
{
	//videoCapture_ = new cv::VideoCapture();
	//exit_ = false;
}

UpldFrame::~UpldFrame()
{
	//delete videoCapture_;
}
/*
bool UpldFrame::openCamera()
{
	// Use 0 to use default camera of OS
	return videoCapture_->open(0);
}

void UpldFrame::terminateCameraStream()
{
	exit_ = true;
}
*/
cv::Mat UpldFrame::fromFile(std::string filename)		//open an filename image 
{
	cv::Mat img;
	img = cv::imread(filename);

	return img;
}
/*
cv::Mat UpldFrame::currentImg()
{
	cv::Mat ret;
	imgLock_.lock();
	currentImg_.copyTo(ret);
	imgLock_.unlock();

	return ret;
}

cv::Mat* UpldFrame::fromCamera(bool returnImg)
{
	// Set camera parameters. Various parameters can be set, see:
	// http://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html
	if  (videoCapture_ != 0)
	{ 
		videoCapture_->set(CV_CAP_PROP_FRAME_WIDTH, CAMERA_WIDHT);
		videoCapture_->set(CV_CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT);
		videoCapture_->set(CV_CAP_PROP_FPS, CAMERA_FPS);

	}

	cv::putText(currentImg_, "Camera not opened!", cv::Point(50, 50), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255));

	while (!exit_)
	{
		if (videoCapture_->isOpened())
		{
			imgLock_.lock();
			currentImg_.release();
			// get a new frame from camera
			videoCapture_->read(currentImg_);

			imgLock_.unlock();

			if (returnImg)
			{
				exit_ = true;
			}

			Q_EMIT newCameraImage(&currentImg_);
		}
		else if (returnImg)
		{
			exit_ = true;
		}
	}

	videoCapture_->release();

	return &currentImg_;
}*/