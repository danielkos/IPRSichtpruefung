#ifndef UPLDFRAME_H
#define UPLDFRAME_H 

#include <functional>
#include <opencv2\opencv.hpp>
#include <mutex>

#include <QObject>

namespace cv
{
	class Mat;
	class VideoCapture;
}

class UpldFrame //: public QObject
{
	//Q_OBJECT
	
public:
	UpldFrame();
	virtual ~UpldFrame();

	static cv::Mat fromFile(std::string file_name);
	/*cv::Mat* fromCamera(bool returnImg = false);
	void terminateCameraStream();
	bool openCamera();

	cv::Mat currentImg();

Q_SIGNALS:
	void newCameraImage(cv::Mat* img);
	
private:

	// Time delay (in milliseconds) between the recording of two camera frames.
	// IPR camera works with 11.2fps => ~89ms per frame
	//const long CAMERA_RECORD_DELAY = 90;

	// Camera parameters
	const double CAMERA_WIDHT = 2048;
	const double CAMERA_HEIGHT = 1536;
	const double CAMERA_FPS = 11.2;

	cv::VideoCapture* videoCapture_;
	bool exit_;
	cv::Mat currentImg_;
	std::mutex imgLock_;
	*/
};
#endif