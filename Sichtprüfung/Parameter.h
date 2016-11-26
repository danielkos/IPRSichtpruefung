#ifndef PARAMETER_H
#define PARAMETER_H

#include <QVariant>
/**
* \brief Represents a parameter shared between mehtod and gui
*/
struct Parameter
{
	QString name_;
	QVariant value_;
	int type_;

	Parameter()
		: name_(""), value_(0), type_(QMetaType::UnknownType)
	{
	}

	void setUp(QString name, QVariant value, int type)
	{
		name_ = name;
		value_ = value;
		type_ = type;
	}

};

#endif

