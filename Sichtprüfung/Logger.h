#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

#define LOGGER Logger::instance()

class Logger
{
public:
	static Logger& instance();

	void log(const QString& msg);
	void log(const std::string& msg);
	void log(const char* msg);
private:
	Logger();

};
#endif // ! LOGGER
