#include "MainGui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	//main application
	QApplication app(argc, argv);
	//GUI generated from ui file
	MainGui mainGui;
	mainGui.show();

	return app.exec();
}
