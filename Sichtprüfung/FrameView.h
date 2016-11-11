#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <memory>
#include <opencv2/opencv.hpp>

class FrameView
{

public:
	FrameView(QWidget* widget);
	~FrameView();

public slots:
	void showImage(const cv::Mat& img);

protected:
	void paintEvent(QPaintEvent*);

private:
	QImage qImg_;
    std::shared_ptr<QWidget> widFrame_;
};

#endif // !FRAMEVIEW_H

