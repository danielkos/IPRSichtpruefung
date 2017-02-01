#ifndef CAMERA_H
#define CAMERA_H

#include <mutex>
#include <thread>

#include <QObject>

#include <opencv2\opencv.hpp>

class Camera : public QObject
{
	Q_OBJECT
public:
	Camera();
	virtual ~Camera();

	virtual bool openCamera() = 0;
	virtual bool isOpen() = 0;
	virtual bool acquireImage() = 0;
	virtual void startStream();
	virtual void stopStream();

	bool streamRunning();
	
	cv::Mat currentImg();
	cv::Mat* currentImgPtr();

Q_SIGNALS:

	void newCameraImage(cv::Mat* img);
private:
	void stream();

	std::thread camThread_;
	bool stopStream_;

protected:
	cv::Mat* currentImg_;
	std::mutex imgLock_;

};
Q_DECLARE_METATYPE(cv::Mat*);
#endif // !CAMERA_H
