#ifndef METHODGUIITEM_H
#define METHODGUIITEM_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QRadioButton>
#include "Parameter.h"
#include "ui_Method.h"

/**
* \brief Class which represents a gui item for a verification method
* Contains a checkbox with a name, a dropbox for parameter name 
* and a line edit/radio button for input
*/
class MethodGuiItem : public QWidget
{
	Q_OBJECT
public:
	MethodGuiItem(std::string name, std::vector<Parameter>& parameters, QWidget* parent = 0);
	virtual ~MethodGuiItem();

	/**
	* \brief Returns if the checkbox is checked
	*/
	bool selected();

	/**
	* \brief Returns the name of the item
	*/
	std::string name();

	/**
	* \brief Returns the parameters from gui
	* Each parameter change will be stored
	*/
	std::vector<Parameter>& parameters();

	/**
	* \brief Sets the mode of the gui item
	* If the associated method fails a red box becomes visible
	* else a green one
	*/
	void setMode(bool successful);

public slots:
	/**
	* \brief Updates the parameters which will be displayed
	* \param index index from dropdown
	*/
	void paramIndexChanged(int index);

	/**
	* \brief Updates the current parameter if the type is string, double, int
	*/
	void paramInputChanged(const QString& input);

	/**
	* \brief Updates the current parameter if the type is bool
	*/
	void paramInputChanged(bool input);

private:
	Ui::Method ui_;
	std::string name_;
	std::string fileName_;
	std::string baseDir_;

	std::vector<Parameter> parameters_;

	/**
	* \brief Updates the displayed parameters
	*/
	void changeParams(int index);

	/**
	* \Resets the current to normal
	* Normal means without box
	*/
	void changeToNormal(bool toggled);

	void loadProfile(const std::string& profilePath);

	void loadProfileClicked();
	void saveProfileClicked();
};

#endif //MethodGuiItem
