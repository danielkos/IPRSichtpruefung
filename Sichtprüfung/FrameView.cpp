#include "FrameView.h"
#include "cvmatandqimage.h"
#include <opencv2/opencv.hpp>
#include <QImage>

#include <chrono>
#include <thread>

#include <Logger.h>

FrameView::FrameView(QWidget* parent)
	: QLabel(parent)
{
	//Allow to scale the image automatically
	setScaledContents(true);
	setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

FrameView::~FrameView()
{
}

void FrameView::convertToQtImage(const cv::Mat *img)
{
	//check for type
	cv::Mat tmp;

	if (img != 0 && !img->empty())
	{
		//cvShowImage("PROVA", img);
		//cv::waitKey(0);

		switch (img->type()) {
		case CV_8UC1:
			cv::cvtColor(*img, tmp, CV_GRAY2RGB);
			break;
		case CV_8UC3:
			cv::cvtColor(*img, tmp, CV_BGR2RGB);
			break;
		case CV_8UC4:
			cv::cvtColor(*img, tmp, CV_BGRA2RGB);
			break;
		}

		// QImage needs the data to be stored continuously in memory
		assert(tmp.isContinuous());
		qImg_ = QtOcv::mat2Image(tmp, QtOcv::MCO_RGB, QImage::Format_RGB888);
	}
}

void FrameView::displayImage()
{
	if (!qImg_.isNull())
	{
		setPixmap(QPixmap::fromImage(qImg_));
	}	
	show();
}

void FrameView::showImage(const cv::Mat* img)
{
	convertToQtImage(img);
	displayImage();
}



