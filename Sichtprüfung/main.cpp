//#include <cstdio>

#include <QtWidgets/QApplication>
#include <QDesktopWidget>
#include <QSize>

#include <opencv2\opencv.hpp>

#include "MainGui.h"
#include "HoleVerification.h"
#include "Calibration.h"
#include "HoleVerification.h"
#include "AngleVerification.h"
#include "ShapeVerification.h"
#include "MaterialVerification.h"
#include "Configs.h"
#include "Logger.h"

void createDirectories();
void loggerOutput(const std::string& path, bool& ret, bool& exists);

int main(int argc, char *argv[])
{
	// Delete log file to make sure a new empty one is created
	// during execution
	std::remove("log.txt");
	
	//main application
	QApplication app(argc, argv);
	//GUI generated from ui file
	MainGui mainGui;
	QDesktopWidget *desktop = QApplication::desktop();

	createDirectories();

	VerificationMethod* calib = new Calibration();
	VerificationMethod* holeVer = new HoleVerification();
	VerificationMethod* angleVer = new AngleVerification();
	VerificationMethod* shapeVer = new ShapeVerification();
	VerificationMethod* materialVer = new MaterialVerification();

	mainGui.addVerificationMethod("Calibration", calib);
	mainGui.addVerificationMethod("Hole Detection", holeVer);
	mainGui.addVerificationMethod("Angle Detection", angleVer);
	mainGui.addVerificationMethod("Shape Verification", shapeVer);
	mainGui.addVerificationMethod("Material Verification", materialVer);

	mainGui.show();

	QSize windowSize = mainGui.size();
	int difference = desktop->frameGeometry().height() - desktop->geometry().height();
	int screenWidth = desktop->availableGeometry().width();
	int x = (screenWidth - windowSize.width()) / 2;
	mainGui.move(x, difference);

	int res = app.exec();

	delete calib;
	delete holeVer;
	delete angleVer;
	delete materialVer;

	return res;
}

void createDirectories()
{
	bool exists;
	std::string path;
	bool ret;

	path = paths::getExecutablePath() + paths::configFolder;
	ret = paths::createDir(path, exists);
	loggerOutput(path, ret, exists);

	if (ret || exists)
	{
		path = paths::getExecutablePath() + paths::configFolder + paths::cameraFolder;
		ret = paths::createDir(path, exists);
		loggerOutput(path, ret, exists);

		path = paths::getExecutablePath() + paths::configFolder + paths::profilesFolder;
		ret = paths::createDir(path, exists);
		loggerOutput(path, ret, exists);
	}	
}

void loggerOutput(const std::string& path, bool& ret, bool& exists)
{
	if (!ret && exists)
	{
		LOGGER.log("Reusing directory: " + path);
	}
	else if (ret)
	{
		LOGGER.log("Directory: " + path + "  created");
	}
	else if (!ret && !exists)
	{
		LOGGER.log("Unknown error while creating directory: " + path);
	}
}