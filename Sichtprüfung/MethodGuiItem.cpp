#include "MethodGuiItem.h"
#include <QString>

MethodGuiItem::MethodGuiItem(std::string name, QWidget* parent)
	: QCheckBox(parent)
{
	this->setText(QString::fromStdString(name));
}

MethodGuiItem::~MethodGuiItem()
{
	
}

bool MethodGuiItem::selected()
{
	return isChecked();
}