#include "Logger.h"
#include "CLogger.h"
#include "GLogger.h"

Logger::Logger()
{

}

void Logger::log(const QString& msg)
{
	GLOG.log(msg);
	TLOG->log(msg.toStdString());
}

void Logger::log(const std::string& msg)
{
	GLOG.log(QString::fromStdString(msg));
	TLOG->log(msg);
}

void Logger::log(const char * msg)
{
	GLOG.log(QString::fromStdString(msg));
	TLOG->log(msg);
}

Logger& Logger::instance()
{
	static Logger logger;
	return logger;
}