#include "Logger.h"

#include <opencv2\opencv.hpp>
#include <Windows.h>
#include <string>
#include <atlstr.h>

#ifndef CONFIGS
#define CONFIGS
namespace colors
{
	const cv::Scalar contourColor(0, 215, 255);
	const cv::Scalar middleColor(255, 255, 0);
	const cv::Scalar resultColor(0, 255, 0);
	const cv::Scalar infoColor(85, 26, 139);

	const int lineThickness = 6;
	const int contourThickness= 8;
	const int pointThickness = 3;
	const int circleThickness = 3;
}
/** \brief Basic structure: exeDir/configFolder/cameraFolder or other folders*/
namespace paths
{
	const std::string defaultFolder = "../Bilder";
	const std::string configFolder = "config\\";
	const std::string cameraFolder = "camera\\";

	static std::string getExecutablePath()
	{
		TCHAR result[2 * MAX_PATH];
		GetModuleFileName(NULL, result, 2 * MAX_PATH);
		std::wstring wpath(result);
		std::string path(wpath.begin(), wpath.end());
		path = path.substr(0, path.find_last_of("\\/")) + "\\";
		return path;
	}

	static bool createDir(const std::string& path, bool& exists)
	{
		bool ret = true;
		exists = false;
		TCHAR *str = new TCHAR[path.size() + 1];
		str[path.size()] = 0;
		//can cause problems with UTF-16
		std::copy(path.begin(), path.end(), str);
		
		ret = CreateDirectory(str, NULL);
		
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			exists = true;
			ret = false;
		}
		return ret;
	}
}
namespace filenames
{
	const std::string optionsName = "options.xml";
	const std::string calibrationName = "calibration.xml";
	const std::string cameraConfig = "IPR.ini";
}

#endif



