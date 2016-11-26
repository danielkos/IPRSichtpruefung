#include "UpldFrame.h"
#include <opencv2\core\core.hpp>

UpldFrame::UpldFrame()
{
	videoCapture_ = new cv::VideoCapture();
	exit_ = false;
}

UpldFrame::~UpldFrame()
{
	delete videoCapture_;
}

void UpldFrame::setCamera(std::string cameraName)
{
	videoCapture_->open(cameraName);
}

void UpldFrame::terminateCameraStream()
{
	exit_ = true;
}

cv::Mat UpldFrame::fromFile(std::string filename)		//open an filename image 
{
	cv::Mat img;
	img = cv::imread(filename);

	return img;
}

void UpldFrame::fromCamera()
{
	cv::Mat frame;

	cv::putText(frame, "Camera not opened!", cv::Point(50, 50), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255));

	while (!exit_)
	{
		if (videoCapture_->isOpened())
		{
			frame.release();
			// get a new frame from camera
			videoCapture_->read(frame);
			Q_EMIT newCameraImage(&frame);
		}
	}
}
