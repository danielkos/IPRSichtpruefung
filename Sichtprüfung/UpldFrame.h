#ifndef UPLDFRAME_H
#define UPLDFRAME_H 

#include <functional>
#include <Qobject>
#include <opencv2\opencv.hpp>

namespace cv
{
	class Mat;
	class VideoCapture;
}

class UpldFrame : public QObject
{
	Q_OBJECT
	
public:
	UpldFrame();
	virtual ~UpldFrame();

	static cv::Mat fromFile(std::string file_name);
	void fromCamera();
	void terminateCameraStream();
	void setCamera(std::string cameraName);
Q_SIGNALS:
	void newCameraImage(cv::Mat* img);

private:

	// Time delay (in milliseconds) between the recording of two camera frames.
	// IPR camera works with 11.2fps => ~89ms per frame
	const long CAMERA_RECORD_DELAY = 90;

	// Camera parameters
	const double CAMERA_WIDHT = 2048;
	const double CAMERA_HEIGHT = 1536;
	const double CAMERA_FPS = 11.2;

	cv::VideoCapture* videoCapture_;
	bool exit_;
	std::string cameraName_;
};
Q_DECLARE_METATYPE(cv::Mat*);
#endif