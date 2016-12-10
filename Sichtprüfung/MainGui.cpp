#include "MainGui.h"
#include "FrameView.h"
#include "VerificationMethod.h"
#include "MethodGuiItem.h"
#include "UpldFrame.h"
#include "OptionsGui.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <utility>
#include <thread>

#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTime>
#include <QCameraInfo>
#include <QFontMetrics>
#include <QTabWidget>

MainGui::MainGui(QWidget *parent)
	: QMainWindow(parent)
{
	//setup ui
	ui_.setupUi(this);

	//set a parent for a view
	inputView_ = new FrameView(ui_.widInputImage);
	
	//add views to the layout of the parent widget
	ui_.widInputImage->layout()->addWidget(inputView_);

	clearTabs();

	//initialize space for original img, needed for copy
	//preprocImg_ and resultImg_ store only the pointer 
	//and are managed by the corresponding processes
	orgImg_ = new cv::Mat();

	//Clear the current file path
	currentFile_.clear();

	//Select the button
	QPushButton* apply = ui_.buttonBoxMethods->button(QDialogButtonBox::Apply);
	QPushButton* open = ui_.buttonBoxInputs->button(QDialogButtonBox::Open);
	QPushButton* remove = ui_.buttonBoxInputs->button(QDialogButtonBox::Discard);
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
	QStandardItemModel* fileModel = new QStandardItemModel(0, 2, ui_.treeViewInput);
	fileModel->setHorizontalHeaderLabels(labels);

	ui_.treeViewInput->setModel(fileModel);
	ui_.treeViewInput->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	ui_.treeViewInput->setAutoScroll(false);

	connect(ui_.treeViewInput, SIGNAL(clicked(QModelIndex)), this, SLOT(setCurrentFile(QModelIndex)));

	connect(ui_.action_Exit, &QAction::triggered, this, &QMainWindow::close);
	connect(ui_.actionTest_Object, &QAction::triggered, this, &MainGui::openOptions);

	//Create an option window without showing it
	options_ = new OptionsGui();

	//Create IO 
	io_ = new UpldFrame();
		
	connect(io_, SIGNAL(newCameraImage(cv::Mat*)), this, SLOT(setInputImage(cv::Mat*)));
	
	//Get default camera
	QCameraInfo camera = QCameraInfo::defaultCamera();

	if (!camera.isNull())
	{
		addFileStream(camera.deviceName());
	}
	
	logOutput("Start up");
}
MainGui::~MainGui()
{
	delete inputView_;
	delete orgImg_;
	delete io_;
}

void MainGui::setInputImage(cv::Mat* img)
{
	if (!img->empty())
	{
		//be carefull on stream this might be invalid
		img->copyTo(*orgImg_);
		inputView_->showImage(orgImg_);
	}
}

bool MainGui::findTab(const QTabWidget* tabWidget, const QString& name, int& index)
{
	bool ret = true;

	index = -1;
	
	if (tabWidget && !name.isEmpty())
	{
		for (size_t i = 0; i < tabWidget->count(); i++)
		{
			if (tabWidget->tabText(i) == name)
			{
				index = i;
				break;
			}
		}
	}
	else
	{
		ret = false;
	}

	return ret;
}

void MainGui::addVerificationMethod(std::string name, VerificationMethod* method)
{
	logOutput("Adding method: " + QString::fromStdString(name));
	//Create an item and attach it to the widget
	MethodGuiItem* item = new MethodGuiItem(name, method->parameters(), ui_.groupBoxMethods);
	FrameView* preprocView = new FrameView(ui_.tabWidgetProcessed);
	FrameView* resView = new FrameView(ui_.tabWidgetResult);
	
	//Setup association
	methods_.insert(ItemMethodPair(item, method));
	//Add item to the layout
	ui_.groupBoxMethods->layout()->addWidget(item);

	ui_.tabWidgetProcessed->addTab(preprocView, QString::fromStdString(name));
	ui_.tabWidgetResult->addTab(resView, QString::fromStdString(name));
}

void MainGui::addMethodResults(const QString& methodName, const cv::Mat* resImg, const cv::Mat* preprocImg)
{
	int index;

	if (findTab(ui_.tabWidgetProcessed, methodName, index) && index >= 0)
	{
		static_cast<FrameView*>(ui_.tabWidgetProcessed->widget(index))->showImage(preprocImg);
	}
	else
	{
		logOutput("Could not find processed tab with name " + methodName + " and index: " + QString::number(index));
	}

	if (findTab(ui_.tabWidgetResult, methodName, index) && index >= 0)
	{
		static_cast<FrameView*>(ui_.tabWidgetResult->widget(index))->showImage(resImg);
	}
	else
	{
		logOutput("Could not find result tab with name " + methodName + " and index: " + QString::number(index));
	}
	
	ui_.tabWidgetProcessed->show();
	ui_.tabWidgetResult->show();
}

void MainGui::clearTabs()
{
	for (size_t i = 0; i < ui_.tabWidgetProcessed->count(); i++)
	{
		ui_.tabWidgetProcessed->removeTab(i);
		ui_.tabWidgetProcessed->widget(i)->deleteLater();
	}

	for (size_t i = 0; i < ui_.tabWidgetResult->count(); i++)
	{
		ui_.tabWidgetResult->removeTab(i);
		ui_.tabWidgetResult->widget(i)->deleteLater();
	}
}

