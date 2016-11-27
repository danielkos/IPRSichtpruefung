#include "OptionsGui.h"
#include <QPushButton>

OptionsGui::OptionsGui(QWidget* parent)
	:QMainWindow(parent)
{
	ui_.setupUi(this);

	objMetrics_.push_back(4.1);
	objMetrics_.push_back(3.9);
	objMetrics_.push_back(0.5);

	referenceSize_.setWidth(4.1);
	referenceSize_.setHeight(3.9);
	
	holeRadius_ = 0.4;
	angle_ = 5;

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