#include "FrameView.h"

FrameView::FrameView(QWidget* widget)
{
	widFrame_.reset(widget);
}

FrameView::~FrameView()
{
}

void FrameView::showImage(const cv::Mat& img)
{
	cv::Mat tmp;
	switch (img.type()) {
		case CV_8UC1:
			cvtColor(img, tmp, CV_GRAY2RGB);
			break;
		case CV_8UC3:
			cvtColor(img, tmp, CV_BGR2RGB);
			break;
	}
	
	// QImage needs the data to be stored continuously in memory
	assert(tmp.isContinuous());
	// Assign OpenCV's image buffer to the QImage. Note that the bytesPerLine parameter
	// (http://qt-project.org/doc/qt-4.8/qimage.html#QImage-6) is 3*width because each pixel
	// has three bytes.
	qImg_ = QImage(tmp.data, tmp.cols, tmp.rows, tmp.cols * 3, QImage::Format_RGB888);

	widFrame_->repaint();
}

void FrameView::paintEvent(QPaintEvent*)
{
	QPainter painter(widFrame_.get());
	painter.drawImage(QPoint(0, 0), qImg_);
	painter.end();
}