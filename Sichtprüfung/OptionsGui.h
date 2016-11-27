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

	QVariantList objMetrics();
	QSize referenceSize();

	QVariant holeRadius();
	QVariant angle();

private:
	Ui::Options ui_;

	QVariantList objMetrics_;
	QSize referenceSize_;
	QVariant holeRadius_;
	QVariant angle_;

	void setValues();

private slots:
	void closeClicked();
};

#endif // !OPTIONS_GUI_H

