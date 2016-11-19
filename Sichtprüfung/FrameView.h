#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QLabel>

namespace cv
{
	class Mat;
}
/** 
* \brief This class represents a view which can display 
* and convert OpenCV images to Qt images
*/
class FrameView : public QLabel
{
	Q_OBJECT

public:
	explicit FrameView(QWidget* parent = 0);
	virtual ~FrameView();

public slots:
	/**
	* \brief Displays an image in the parent widget
	* \param img image which will be displayed
	*/
	virtual void showImage(const cv::Mat* img);

private:
	/**
	* \brief Converts the OpenCV image into a QImage and setores it in qImg_
	* \param img image which will be converted
	*/
	void convertToQtImage(const cv::Mat *img);

	/**
	* \brief Displays the current stored image
	*/
	void displayImage();

	QImage qImg_;
};

#endif // !FRAMEVIEW_H

