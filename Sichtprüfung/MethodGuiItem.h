#ifndef METHODGUIITEM_H
#define METHODGUIITEM_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>

class MethodGuiItem : public QCheckBox
{
	Q_OBJECT
public:
	MethodGuiItem(std::string name, QWidget* parent = 0);
	~MethodGuiItem();

	bool selected();
};

#endif //MethodGuiItem
