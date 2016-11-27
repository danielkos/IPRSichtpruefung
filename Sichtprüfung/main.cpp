#include "MainGui.h"
#include <QtWidgets/QApplication>
#include <QDesktopWidget>
#include <QSize>
#include <opencv2\opencv.hpp>
#include "HoleVerification.h"
#include "Calibration.h"
#include "HoleParameter.h"

int main(int argc, char *argv[])
{
	//main application
	QApplication app(argc, argv);
	//GUI generated from ui file
	MainGui mainGui;
	QDesktopWidget *desktop = QApplication::desktop();
	QSize windowSize = mainGui.size();
	int screenWidth = desktop->width();
	int screenHeight = desktop->height();
	int x = (screenWidth - windowSize.width()) / 2;
	int y = (screenHeight - windowSize.height()) / 2;

	VerificationMethod* calib = new Calibration();
	//VerificationMethod* holeparam = new HoleParameter();
	
	mainGui.addVerificationMethod("Calibration", calib);
	//mainGui.addVerificationMethod("Hole detection", holeparam);
	
	mainGui.move(x, y);
	mainGui.show();


	return app.exec();
}
