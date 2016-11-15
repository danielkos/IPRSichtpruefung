#include "FrameView.h"
#include <opencv2/opencv.hpp>
#include <QImage>

FrameView::FrameView(QWidget* parent)
	:QLabel(parent)
{
	setScaledContents(true);
	setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

FrameView::~FrameView()
{
}

void FrameView::convertToQtImage(const cv::Mat *img)
{
	cv::Mat tmp;
	switch (img->type()) {
	case CV_8UC1:
		cv::cvtColor(*img, tmp, CV_GRAY2RGB);
		break;
	case CV_8UC3:
		cv::cvtColor(*img, tmp, CV_BGR2RGB);
		break;
	}

	// QImage needs the data to be stored continuously in memory
	assert(tmp.isContinuous());

	qImg_ = QImage((uchar*)tmp.data, tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888);
}

void FrameView::displayImage()
{
	setPixmap(QPixmap::fromImage(qImg_));
	show();
}

void FrameView::showImage(const cv::Mat* img)
{
	convertToQtImage(img);
	displayImage();
}



