#include "MainGui.h"
#include <QtWidgets/QApplication>
#include <opencv2\opencv.hpp>
#include "HoleVerification.h"
#include "Calibration.h"

int main(int argc, char *argv[])
{
	//main application
	QApplication app(argc, argv);
	//GUI generated from ui file
	MainGui mainGui;
	VerificationMethod* item = new Calibration();
	
	mainGui.addVerificationMethod("Calibration", item);

	mainGui.show();


	return app.exec();
}
