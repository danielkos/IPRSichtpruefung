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

	VerificationMethod* calib = new Calibration();
	VerificationMethod* holeVer = new HoleVerification();
	VerificationMethod* angleVer = new AngleVerification();
	VerificationMethod* shapeVer = new ShapeVerification();

	mainGui.addVerificationMethod("Calibration", calib);
	mainGui.addVerificationMethod("Hole detection", holeVer);
	mainGui.addVerificationMethod("Angle detection", angleVer);
	mainGui.addVerificationMethod("Shape Verification", shapeVer);
	
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
	
	return res;
}
