/********************************************************************************
** Form generated from reading UI file 'Options.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Options
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBoxSize;
    QGridLayout *gridLayout;
    QDoubleSpinBox *doubleSpinBoxLength;
    QDoubleSpinBox *doubleSpinBoxWidth;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxHeight;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxDiameter;
    QDoubleSpinBox *doubleSpinBoxAngle;
    QDialogButtonBox *buttonBoxOptions;

    void setupUi(QMainWindow *Options)
    {
        if (Options->objectName().isEmpty())
            Options->setObjectName(QStringLiteral("Options"));
        Options->resize(232, 200);
        Options->setMinimumSize(QSize(230, 200));
        centralwidget = new QWidget(Options);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBoxSize = new QGroupBox(centralwidget);
        groupBoxSize->setObjectName(QStringLiteral("groupBoxSize"));
        groupBoxSize->setFlat(false);
        groupBoxSize->setCheckable(false);
        gridLayout = new QGridLayout(groupBoxSize);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        doubleSpinBoxLength = new QDoubleSpinBox(groupBoxSize);
        doubleSpinBoxLength->setObjectName(QStringLiteral("doubleSpinBoxLength"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(doubleSpinBoxLength->sizePolicy().hasHeightForWidth());
        doubleSpinBoxLength->setSizePolicy(sizePolicy);
        doubleSpinBoxLength->setMaximum(200);
        doubleSpinBoxLength->setSingleStep(0.01);

        gridLayout->addWidget(doubleSpinBoxLength, 3, 1, 1, 1);

        doubleSpinBoxWidth = new QDoubleSpinBox(groupBoxSize);
        doubleSpinBoxWidth->setObjectName(QStringLiteral("doubleSpinBoxWidth"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(doubleSpinBoxWidth->sizePolicy().hasHeightForWidth());
        doubleSpinBoxWidth->setSizePolicy(sizePolicy1);
        doubleSpinBoxWidth->setMaximum(200);
        doubleSpinBoxWidth->setSingleStep(0.01);

        gridLayout->addWidget(doubleSpinBoxWidth, 3, 0, 1, 1);

        label_2 = new QLabel(groupBoxSize);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(groupBoxSize);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        label_3 = new QLabel(groupBoxSize);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 2, 1, 1);

        doubleSpinBoxHeight = new QDoubleSpinBox(groupBoxSize);
        doubleSpinBoxHeight->setObjectName(QStringLiteral("doubleSpinBoxHeight"));
        sizePolicy1.setHeightForWidth(doubleSpinBoxHeight->sizePolicy().hasHeightForWidth());
        doubleSpinBoxHeight->setSizePolicy(sizePolicy1);
        doubleSpinBoxHeight->setMaximum(200);
        doubleSpinBoxHeight->setSingleStep(0.01);

        gridLayout->addWidget(doubleSpinBoxHeight, 3, 2, 1, 1);


        verticalLayout_2->addWidget(groupBoxSize);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 1, 1, 1);

        doubleSpinBoxDiameter = new QDoubleSpinBox(groupBox);
        doubleSpinBoxDiameter->setObjectName(QStringLiteral("doubleSpinBoxDiameter"));

        gridLayout_3->addWidget(doubleSpinBoxDiameter, 1, 0, 1, 1);

        doubleSpinBoxAngle = new QDoubleSpinBox(groupBox);
        doubleSpinBoxAngle->setObjectName(QStringLiteral("doubleSpinBoxAngle"));

        gridLayout_3->addWidget(doubleSpinBoxAngle, 1, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        buttonBoxOptions = new QDialogButtonBox(centralwidget);
        buttonBoxOptions->setObjectName(QStringLiteral("buttonBoxOptions"));
        buttonBoxOptions->setLayoutDirection(Qt::LeftToRight);
        buttonBoxOptions->setOrientation(Qt::Horizontal);
        buttonBoxOptions->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

        verticalLayout_2->addWidget(buttonBoxOptions);

        Options->setCentralWidget(centralwidget);

        retranslateUi(Options);

        QMetaObject::connectSlotsByName(Options);
    } // setupUi

    void retranslateUi(QMainWindow *Options)
    {
        Options->setWindowTitle(QApplication::translate("Options", "Options", 0));
        groupBoxSize->setTitle(QApplication::translate("Options", "Size", 0));
        label_2->setText(QApplication::translate("Options", "Width (cm):", 0));
        label->setText(QApplication::translate("Options", " Length (cm):", 0));
        label_3->setText(QApplication::translate("Options", "Height (cm):", 0));
        groupBox->setTitle(QApplication::translate("Options", "Properties", 0));
        label_4->setText(QApplication::translate("Options", "Hole Diameter (cm):", 0));
        label_5->setText(QApplication::translate("Options", "Angle (\302\260):", 0));
    } // retranslateUi

};

namespace Ui {
    class Options: public Ui_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