void MainGui::runSelectedMethods()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	statusOutput("Run selected methods...");

	cv::Mat oldResult;

	// Look for all checked methods an execute them
	for (ItemMethodMap::iterator it = methods_.begin(); it != methods_.end(); it++)
	{
		if (it->first->selected())
		{
			QString methodName = QString::fromStdString(it->first->name());

			logOutput("Running method: " + methodName);
			//Get current parametrs from method
			it->second->setParameters(it->first->parameters());

			if (it->second->run(orgImg_))
			{
				logOutput("Method: " + methodName + " successful");		
				
				it->first->setMode(true);

				//Show imgs on gui
				//preprocView_->showImage(preprocImg_);
				addMethodResults(QString::fromStdString(it->first->name()), it->second->resultImg(), it->second->processed());
				//resultView_->showImage(resultImg_);

				resGenerator.setSettings(generateSettings());
				QStringList res = resGenerator.results(methodName, it->second->results());
				
				for (QStringList::iterator it = res.begin(); it != res.end(); it++)
				{
					ui_.listWidgetResults->addItem(*it);
				}
				ui_.listWidgetResults->addItem("");
			}
			else
			{
				//If method fails change appearance 
				it->first->setMode(false);
				logOutput("Method: " + methodName + " failed");
			}

		}
	}

	ui_.listWidgetResults->addItem("-------------------------------------------------------------------------");

	QApplication::restoreOverrideCursor();
	statusOutput("Selected methods completed");
}

void MainGui::addFileStream(QString stream)
{
	QStandardItemModel* model = static_cast<QStandardItemModel*>(ui_.treeViewInput->model());
	if (model)
	{
		//Add filename and filepath to the model
		QStandardItem* name = new QStandardItem(stream);

		logOutput("Adding Camera: " + stream);

		name->setEditable(false);

		name->setData(stream, Qt::DisplayRole);

		model->appendRow(name);
	}
}

void MainGui::addFile()
{
	QFileDialog dialog(this);
	QStringList filenames;

	QString filter = "Images(*.png *.bmp *.jpg *.jpeg)";
	
	filenames = dialog.getOpenFileNames(this, "Select an image", QString(), filter);

	QStandardItemModel* model = static_cast<QStandardItemModel*>(ui_.treeViewInput->model());

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

			//resize the header to path length
			QFont font;
			QFontMetrics metrics(font.family());
			QRect rect = metrics.boundingRect(fileInfo.filePath());

			if (ui_.treeViewInput->header()->length() < rect.width())
			{
				ui_.treeViewInput->header()->resizeSection(1, rect.width());
			}
		}
	}
	//Select last added file
	QModelIndex index = model->index(model->rowCount() - 1, model->columnCount() - 1);
	ui_.treeViewInput->setCurrentIndex(index);
	setCurrentFile(index);
}

void MainGui::removeFile()
{
	logOutput("Removing last file");
	QModelIndexList selection = ui_.treeViewInput->selectionModel()->selectedRows();

	// Multiple rows can be selected
	for (int i = 0; i < selection.count(); i++)
	{
		QModelIndex index = selection.at(i);
		ui_.treeViewInput->model()->removeRow(index.row());
	}

	if (io_)
	{
		io_->terminateCameraStream();
	}

	reset();
}

void MainGui::setCurrentFile(QModelIndex index)
{
	//Cast from QAbstractItemModel to QStandardItemModel to have full functionality
	QStandardItem* path = static_cast<QStandardItemModel*>(ui_.treeViewInput->model())->item(index.row(), 1);
	QStandardItem* name = static_cast<QStandardItemModel*>(ui_.treeViewInput->model())->item(index.row(), 0);
	cv::Mat img;

	//Check if cast was successful
	if (path || name)
	{
		//stop camera 
		io_->terminateCameraStream();
		//Get the file path
		if (path)
		{
			currentFile_ = path->data(Qt::DisplayRole).value<QString>();
		}
		else
		{
			currentFile_.clear();
		}

		if (currentFile_.isEmpty() == false) 
		{
			// Camera image has no file
			logOutput("Using current file: " + currentFile_);
		}

		if (currentFile_.isEmpty())
		{
			io_->setCamera(name->data(Qt::DisplayRole).value<QString>().toStdString());
			std::thread ioThread(&UpldFrame::fromCamera, io_);
			ioThread.detach();
		}
		else
		{
			img = UpldFrame::fromFile(currentFile_.toStdString());
		}

		statusOutput("Image loaded");

		setInputImage(&img);
	}
}

void MainGui::reset()
{
	orgImg_->release();
}

void MainGui::logOutput(QString msg)
{
	if (msg.isEmpty() == false)
	{
		QString str = "[" + QTime::currentTime().toString() + "]: " + msg;
		ui_.listWidgetLog->addItem(str);
	}
}

void MainGui::statusOutput(QString msg)
{
	if (msg.isEmpty() == false)
	{
		ui_.labelProgress->setText(msg);
	}
}

void MainGui::openOptions()
{
	options_->show();
}

ResultGenerator::SettingsMap MainGui::generateSettings()
{
	ResultGenerator::SettingsMap map;
	Parameter param;
	
	param.setUp("Real circle radius", options_->holeRadius(), QMetaType::Double);
	map.insert(ResultGenerator::SettingsPair(ResultGenerator::Settings::SET_CIRCLE_RADIUS, param));

	param.setUp("Real angle", options_->angle(), QMetaType::Double);
	map.insert(ResultGenerator::SettingsPair(ResultGenerator::Settings::SET_OBJ_ANGLE, param));

	QVariantList metrics = options_->objMetrics();
	QSize size(metrics.at(0).toDouble(), metrics.at(1).toDouble());
	param.setUp("Real object size", size, QVariant::Size);
	map.insert(ResultGenerator::SettingsPair(ResultGenerator::Settings::SET_OBJ_METRICS, param));

	size = options_->referenceSize();
	param.setUp("Real reference size", size, QVariant::Size);
	map.insert(ResultGenerator::SettingsPair(ResultGenerator::Settings::SET_REF_SIZE, param));

	return map;
}