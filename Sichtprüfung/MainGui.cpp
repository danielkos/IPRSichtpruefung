#include "MainGui.h"

MainGui::MainGui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	inputView_.reset(new FrameView(ui.widInputImage));
}

MainGui::~MainGui()
{
	
}

void MainGui::setInputImage(cv::Mat* img)
{
	inputImg_.reset(img);
	inputView_->showImage()
}
