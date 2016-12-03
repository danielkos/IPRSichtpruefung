#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <time.h>

/*
Simple helper class for Logger.cpp class. Defines a time format.
*/
namespace Util
{
	// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
	inline const std::string CurrentDateTime()
	{
		time_t     now = time(NULL);
		struct tm  tstruct;
		char       buf[80];
		localtime_s(&tstruct, &now);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
		return buf;
	}
}
#endif