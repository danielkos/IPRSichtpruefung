#ifndef MAINGUI_H
#define MAINGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_MainGui.h"

class FrameView;

namespace cv
{
	class Mat;
}

class MainGui : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainGui(QWidget *parent = 0);
	virtual ~MainGui();

	/**
	* \brief Sets the input image vor each available view
	*/
	void setInputImage(cv::Mat* img);

private:
	Ui::MainGui ui;
	/**
	* \brief Views: Input, Processed, Result
	*/
	FrameView* inputView_;
};

#endif // MAINGUI_H
