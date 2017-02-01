#include "Camera.h"
#include "MainGui.h"
#include <opencv2\opencv.hpp>

Camera::Camera()
{
	currentImg_ = NULL;
	stopStream_ = false;
}

Camera::~Camera()
{
	stopStream();

	imgLock_.lock();
	if (currentImg_)
	{
		currentImg_->release();
	}
	imgLock_.unlock();

	currentImg_ = NULL;
	stopStream_ = false;
}

void Camera::startStream()
{
	//stopStream();
	stopStream_ = false;
	camThread_ = std::thread(&Camera::stream, this);
	camThread_.detach();
}

void Camera::stopStream()
{
	stopStream_ = true;
}

void Camera::stream()
{
	bool ret = true;
	while (!stopStream_)
	{
		imgLock_.lock();
		ret = acquireImage();
		imgLock_.unlock();

		if (ret)
		{
			Q_EMIT newCameraImage(currentImg_);
		}	
	}
}

bool Camera::streamRunning()
{
	return stopStream_;
}

cv::Mat Camera::currentImg()
{
	cv::Mat ret;
	imgLock_.lock();

	if (currentImg_)
	{
		currentImg_->copyTo(ret);
	}
	
	imgLock_.unlock();

	return ret;
}

cv::Mat* Camera::currentImgPtr()
{
	return currentImg_;
}