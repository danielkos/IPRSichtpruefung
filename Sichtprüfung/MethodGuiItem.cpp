#include "MethodGuiItem.h"
#include <QString>
#include <QLineEdit>
#include <QComboBox>

MethodGuiItem::MethodGuiItem(std::string name, std::vector<Parameter>& parameters, QWidget* parent)
	: QWidget(parent), name_(name), parameters_(parameters)
{
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

	//Connections to manage inputs and selection of parameters
	QObject::connect(ui_.comboBoxParams, SIGNAL(currentIndexChanged(int)), this, SLOT(paramIndexChanged(int)));
	QObject::connect(ui_.lineEditNumInput, SIGNAL(textEdited(QString)), this, SLOT(paramInputChanged(QString)));
	QObject::connect(ui_.radioButtonBoolInput, SIGNAL(toggled(bool)), this, SLOT(paramInputChanged(bool)));
	QObject::connect(ui_.groupBoxMethod, &QGroupBox::toggled, this, &MethodGuiItem::changeToNormal);
}

MethodGuiItem::~MethodGuiItem()
{
	
}

void MethodGuiItem::paramIndexChanged(int index)
{
	changeParams(index);
}

void MethodGuiItem::paramInputChanged(const QString& input)
{
	int index = ui_.comboBoxParams->currentIndex();
	parameters_[index].value_ = input;
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
		ui_.lineEditNumInput->setVisible(true);
		ui_.lineEditNumInput->setText(parameters_[index].value_.toString());
		break;
	case QMetaType::Int:
		ui_.radioButtonBoolInput->setVisible(false);
		ui_.lineEditNumInput->setVisible(true);
		ui_.lineEditNumInput->setText(parameters_[index].value_.toString());
		break;
	case QMetaType::Bool:
		ui_.lineEditNumInput->setVisible(false);
		ui_.radioButtonBoolInput->setVisible(true);
		ui_.radioButtonBoolInput->setChecked(parameters_[index].value_.toBool());
		ui_.radioButtonBoolInput->setText(parameters_[index].value_.toBool() ? "Enabled" : "Disabled");
		break;
	default:
		ui_.lineEditNumInput->setVisible(false);
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