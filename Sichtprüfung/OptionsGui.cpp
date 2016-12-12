#include "OptionsGui.h"
#include "ConfigurationStorage.h"

#include <QPushButton>

OptionsGui::OptionsGui(QWidget* parent, const std::string& configFile)
	:QMainWindow(parent)
{
	QVariant value;

	ui_.setupUi(this);

	if (configFile.empty())
	{
		configFile_ = "options.xml";
	}
	else
	{
		configFile_ = configFile;
	}

	ConfigurationStorage::instance().read(configFile_, "object_width", QMetaType::Double, value);
	objMetrics_.push_back(value);
	ConfigurationStorage::instance().read(configFile_, "object_length", QMetaType::Double, value);
	objMetrics_.push_back(value);
	ConfigurationStorage::instance().read(configFile_, "object_height", QMetaType::Double, value);
	objMetrics_.push_back(value);

	referenceSize_.setWidth(4.1);
	referenceSize_.setHeight(3.9);
	
	ConfigurationStorage::instance().read(configFile_, "object_hole_radius", QMetaType::Double, value);
	holeRadius_ = value;
	ConfigurationStorage::instance().read(configFile_, "object_side_angle", QMetaType::Double, value);
	angle_ = value;

	QPushButton* save = ui_.buttonBoxOptions->button(QDialogButtonBox::Save);
	QPushButton* cancel = ui_.buttonBoxOptions->button(QDialogButtonBox::Cancel);

	//Connect the signals from the button box to other functions
	connect(save, &QPushButton::clicked, this, &OptionsGui::saveValues);
	connect(cancel, &QPushButton::clicked, this, &OptionsGui::closeClicked);

	setValues();
}

OptionsGui::~OptionsGui()
{
}

void OptionsGui::setValues()
{
	ui_.doubleSpinBoxWidth->setValue(objMetrics_[0].toDouble());
	ui_.doubleSpinBoxLength->setValue(objMetrics_[1].toDouble());
	ui_.doubleSpinBoxHeight->setValue(objMetrics_[2].toDouble());

	ui_.doubleSpinBoxDiameter->setValue(holeRadius_.toDouble());
	ui_.doubleSpinBoxAngle->setValue(angle_.toDouble());

	ui_.doubleSpinBoxRefWidth->setValue(referenceSize_.width());
	ui_.doubleSpinBoxRefHeight->setValue(referenceSize_.height());
}

void OptionsGui::closeClicked()
{
	setValues();
	close();
}
void OptionsGui::saveValues()
{
	objMetrics_[0] = ui_.doubleSpinBoxWidth->value();
	objMetrics_[1] = ui_.doubleSpinBoxLength->value();
	objMetrics_[2] = ui_.doubleSpinBoxHeight->value();

	holeRadius_ = ui_.doubleSpinBoxDiameter->value();
	angle_ = ui_.doubleSpinBoxAngle->value();

	ConfigurationStorage::instance().write(configFile_, "object_width", objMetrics_[0]);
	ConfigurationStorage::instance().write(configFile_, "object_length", objMetrics_[1]);
	ConfigurationStorage::instance().write(configFile_, "object_height", objMetrics_[2]);
	ConfigurationStorage::instance().write(configFile_, "object_hole_radius", holeRadius_);
	ConfigurationStorage::instance().write(configFile_, "object_side_angle", angle_);
	ConfigurationStorage::instance().realease();

	close();
}

QVariantList OptionsGui::objMetrics()
{
	return objMetrics_;
}

QSize OptionsGui::referenceSize()
{
	return referenceSize_;
}

QVariant OptionsGui::holeRadius()
{
	return holeRadius_;
}

QVariant OptionsGui::angle()
{
	return angle_;
}