#include "UpldFrame.h"
#include <opencv2\core\core.hpp>

#include <chrono>
#include <thread>

#include "CLogger.h"


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
	// Use 0 to use default camera of OS
	videoCapture_->open(0);
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
	exit_ = false;

	cv::putText(frame, "Camera not opened!", cv::Point(50, 50), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255));

	while (!exit_)
	{
		if (videoCapture_->isOpened())
		{
			frame.release();
			// get a new frame from camera
			videoCapture_->read(frame);

			// TODO: Kamerauflösung und Einstellungen checken: es kommt immer ein Bild von 640x480 an
			LOGGER->Log("Camera resolution: %d %d", frame.cols, frame.rows);
		}

		Q_EMIT newCameraImage(&frame);
		
		// Delay between two camera frames, to have some time for calculations on an image
		std::this_thread::sleep_for(std::chrono::milliseconds(CAMERA_RECORD_DELAY));
	}

	videoCapture_->release();
}