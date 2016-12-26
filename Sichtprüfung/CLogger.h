#ifndef CLogger_H
#define CLogger_H

#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>

using namespace std;

#define TLOG CLogger::GetLogger()

/**
Implements a simple logger that logs the given output to a file on the local
file system. Used name for log file: log.txt (can be changed in CLogger.cpp)

The log file is stored inside the project folder of the project.
This class implements the singleton software pattern to make sure that all
classes log their output to the same file.

Source: https://cppcodetips.wordpress.com/2014/01/02/a-simple-logger-class-in-c/

Example usage in any class:
1) Include log file:
#include "CLogger.h"


2) Log any text:
LogCLogger::GetLogger()->Log("Message to log");
Or
LOGGER->Log("Message to log with a number: %d", number);

*/
class CLogger
{
public:
	/**
	*   Logs a message
	*   @param sMessage message to be logged.
	*/
	void log(const std::string& sMessage);
	/**
	*   Variable Length Logger function
	*   @param format string for the message to be logged.
	*/
	void log(const char * format, ...);
	/**
	*   << overloaded function to Logs a message
	*   @param sMessage message to be logged.
	*/
	CLogger& operator<<(const string& sMessage);
	/**
	*   Funtion to create the instance of logger class.
	*   @return singleton object of Clogger class..
	*/
	static CLogger* GetLogger();
private:
	/**
	*    Default constructor for the Logger class.
	*/
	CLogger();
	/**
	*   copy constructor for the Logger class.
	*/
	CLogger(const CLogger&) {};             // copy constructor is private
											/**
											*   assignment operator for the Logger class.
											*/
	CLogger& operator=(const CLogger&) { return *this; };  // assignment operator is private
														   /**
														   *   Log file name.
														   **/
	static const std::string m_sFileName;

	/**
	*   Singleton logger class object pointer.
	**/
	static CLogger* m_pThis;
	/**
	*   Log file stream object.
	**/
	static ofstream m_Logfile;
};
#endif