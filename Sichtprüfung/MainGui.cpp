#include "MainGui.h"
#include "FrameView.h"
#include <opencv2/opencv.hpp>

MainGui::MainGui(QWidget *parent)
	: QMainWindow(parent)
{
	//setup ui
	ui.setupUi(this);

	//set a parent for a view
	inputView_ = new FrameView(ui.widInputImage);

	//add it to the layout of the parent widget
	ui.widInputImage->layout()->addWidget(inputView_);
}
MainGui::~MainGui()
{
	delete inputView_;
}

void MainGui::setInputImage(cv::Mat* img)
{
	//show image in each view
	inputView_->showImage(img);
}
