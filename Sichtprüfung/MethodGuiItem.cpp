#include "MethodGuiItem.h"

#include "Configs.h"
#include "ConfigurationStorage.h"

#include <QFileDialog>
#include <QToolButton>
#include <QPushButton>
#include <QString>
#include <QLineEdit>
#include <QComboBox>

MethodGuiItem::MethodGuiItem(std::string name, std::vector<Parameter>& parameters, QWidget* parent)
	: QWidget(parent), name_(name), fileName_(name), parameters_(parameters)
{
	//fileName_.erase(std::remove_if(fileName_.begin(), fileName_.end(), std::isspace), fileName_.end());
	ui_.setupUi(this);
	ui_.groupBoxMethod->setTitle(QString::fromStdString(name));
	
	//Add paramters to dropdown
	for (size_t i = 0; i < parameters_.size(); i++)
	{
		ui_.comboBoxParams->addItem(parameters_[i].name_, parameters_[i].value_);
	}

	//Set first parameter
	ui_.comboBoxParams->setCurrentIndex(0);
	changeParams(0);

	baseDir_ = paths::getExecutablePath() + paths::configFolder + paths::profilesFolder + filenames::profilesConfig + extensions::profileExt;
	bool profile = false;

	if (ConfigurationStorage::instance().exists(baseDir_))
	{
		QVariant value;

		if (ConfigurationStorage::instance().read(baseDir_, fileName_, value))
		{
			loadProfile(value.toString().toStdString());
			profile = true;
		}

		baseDir_ = paths::getExecutablePath() + paths::configFolder + paths::profilesFolder + fileName_ + "\\";
		
	}

	if(!profile)
	{
		baseDir_ = paths::getExecutablePath() + paths::configFolder + paths::profilesFolder + fileName_ + "\\";

		if (ConfigurationStorage::instance().exists(baseDir_ + fileName_ + extensions::profileExt))
		{
			std::string path = baseDir_ + fileName_ + extensions::profileExt;
			loadProfile(path);
		}
		else
		{
			LOGGER.log(baseDir_ + " does not exist. File will be created at same destination");

			bool exists;
			bool ret = paths::createDir(baseDir_, exists);

			if (!ret && exists)
			{
				LOGGER.log("Reusing directory: " + baseDir_);
			}
			else if (ret)
			{
				LOGGER.log("Directory: " + baseDir_ + "  created");
			}
			else if (!ret && !exists)
			{
				LOGGER.log("Unknown error while creating directory: " + baseDir_);
			}
		}
	}
	
	//Try editingFinished
	//Connections to manage inputs and selection of parameters
	QObject::connect(ui_.comboBoxParams, SIGNAL(currentIndexChanged(int)), this, SLOT(paramIndexChanged(int)));
	//QObject::connect(ui_.doubleSpinBoxNumInput, SIGNAL(valueChanged(double)), this, SLOT(paramInputChanged(double)));
	//QObject::connect(ui_.spinBoxNumInput, SIGNAL(valueChanged(int)), this, SLOT(paramInputChanged(int)));
	QObject::connect(ui_.doubleSpinBoxNumInput, SIGNAL(editingFinished()), this, SLOT(paramInputChanged()));
	QObject::connect(ui_.spinBoxNumInput, SIGNAL(editingFinished()), this, SLOT(paramInputChanged()));
	QObject::connect(ui_.radioButtonBoolInput, SIGNAL(toggled(bool)), this, SLOT(paramInputChanged(bool)));
	QObject::connect(ui_.groupBoxMethod, &QGroupBox::toggled, this, &MethodGuiItem::changeToNormal);
	QObject::connect(ui_.openProfileButton, &QToolButton::clicked, this, &MethodGuiItem::loadProfileClicked);
	QObject::connect(ui_.pushButtonSaveProfile, &QPushButton::clicked, this, &MethodGuiItem::saveProfileClicked);
}

MethodGuiItem::~MethodGuiItem()
{
	
}

void MethodGuiItem::paramIndexChanged(int index)
{
	changeParams(index);
}

void MethodGuiItem::paramInputChanged()
{
	int index = ui_.comboBoxParams->currentIndex();
	switch (parameters_[index].type_)
	{
	case QMetaType::Double:
		parameters_[index].value_ = ui_.doubleSpinBoxNumInput->value();
		break;
	case QMetaType::Int:
		parameters_[index].value_ = ui_.spinBoxNumInput->value();
		break;
	case QMetaType::Bool:
		parameters_[index].value_ = ui_.radioButtonBoolInput->isChecked();
		break;
	}
}

void MethodGuiItem::paramInputChanged(const double& input)
{
	int index = ui_.comboBoxParams->currentIndex();
	QVariant value = input;
	//value.convert(parameters_[index].type_);
	parameters_[index].value_ = value;

	changeParams(index);
}

void MethodGuiItem::paramInputChanged(const int& input)
{
	int index = ui_.comboBoxParams->currentIndex();
	QVariant value = input;
	//value.convert(parameters_[index].type_);
	parameters_[index].value_ = value;

	changeParams(index);
}

