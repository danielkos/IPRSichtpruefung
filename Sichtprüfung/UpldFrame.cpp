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
cv::Mat* UpldFrame::fromCamera(bool returnImg)
{
	cv::Mat frame;
	exit_ = false;


	cv::putText(frame, "Camera not opened!", cv::Point(50, 50), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255));

	// Set camera parameters. Various parameters can be set, see:
	// http://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html
	if  (videoCapture_ != 0)
	{ 
		videoCapture_->set(CV_CAP_PROP_FRAME_WIDTH, CAMERA_WIDHT);
		videoCapture_->set(CV_CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT);
		//videoCapture_->set(CV_CAP_PROP_BRIGHTNESS, 2);
		//videoCapture_->set(CV_CAP_PROP_CONTRAST, 2);
		videoCapture_->set(CV_CAP_PROP_FPS, CAMERA_FPS);

	}

	while (!exit_)
	{
		if (videoCapture_->isOpened())
		{
			frame.release();
			// get a new frame from camera
			videoCapture_->read(frame);

			if (returnImg)
			{
				exit_ = true;
			}

			Q_EMIT newCameraImage(&frame);
		}
		else if (returnImg)
		{
			exit_ = true;
		}

		// Delay between two camera frames, to have some time for calculations on an image
		std::this_thread::sleep_for(std::chrono::milliseconds(CAMERA_RECORD_DELAY));
	}

	videoCapture_->release();

	return &frame;
}*/