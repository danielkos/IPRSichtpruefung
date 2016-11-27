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

	std::vector<QVariant> objMetrics();
	QSize referenceSize();

	QVariant holeDiameter();
	QVariant angle();

private:
	Ui::Options ui_;

	std::vector<QVariant> objMetrics_;
	QSize referenceSize_;
	QVariant holeDiameter_;
	QVariant angle_;
	QVariant referenceWidth_;
	QVariant referenceHeigth_;

	void setValues();

private slots:
	void closeClicked();
};

#endif // !OPTIONS_GUI_H

