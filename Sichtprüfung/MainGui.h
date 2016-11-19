#ifndef MAINGUI_H
#define MAINGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_MainGui.h"

class FrameView;
class VerificationMethod;
class MethodGuiItem;

namespace cv
{
	class Mat;
}

class MainGui : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainGui(QWidget *parent = 0);
	virtual ~MainGui();

	void addVerificationMethod(std::string name, VerificationMethod* method);

private:
	Ui::MainGui ui;

	cv::Mat* orgImg_;
	cv::Mat* preprocImg_;
	cv::Mat* resultImg_;

	/**
	* \brief Views: Input, Processed, Result
	*/
	FrameView* inputView_;
	FrameView* preprocView_;
	FrameView* resultView_;

	typedef std::map<MethodGuiItem*, VerificationMethod*> ItemMethodMap;
	typedef std::pair<MethodGuiItem*, VerificationMethod*> ItemMethodPair;
	ItemMethodMap methods_;

public slots:
	void runSelectedMethods();
	/**
	* \brief Sets the input image vor each available view
	*/
	void setInputImage(cv::Mat* img);
};

#endif // MAINGUI_H
