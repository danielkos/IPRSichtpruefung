#include "GLogger.h"

#include <string>
#include <cstdarg>

#include <QListWidget>
#include <QTime>

GLogger::GLogger()
{
	listWidget_ = NULL;
}

GLogger& GLogger::instance()
{
	static GLogger logger;
	return logger;
}

void GLogger::setListWidget(QListWidget* widget)
{
	listWidget_ = widget;
}

void GLogger::log(const QString& msg)
{
	if (!msg.isEmpty() && listWidget_)
	{
		QString str = "[" + QTime::currentTime().toString() + "]: " + msg;
		listWidget_->addItem(str);
	}
}

void GLogger::log(const char* format, ...)
{
	char* sMessage = NULL;
	int nLength = 0;
	va_list args;
	va_start(args, format);
	//  Return the number of characters in the string referenced the list of arguments.
	// _vscprintf doesn't count terminating '\0' (that's why +1)
	nLength = _vscprintf(format, args) + 1;
	sMessage = new char[nLength];
	vsprintf_s(sMessage, nLength, format, args);
	va_end(args);

	QString msg = QString::fromStdString(sMessage);
	log(msg);

	delete[] sMessage;
}