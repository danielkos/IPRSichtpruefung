#ifndef MAINGUI_H
#define MAINGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_MainGui.h"
#include "ResultGenerator.h"

class FrameView;
class VerificationMethod;
class MethodGuiItem;
class OptionsGui;
class UpldFrame;
class QTabWidget;
class IDSCamera;

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

	/** \brief Adds the result and processed image to a new tab in corresponding view
	*   \param methodName name of the method
	*   \param resImg a result image
	*   \param preprocImg a preprocessed image
	*/
	void addMethodResults(const QString& methodName, const cv::Mat* resImg, const cv::Mat* preprocImg);

private:
	/** \brief Finds a tab in a widget with a name
	*	\param tabWidget a tab widget
	*   \param name name of method
	*   \param index index which will be returned
	*/
	bool findTab(const QTabWidget* tabWidget, const QString& name, int& intdex);

	/** \brief Clears all tabs */
	void clearTabs();

	/** \brief Sets a tab by name
	*   \param methodName name of method 
	*/
	void setTab(QString methodName);

	Ui::MainGui ui_;

	//Original image initialized in constructor
	cv::Mat* orgImg_;

	//View to display original image
	FrameView* inputView_;

	//Types to make code more readable
	typedef std::map<MethodGuiItem*, VerificationMethod*> ItemMethodMap;
	typedef std::pair<MethodGuiItem*, VerificationMethod*> ItemMethodPair;
	//Association between method and gui item
	ItemMethodMap methods_;

	//Path to selected file
	QString currentFile_;

	//Options dialog
	OptionsGui* options_;

	//IO
	UpldFrame* io_;

	IDSCamera* cam_;
	//Result presenter
	ResultGenerator resGenerator;

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

	/**
	* \brief Open the optios gui
	*/
	void openOptions();

	/**
	* \brief Create map with all settings provided by the option gui
	*/
	ResultGenerator::SettingsMap generateSettings();
};

#endif // MAINGUI_H
