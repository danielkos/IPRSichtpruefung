#include "MainGui.h"
#include "FrameView.h"
#include "VerificationMethod.h"
#include "MethodGuiItem.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <utility>

#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QTableWidgetItem>
#include <QPushButton>

MainGui::MainGui(QWidget *parent)
	: QMainWindow(parent)
{
	//setup ui
	ui.setupUi(this);

	//set a parent for a view
	inputView_ = new FrameView(ui.widInputImage);
	preprocView_ = new FrameView(ui.widPreprocessed);
	resultView_ = new FrameView(ui.widResult);

	//add views to the layout of the parent widget
	ui.widInputImage->layout()->addWidget(inputView_);
	ui.widPreprocessed->layout()->addWidget(preprocView_);
	ui.widResult->layout()->addWidget(resultView_);

	//initialize images; needed for copy
	orgImg_ = new cv::Mat();
	preprocImg_ = new cv::Mat();
	resultImg_ = new cv::Mat();

	//Select the button
	QPushButton* apply = ui.buttonBoxMethods->button(QDialogButtonBox::Apply);
	QPushButton* open = ui.buttonBoxInputs->button(QDialogButtonBox::Open);
	QPushButton* remove = ui.buttonBoxInputs->button(QDialogButtonBox::Discard);
	remove->setText("Remove");

	//Connect the signals from the button box to other functions
	connect(apply, &QPushButton::clicked, this, &MainGui::runSelectedMethods);
	connect(open, &QPushButton::clicked, this, &MainGui::addFile);
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
	//compute the grayscale image
	cv::cvtColor(*orgImg_, *preprocImg_, CV_BGR2GRAY);

	//at startup all images are empty
	inputView_->showImage(orgImg_);
	preprocView_->showImage(preprocImg_);
	resultView_->showImage(resultImg_);
}

void MainGui::addVerificationMethod(std::string name, VerificationMethod* method)
{
	//Create an item and attach it to the widget
	MethodGuiItem* item = new MethodGuiItem(name, ui.widMethods);
	//Setup association
	methods_.insert(ItemMethodPair(item, method));
	//Add item to the layout
	ui.widMethods->layout()->addWidget(item);
}

void MainGui::runSelectedMethods()
{
	//look for all checked methods an execute them
	for (ItemMethodMap::iterator it = methods_.begin(); it != methods_.end(); it++)
	{
		if (it->first->selected())
		{
			if (it->second->run(preprocImg_))
			{
				//If method was successful, combine results into one image
				//In this state not suitable for parallelization
				cv::addWeighted(*preprocImg_, 0.5, *(it->second->getResult()), 0.5, 0.0, *resultImg_);
				resultView_->showImage(resultImg_);
			}

		}
	}
}

void MainGui::addFileStream(QString stream)
{
}

void MainGui::addFile()
{
	QFileDialog dialog(this);
	QStringList filenames;
	QString filter = "Images(*.png *.bmp *.jpg *.jpeg)";
	QTableWidgetItem* item = new QTableWidgetItem("test");

	filenames = dialog.getOpenFileNames(this, "Select an image", QString(), filter);
	ui.tableInput->setItem(0, 1, item);
}