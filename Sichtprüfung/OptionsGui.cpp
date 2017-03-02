#include "OptionsGui.h"
#include "ConfigurationStorage.h"
#include "Configs.h"
#include "Logger.h"

#include <QDir>
#include <QPushButton>
#include <QFileDialog>

OptionsGui::OptionsGui(QWidget* parent)
	:QMainWindow(parent)
{
	QVariant value;

	ui_.setupUi(this);

	getValues();

	configFile_ = paths::getExecutablePath() + paths::configFolder + filenames::optionsName + extensions::optionsExt;
	
	if (ConfigurationStorage::instance().exists(configFile_))
	{
		LOGGER.log("Reading file: " + configFile_);

		if (ConfigurationStorage::instance().read(configFile_, "object_width", value))
		{
			objSize_.setWidth(value.toDouble());
		}
		else
		{
			LOGGER.log("Can not read object_width from " + configFile_);
		}

		if (ConfigurationStorage::instance().read(configFile_, "object_length", value))
		{
			objSize_.setHeight(value.toDouble());
		}
		else
		{
			LOGGER.log("Can not read object_length from " + configFile_);
		}
		
		if (ConfigurationStorage::instance().read(configFile_, "object_hole_radius", value))
		{
			holeRadius_ = value;
		}
		else
		{
			LOGGER.log("Can not read object_hole_radius from " + configFile_);
		}

		if (ConfigurationStorage::instance().read(configFile_, "object_side_angle", value))
		{
			angle_ = value;
		}
		else
		{
			LOGGER.log("Can not read object_side_angle from " + configFile_);
		}

		if (ConfigurationStorage::instance().read(configFile_, "use_calibration", value))
		{
			useCalibration_ = value.toBool();
		}
		else
		{
			LOGGER.log("Can not read use_calibration from " + configFile_);
		}
		
		if (ConfigurationStorage::instance().read(configFile_, "camera_config_path", value))
		{
			cameraConfig_ = value.toString().toStdString();
		}
		else
		{
			LOGGER.log("Can not read camera_config_path from " + configFile_);
			cameraConfig_ = paths::getExecutablePath() + paths::configFolder + paths::cameraFolder + filenames::cameraConfig + extensions::cameraConfigExt;
		}
		setValues();
	}
	else
	{
		LOGGER.log(configFile_ + " does not exist. Directory could not be created. Please restart with administrative rights!");
	}
	
	QPushButton* save = ui_.buttonBoxOptions->button(QDialogButtonBox::Save);
	QPushButton* cancel = ui_.buttonBoxOptions->button(QDialogButtonBox::Cancel);

	//Connect the signals from the button box to other functions
	QObject::connect(save, &QPushButton::clicked, this, &OptionsGui::saveValues);
	QObject::connect(cancel, &QPushButton::clicked, this, &OptionsGui::closeClicked);
	QObject::connect(ui_.pushButtonOpen, &QPushButton::clicked, this, &OptionsGui::selectPathClicked);

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
	ui_.checkBoxCalibration->setChecked(useCalibration_);

	ui_.lineEditConfig->setText(QString::fromStdString(cameraConfig_));
}

void OptionsGui::getValues()
{
	objSize_.setWidth(ui_.doubleSpinBoxWidth->value());
	objSize_.setHeight(ui_.doubleSpinBoxLength->value());

	holeRadius_ = ui_.doubleSpinBoxDiameter->value();
	angle_ = ui_.doubleSpinBoxAngle->value();
	useCalibration_ = ui_.checkBoxCalibration->isChecked();

	cameraConfig_ = ui_.lineEditConfig->text().toStdString();
}

void OptionsGui::selectPathClicked()
{
	QFileDialog dialog(this);
	QString filename;
	QString filter = "Configuration Files(*" + QString::fromStdString(extensions::optionsExt) + ")";
	std::string path = paths::getExecutablePath() + paths::configFolder;
	filename = dialog.getOpenFileName(this, "Select an image", QString::fromStdString(path), filter);

	if (!filename.isEmpty())
	{
		ui_.lineEditConfig->setText(filename);
	}
	
	cameraConfig_ = filename.toStdString();
}

void OptionsGui::closeClicked()
{
	close();
}

void OptionsGui::saveValues()
{
	objSize_.setWidth(ui_.doubleSpinBoxWidth->value());
	objSize_.setHeight(ui_.doubleSpinBoxLength->value());

	holeRadius_ = ui_.doubleSpinBoxDiameter->value();
	angle_ = ui_.doubleSpinBoxAngle->value();

	useCalibration_ = ui_.checkBoxCalibration->isChecked();

	cameraConfig_ = ui_.lineEditConfig->text().toStdString();

	if (!ConfigurationStorage::instance().write(configFile_, "object_width", objSize_.width()))
	{
		LOGGER.log("Can not write object_width to " + configFile_);
	}

	if (!ConfigurationStorage::instance().write(configFile_, "object_length", objSize_.height()))
	{
		LOGGER.log("Can not write object_length to " + configFile_);
	}

	if (!ConfigurationStorage::instance().write(configFile_, "object_hole_radius", holeRadius_))
	{
		LOGGER.log("Can not write object_hole_radius to " + configFile_);
	}

	if (!ConfigurationStorage::instance().write(configFile_, "object_side_angle", angle_))
	{
		LOGGER.log("Can not write object_side_angle to " + configFile_);
	}

	if (!ConfigurationStorage::instance().write(configFile_, "use_calibration", useCalibration_))
	{
		LOGGER.log("Can not write camera_config_path to " + configFile_);
	}

	if (!ConfigurationStorage::instance().write(configFile_, "camera_config_path", QString::fromStdString(cameraConfig_)))
	{
		LOGGER.log("Can not write camera_config_path to " + configFile_);
	}

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

bool OptionsGui::useCalibration()
{
	return useCalibration_;
}

std::string OptionsGui::cameraConfigPath()
{
	return configFile_;
}
