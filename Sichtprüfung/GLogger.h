#ifndef GLOGGRER
#define GLOGGER

#include <QString>

class QListWidget;

#define GLOG GLogger::instance()

class GLogger
{
public:
	void log(const QString& msg);

	void log(const char* format, ...);

	void setListWidget(QListWidget* widget);
	
	static GLogger& instance();
private:
	GLogger();

	QListWidget* listWidget_;

};
#endif // !GLOGGRER
