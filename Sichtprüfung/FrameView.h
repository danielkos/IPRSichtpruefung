#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QLabel>

namespace cv
{
	class Mat;
}


class FrameView : public QLabel
{
	Q_OBJECT

public:
	explicit FrameView(QWidget* parent = 0);
	virtual ~FrameView();

public slots:
	/**
	* \brief Displays an image in the parent widget
	*/
	virtual void showImage(const cv::Mat* img);

private:
	/**
	* \brief Converts the OpenCV image into a QImage and sets it
	*/
	void convertToQtImage(const cv::Mat *img);

	/**
	* \brief Displays the current stored image
	*/
	void displayImage();

	QImage qImg_;
};

#endif // !FRAMEVIEW_H

