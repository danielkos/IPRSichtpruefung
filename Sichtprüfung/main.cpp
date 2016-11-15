#include "MainGui.h"
#include <QtWidgets/QApplication>
#include <opencv2\opencv.hpp>

int main(int argc, char *argv[])
{
	//main application
	QApplication app(argc, argv);
	//GUI generated from ui file
	MainGui mainGui;
	cv::Mat src;
	
	src = cv::imread(argv[1], true);
	
	mainGui.setInputImage(&src);
	mainGui.show();


	return app.exec();
}
