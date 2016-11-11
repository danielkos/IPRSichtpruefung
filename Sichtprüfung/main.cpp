#include "MainGui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainGui mainGui;
	mainGui.show();
	return app.exec();
}
