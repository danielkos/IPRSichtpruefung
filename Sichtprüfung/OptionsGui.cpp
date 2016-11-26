#include "OptionsGui.h"
#include <QPushButton>

OptionsGui::OptionsGui(QWidget* parent)
	:QMainWindow(parent)
{
	ui_.setupUi(this);

	size_.push_back(4.1);
	size_.push_back(3.9);
	size_.push_back(0.5);

	referenceSize_.push_back(4.1);
	referenceSize_.push_back(3.9);
	
	holeDiameter_ = 0.4;
	angle_ = 5;

	ui_.doubleSpinBoxWidth->setValue(size_[0]);
	ui_.doubleSpinBoxLength->setValue(size_[1]);
	ui_.doubleSpinBoxHeight->setValue(size_[2]);

	ui_.doubleSpinBoxDiameter->setValue(holeDiameter_);
	ui_.doubleSpinBoxAngle->setValue(angle_);

	ui_.doubleSpinBoxRefWidth->setValue(referenceSize_[0]);
	ui_.doubleSpinBoxRefHeight->setValue(referenceSize_[0]);

	QPushButton* save = ui_.buttonBoxOptions->button(QDialogButtonBox::Save);
	QPushButton* discard = ui_.buttonBoxOptions->button(QDialogButtonBox::Cancel);

	//Connect the signals from the button box to other functions
	connect(save, &QPushButton::clicked, this, &OptionsGui::saveValues);
	connect(discard, &QPushButton::clicked, this, &QWidget::close);

	setAttribute(Qt::WA_DeleteOnClose);

	show();
}

OptionsGui::~OptionsGui()
{
}

void OptionsGui::saveValues()
{
	size_[0] = ui_.doubleSpinBoxWidth->value();
	size_[1] = ui_.doubleSpinBoxLength->value();
	size_[2] = ui_.doubleSpinBoxHeight->value();

	holeDiameter_ = ui_.doubleSpinBoxDiameter->value();
	angle_ = ui_.doubleSpinBoxAngle->value();

	close();
}

std::vector<double> OptionsGui::size()
{
	return size_;
}

std::vector<double> OptionsGui::referenceSize()
{
	return referenceSize_;
}

double OptionsGui::holeDiameter()
{
	return holeDiameter_;
}

double OptionsGui::angle()
{
	return angle_;
}