void MethodGuiItem::paramInputChanged(bool input)
{
	int index = ui_.comboBoxParams->currentIndex();
	parameters_[index].value_ = input;
	changeParams(index);
}

bool MethodGuiItem::selected()
{
	return ui_.groupBoxMethod->isChecked();
}

std::string MethodGuiItem::name()
{
	return name_;
}

std::vector<Parameter>& MethodGuiItem::parameters()
{
	return parameters_;
}

void MethodGuiItem::setMode(bool successful)
{
	if (successful)
	{
		ui_.groupBoxMethod->setStyleSheet("#groupBoxMethod{ border: 3px solid green;  }");
	}
	else
	{
		ui_.groupBoxMethod->setStyleSheet("#groupBoxMethod{ border: 3px solid red; }");
	}
}

void MethodGuiItem::changeParams(int index)
{
	switch (parameters_[index].type_)
	{
	case QMetaType::Double:
		ui_.radioButtonBoolInput->setVisible(false);
		ui_.spinBoxNumInput->setVisible(false);
		ui_.doubleSpinBoxNumInput->setVisible(true);
		ui_.doubleSpinBoxNumInput->setValue(parameters_[index].value_.toDouble());
		ui_.doubleSpinBoxNumInput->show();
		break;
	case QMetaType::Int:
		ui_.radioButtonBoolInput->setVisible(false);
		ui_.doubleSpinBoxNumInput->setVisible(false);
		ui_.spinBoxNumInput->setVisible(true);
		ui_.spinBoxNumInput->setValue(parameters_[index].value_.toInt());
		ui_.spinBoxNumInput->show();
		break;
	case QMetaType::Bool:
		ui_.doubleSpinBoxNumInput->setVisible(false);
		ui_.spinBoxNumInput->setVisible(false);
		ui_.radioButtonBoolInput->setVisible(true);
		ui_.radioButtonBoolInput->setChecked(parameters_[index].value_.toBool());
		ui_.radioButtonBoolInput->setText(parameters_[index].value_.toBool() ? "Enabled" : "Disabled");
		ui_.radioButtonBoolInput->show();
		break;
	default:
		ui_.doubleSpinBoxNumInput->setVisible(false);
		ui_.radioButtonBoolInput->setVisible(false);
		break;
	}
}

void MethodGuiItem::changeToNormal(bool toggled)
{
	if (!toggled)
	{
		ui_.groupBoxMethod->setStyleSheet("");
	}
}

void MethodGuiItem::loadProfileClicked()
{
	QFileDialog dialog(this);
	QString filename;
	QString filter = "Configuration Files(*" + QString::fromStdString(extensions::profileExt) + ")";
	filename = dialog.getOpenFileName(this, "Open profile", QString::fromStdString(baseDir_), filter);
	
	if (!filename.isEmpty())
	{
		loadProfile(filename.toStdString());
	}

	ui_.comboBoxParams->setCurrentIndex(0);
	changeParams(0);
}

void MethodGuiItem::loadProfile(const std::string& profilePath)
{
	LOGGER.log("Reading file: " + profilePath);
	QVariant value;

	for (size_t i = 0; i < parameters_.size(); i++)
	{
		if (ConfigurationStorage::instance().read(profilePath, parameters_[i].name_.toStdString(), value))
		{			
			parameters_[i].value_ = value;
			changeParams(i);
		}
		else
		{
			LOGGER.log("Cannot read parameter " + parameters_[i].name_ + " for method " + QString::fromStdString(name_) + " from " + QString::fromStdString(profilePath));
			ui_.lineEditProfile->setText("");
			break;
		}
		if (i == parameters_.size() - 1)
		{
			ui_.lineEditProfile->setText(QString::fromStdString(profilePath));
		}
	}	
}

void MethodGuiItem::saveProfileClicked()
{
	QFileDialog dialog(this);
	QString filename;
	QString filter = "Configuration Files(*" + QString::fromStdString(extensions::profileExt) + ")";
	std::string path = baseDir_ + fileName_ + extensions::profileExt;
	filename = dialog.getSaveFileName(this, "Save current profile", QString::fromStdString(path), filter);
	bool error = false;

	if (!filename.isEmpty())
	{
		for (size_t i = 0; i < parameters_.size(); i++)
		{
			if (!ConfigurationStorage::instance().write(filename.toStdString(), parameters_[i].name_.toStdString(), parameters_[i].value_))
			{
				LOGGER.log("Cannot write parameter " + parameters_[i].name_ + " for method " + QString::fromStdString(name_) + " to " + filename);
				error = true;
			}
		}
	}
	if(!error && !filename.isEmpty())
	{
		ui_.lineEditProfile->setText(filename);
		LOGGER.log("Saved file " + path);

		path = paths::getExecutablePath() + paths::configFolder + paths::profilesFolder + filenames::profilesConfig + extensions::profileExt;

		if (!ConfigurationStorage::instance().write(path, fileName_, filename))
		{
			LOGGER.log("Cannot write profile path " + filename.toStdString() + " for method " + name_ + " to " + path);
		}
	}
	
}