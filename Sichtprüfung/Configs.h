#include <opencv2\opencv.hpp>
#include <Windows.h>
#include <string>

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
		return path.substr(0, path.find_last_of("\\/"));
	}
}
namespace filenames
{
	const std::string optionsName = "options.xml";
	const std::string calibrationName = "calibration.xml";
	const std::string cameraConfig = "IPR.ini";
}

#endif



