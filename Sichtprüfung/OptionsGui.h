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

	std::vector<double> size();
	double holeDiameter();
	double angle();

private:
	Ui::Options ui_;

	std::vector<double> size_;
	double holeDiameter_;
	double angle_;
};

#endif // !OPTIONS_GUI_H

