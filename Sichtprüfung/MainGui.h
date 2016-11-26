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
/**
* \brief Main gui
*/
class MainGui : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainGui(QWidget *parent = 0);
	virtual ~MainGui();

	/** \brief Adds a method to the gui
	*	Generates a association between a VerificationMethod and MethodGuiItem
	*	\param name method name which will be displayed next to the checkbox
	*	\param method the method which will be executed if the checkbox is checked
	*/
	void addVerificationMethod(std::string name, VerificationMethod* method);

private:
	Ui::MainGui ui;

	//Original image
	cv::Mat* orgImg_;
	//Preprocessed image
	cv::Mat* preprocImg_;
	//Result image
	cv::Mat* resultImg_;

	//View to display original image
	FrameView* inputView_;
	//View to display preprocessed image
	FrameView* preprocView_;
	//View to display result image
	FrameView* resultView_;

	//Types to make code more readable
	typedef std::map<MethodGuiItem*, VerificationMethod*> ItemMethodMap;
	typedef std::pair<MethodGuiItem*, VerificationMethod*> ItemMethodPair;
	//Association between method and gui item
	ItemMethodMap methods_;

	//Path to selected file
	QString currentFile_;

public slots:
	/**
	* \brief Runs alls selected methods
	*/
	void runSelectedMethods();
	/**
	* \brief Sets the image for input and preprocView_. 
	*  Schould be called before runSelectedMethods at least once!!!
	*  In case of preprocView_ a grayscale image is generated and stored
	*  to preprocImg_
	*/
	void setInputImage(cv::Mat* img);

	/**
	* \brief Adds a file stream to the table widget
	*/
	void addFileStream(QString stream);

private slots:

	/**
	* \brief Adds the file and its path to the input tab
	*/
	void addFile();

	/**
	* \brief Removes a file from input tab
	*/
	void removeFile();

	/**
	* \brief Sets the path of the current selected file
	*/
	void setCurrentFile(QModelIndex index);

	/**
	* \brief Resets all stored images
	*/
	void reset();

	/**
	* \brief Displayes msg onto log tab
	*/
	void logOutput(QString msg);

	/**
	* \brief Displays msg onto status label
	*/
	void statusOutput(QString msg);
};

#endif // MAINGUI_H
