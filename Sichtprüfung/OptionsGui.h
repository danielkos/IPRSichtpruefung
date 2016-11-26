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
	std::vector<double> referenceSize();

	double holeDiameter();
	double angle();

private:
	Ui::Options ui_;

	std::vector<double> size_;
	std::vector<double> referenceSize_;
	double holeDiameter_;
	double angle_;
	double referenceWidth_;
	double referenceHeigth_;
};

#endif // !OPTIONS_GUI_H

