#include "MainGui.h"
#include "FrameView.h"
#include "VerificationMethod.h"
#include "MethodGuiItem.h"
#include "UpldFrame.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <utility>

#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QTreeView>
#include <QStandardItemModel>
#include <QTime>

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

	//Clear the current file path
	currentFile_.clear();

	//Select the button
	QPushButton* apply = ui.buttonBoxMethods->button(QDialogButtonBox::Apply);
	QPushButton* open = ui.buttonBoxInputs->button(QDialogButtonBox::Open);
	QPushButton* remove = ui.buttonBoxInputs->button(QDialogButtonBox::Discard);
	open->setText("Add");
	remove->setText("Remove");

	//Connect the signals from the button box to other functions
	connect(apply, &QPushButton::clicked, this, &MainGui::runSelectedMethods);
	connect(open, &QPushButton::clicked, this, &MainGui::addFile);
	connect(remove, &QPushButton::clicked, this, &MainGui::removeFile);
	
	//Labels for the input tab model
	QStringList labels;
	labels.push_back("Filename");
	labels.push_back("Path");
	
	//Create the model for input tab
	QStandardItemModel* fileModel = new QStandardItemModel(0, 2, ui.treeViewInput);
	fileModel->setHorizontalHeaderLabels(labels);

	ui.treeViewInput->setModel(fileModel);
	ui.treeViewInput->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

	connect(ui.treeViewInput, SIGNAL(clicked(QModelIndex)),	this, SLOT(setCurrentFile(QModelIndex)));

	logOutput("Start up");
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
	if (!img->empty())
	{
		//be carefull on stream this might be invalid
		*orgImg_ = *img;
		//at startup all images are empty
		inputView_->showImage(orgImg_);

		logOutput("Setting image");
	}
}

void MainGui::addVerificationMethod(std::string name, VerificationMethod* method)
{
	logOutput("Adding method: " + QString::fromStdString(name));
	//Create an item and attach it to the widget
	MethodGuiItem* item = new MethodGuiItem(name, method->parameters(), ui.widMethods);
	//Setup association
	methods_.insert(ItemMethodPair(item, method));
	//Add item to the layout
	ui.widMethods->layout()->addWidget(item);
}

void MainGui::runSelectedMethods()
{
	//Look for all checked methods an execute them
	for (ItemMethodMap::iterator it = methods_.begin(); it != methods_.end(); it++)
	{
		if (it->first->selected())
		{
			logOutput("Running method: " + QString::fromStdString(it->first->name()));
			//Get current parametrs from method
			it->second->setParameters(it->first->parameters());

			if (it->second->run(orgImg_))
			{
				logOutput("Method: " + QString::fromStdString(it->first->name()) + " successful");
				//If method was successful, combine results into one image
				//In this state not suitable for parallelization
				//Src and Dst have to have the same type
				it->first->setMode(true);
				//Get results from method, in this case imgs
				preprocImg_ = it->second->processed();
				resultImg_ = it->second->result();
				//Show imgs on gui
				resultView_->showImage(resultImg_);
				preprocView_->showImage(preprocImg_);
			}
			else
			{
				//If method fails change appearance 
				it->first->setMode(false);
				logOutput("Method: " + QString::fromStdString(it->first->name()) + " failed");
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
	
	filenames = dialog.getOpenFileNames(this, "Select an image", QString(), filter);

	QStandardItemModel* model = static_cast<QStandardItemModel*>(ui.treeViewInput->model());

	for (size_t i = 0; i < filenames.size(); i++)
	{
		QFileInfo fileInfo(filenames.at(i));
		//Cast from QAbstractItemModel to QStandardItemModel to have full functionality
		
		//Check if cast was successful
		if (model)
		{
			//Add filename and filepath to the model
			QStandardItem* name = new QStandardItem(fileInfo.fileName());
			QStandardItem* path = new QStandardItem(fileInfo.filePath());

			logOutput("Adding file: " + fileInfo.fileName() + " with path: " + fileInfo.filePath());
			
			name->setEditable(false);
			path->setEditable(false);

			name->setData(QVariant::fromValue(QString(fileInfo.fileName())), Qt::DisplayRole);
			path->setData(QVariant::fromValue(QString(fileInfo.filePath())), Qt::DisplayRole);
			
			model->appendRow(name);
			model->setItem(model->rowCount()-1, model->columnCount()-1, path);
	//Select last added file
		}
	}

	QModelIndex index = model->index(model->rowCount() - 1, model->columnCount() - 1);
	ui.treeViewInput->setCurrentIndex(index);
	setCurrentFile(index);
}

void MainGui::removeFile()
{
	logOutput("Removing last file");
	QModelIndexList selection = ui.treeViewInput->selectionModel()->selectedRows();

	// Multiple rows can be selected
	for (int i = 0; i < selection.count(); i++)
	{
		QModelIndex index = selection.at(i);
		ui.treeViewInput->model()->removeRow(index.row());
	}

	reset();
}

void MainGui::setCurrentFile(QModelIndex index)
{
	//Cast from QAbstractItemModel to QStandardItemModel to have full functionality
	QStandardItem* item = static_cast<QStandardItemModel*>(ui.treeViewInput->model())->item(index.row(), 1);
	cv::Mat img;

	//Check if cast was successful
	if (item)
	{
		//Get the file path
		currentFile_ = item->data(Qt::DisplayRole).value<QString>();

		logOutput("Using current file: " + currentFile_);

		if (currentFile_.isEmpty())
		{
			img = UpldFrame::fromCamera();
		}
		else
		{
			img = UpldFrame::fromFile(currentFile_.toStdString());
		}

		statusOutput("Finished!");

		setInputImage(&img);
	}
}

void MainGui::reset()
{
	orgImg_->release();
	preprocImg_->release();
	resultImg_->release();
}

void MainGui::logOutput(QString msg)
{
	QString str = "[" + QTime::currentTime().toString() + "]: " + msg;
	ui.listWidgetLog->addItem(str);
}

void MainGui::statusOutput(QString msg)
{
	ui.labelProgress->setText(msg);
}