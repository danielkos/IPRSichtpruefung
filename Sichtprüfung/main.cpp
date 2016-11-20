#include "MainGui.h"
#include <QtWidgets/QApplication>
#include <opencv2\opencv.hpp>
#include "HoleVerification.h"

int main(int argc, char *argv[])
{
	//main application
	QApplication app(argc, argv);
	//GUI generated from ui file
	MainGui mainGui;
	VerificationMethod* item = new HoleVerification();
	
	mainGui.addVerificationMethod("1adfadf", item);
	mainGui.addVerificationMethod("2adfadf", item);

	mainGui.show();


	return app.exec();
}
