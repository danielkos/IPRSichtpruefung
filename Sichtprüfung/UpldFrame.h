#ifndef UPLDFRAME_H
#define UPLDFRAME_H 

#include "Camera.h"

#include <mutex>

namespace cv
{
	class Mat;
	class VideoCapture;
}

class UpldFrame : public Camera
{

public:
	UpldFrame();
	virtual ~UpldFrame();

	bool openCamera();
	bool isOpen();
	bool acquireImage();

	static cv::Mat fromFile(std::string file_name);

private:

	// Time delay (in milliseconds) between the recording of two camera frames.
	// IPR camera works with 11.2fps => ~89ms per frame
	//const long CAMERA_RECORD_DELAY = 90;

	// Camera parameters
	const double CAMERA_WIDHT = 2048;
	const double CAMERA_HEIGHT = 1536;
	const double CAMERA_FPS = 11.2;

	cv::VideoCapture* videoCapture_;
};
#endif