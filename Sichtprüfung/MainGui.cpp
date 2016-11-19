#include "MainGui.h"
#include "FrameView.h"
#include "VerificationMethod.h"
#include "MethodGuiItem.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <utility>
#include <QDialogButtonBox>

MainGui::MainGui(QWidget *parent)
	: QMainWindow(parent)
{
	//setup ui
	ui.setupUi(this);

	//set a parent for a view
	inputView_ = new FrameView(ui.widInputImage);
	preprocView_ = new FrameView(ui.widPreprocessed);
	resultView_ = new FrameView(ui.widResult);

	//add it to the layout of the parent widget
	ui.widInputImage->layout()->addWidget(inputView_);
	ui.widPreprocessed->layout()->addWidget(preprocView_);
	ui.widResult->layout()->addWidget(resultView_);

	orgImg_ = new cv::Mat();
	preprocImg_ = new cv::Mat();
	resultImg_ = new cv::Mat();

	
	ui.buttonBoxMethods->addButton(QDialogButtonBox::Ok);
	//ui.buttonBoxMethods->addButton(QDialogButtonBox::Cancel);
	QObject::connect(ui.buttonBoxMethods, &QDialogButtonBox::accepted, this, &MainGui::runSelectedMethods);
}
MainGui::~MainGui()
{
	delete inputView_;
	delete preprocView_;
	delete resultView_;
	delete orgImg_;
	delete preprocImg_;
	delete resultImg_;
}

void MainGui::setInputImage(cv::Mat* img)
{
	//be carefull on stream this might be invalid
	*orgImg_ = *img;
	cv::cvtColor(*orgImg_, *preprocImg_, CV_BGR2GRAY);

	inputView_->showImage(orgImg_);
	preprocView_->showImage(preprocImg_);
	resultView_->showImage(resultImg_);
}

void MainGui::addVerificationMethod(std::string name, VerificationMethod* method)
{
	MethodGuiItem* item = new MethodGuiItem(name, ui.widMethods);
	methods_.insert(ItemMethodPair(item, method));
	
	ui.widMethods->layout()->addWidget(item);
}

void MainGui::runSelectedMethods()
{
	for (ItemMethodMap::iterator it = methods_.begin(); it != methods_.end(); it++)
	{
		if (it->first->selected())
		{
			if (it->second->run(preprocImg_))
			{
				cv::addWeighted(*preprocImg_, 0.5, *(it->second->getResult()), 0.5, 0.0, *resultImg_);
				resultView_->showImage(resultImg_);
			}

		}
	}
}