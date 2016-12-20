#include "OptionsGui.h"
#include "ConfigurationStorage.h"
#include "Configs.h"
#include "CLogger.h"

#include <QDir>
#include <QPushButton>
#include <QFileDialog>

OptionsGui::OptionsGui(QWidget* parent)
	:QMainWindow(parent)
{
	QVariant value;

	ui_.setupUi(this);

	configFile_ = paths::getExecutablePath() + "\\" + paths::configFolder + filenames::optionsName;
	
	if (ConfigurationStorage::instance().exists(configFile_))
	{
		if (ConfigurationStorage::instance().read(configFile_, "object_width", QMetaType::Double, value))
		{
			objSize_.setWidth(value.toDouble());
		}
		else
		{
			LOGGER->Log("Can not read object_width from %s", configFile_);
		}

		if (ConfigurationStorage::instance().read(configFile_, "object_length", QMetaType::Double, value))
		{
			objSize_.setHeight(value.toDouble());
		}
		else
		{
			LOGGER->Log("Can not read object_length from %s", configFile_);
		}
		
		if (ConfigurationStorage::instance().read(configFile_, "object_hole_radius", QMetaType::Double, value))
		{
			holeRadius_ = value;
		}
		else
		{
			LOGGER->Log("Can not read object_hole_radius from %s", configFile_);
		}

		if (ConfigurationStorage::instance().read(configFile_, "object_side_angle", QMetaType::Double, value))
		{
			angle_ = value;
		}
		else
		{
			LOGGER->Log("Can not read object_side_angle from %s", configFile_);
		}
		
		if (ConfigurationStorage::instance().read(configFile_, "camera_config_path", QVariant::String, value))
		{
			cameraConfig_ = value.toString().toStdString();
		}
		else
		{
			LOGGER->Log("Can not read camera_config_path from %s", configFile_);
		}
	}
	else
	{
		LOGGER->Log("%s does not exist. File will be created at same destination", configFile_);
	}
	
	QPushButton* save = ui_.buttonBoxOptions->button(QDialogButtonBox::Save);
	QPushButton* cancel = ui_.buttonBoxOptions->button(QDialogButtonBox::Cancel);

	//Connect the signals from the button box to other functions
	QObject::connect(save, &QPushButton::clicked, this, &OptionsGui::saveValues);
	QObject::connect(cancel, &QPushButton::clicked, this, &OptionsGui::closeClicked);
	QObject::connect(ui_.pushButtonOpen, &QPushButton::clicked, this, &OptionsGui::selectPathClicked);

	setValues();
}

OptionsGui::~OptionsGui()
{
}

void OptionsGui::setValues()
{
	ui_.doubleSpinBoxWidth->setValue(objSize_.width());
	ui_.doubleSpinBoxLength->setValue(objSize_.height());

	ui_.doubleSpinBoxDiameter->setValue(holeRadius_.toDouble());
	ui_.doubleSpinBoxAngle->setValue(angle_.toDouble());

	ui_.lineEditConfig->setText(QString::fromStdString(cameraConfig_));
}

void OptionsGui::selectPathClicked()
{
	QFileDialog dialog(this);
	QString filename;
	QString filter = "Configuration Files(*.ini)";

	filename = dialog.getOpenFileName(this, "Select an image", QString::fromStdString(paths::configFolder), filter);

	ui_.lineEditConfig->setText(filename);
	cameraConfig_ = filename.toStdString();
}

void OptionsGui::closeClicked()
{
	setValues();
	close();
}

void OptionsGui::saveValues()
{
	objSize_.setWidth(ui_.doubleSpinBoxWidth->value());
	objSize_.setHeight(ui_.doubleSpinBoxLength->value());

	holeRadius_ = ui_.doubleSpinBoxDiameter->value();
	angle_ = ui_.doubleSpinBoxAngle->value();

	cameraConfig_ = ui_.lineEditConfig->text().toStdString();

	if (!ConfigurationStorage::instance().write(configFile_, "object_width", objSize_.width()))
	{
		LOGGER->Log("Can not write object_width to %s", configFile_);
	}

	if (!ConfigurationStorage::instance().write(configFile_, "object_length", objSize_.height()))
	{
		LOGGER->Log("Can not write object_length to %s", configFile_);
	}

	if (!ConfigurationStorage::instance().write(configFile_, "object_hole_radius", holeRadius_))
	{
		LOGGER->Log("Can not write object_hole_radius to %s", configFile_);
	}

	if (!ConfigurationStorage::instance().write(configFile_, "object_side_angle", angle_))
	{
		LOGGER->Log("Can not write object_side_angle to %s", configFile_);
	}

	if (!ConfigurationStorage::instance().write(configFile_, "camera_config_path", QString::fromStdString(cameraConfig_)))
	{
		LOGGER->Log("Can not write camera_config_path to %s", configFile_);
	}

	ConfigurationStorage::instance().realease();

	close();
}

QSize OptionsGui::objSize()
{
	return objSize_;
}

QVariant OptionsGui::holeRadius()
{
	return holeRadius_;
}

QVariant OptionsGui::angle()
{
	return angle_;
}

std::string OptionsGui::cameraConfigPath()
{
	return configFile_;
}
