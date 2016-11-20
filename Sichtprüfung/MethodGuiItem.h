#ifndef METHODGUIITEM_H
#define METHODGUIITEM_H

#include <QWidget>
#include <QCheckBox>

/**
* \brief Class which represents a gui item for a verification method
* Contains a checkbox with a name
*/
class MethodGuiItem : public QCheckBox
{
	Q_OBJECT
public:
	MethodGuiItem(std::string name, QWidget* parent = 0);
	~MethodGuiItem();

	/**
	* \brief Returns if the checkbox is checked
	*/
	bool selected();
};

#endif //MethodGuiItem
