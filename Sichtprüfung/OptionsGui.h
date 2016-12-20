#ifndef OPTIONS_GUI_H
#define OPTIONS_GUI_H

#include <QWidget>
#include <QMainWindow>

#include "ui_Options.h"


class OptionsGui : public QMainWindow
{
	Q_OBJECT
public:
	OptionsGui(QWidget* parent = 0);
	~OptionsGui();

	void saveValues();

	QSize objSize();

	QVariant holeRadius();
	QVariant angle();

	std::string cameraConfigPath();

private:
	Ui::Options ui_;

	QSize objSize_;
	QVariant holeRadius_;
	QVariant angle_;

	std::string configFile_;
	std::string cameraConfig_;

	void setValues();

private slots:
	void closeClicked();

	void selectPathClicked();
};

#endif // !OPTIONS_GUI_H

