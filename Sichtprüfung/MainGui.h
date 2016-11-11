#ifndef MAINGUI_H
#define MAINGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_MainGui.h"

#include "FrameView.h"

class MainGui : public QMainWindow
{
	Q_OBJECT

public:
	MainGui(QWidget *parent = 0);
	~MainGui();

	void setInputImage(cv::Mat* img);

private:
	Ui::MainGui ui;
	std::shared_ptr<FrameView> inputView_;

	std::shared_ptr<cv::Mat> inputImg_;
};

#endif // MAINGUI_H
