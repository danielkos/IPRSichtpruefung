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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
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
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxWidth;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxLength;
    QGroupBox *groupBoxProperties;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxDiameter;
    QDoubleSpinBox *doubleSpinBoxAngle;
    QGroupBox *groupBoxReference;
    QGridLayout *gridLayout_4;
    QPushButton *pushButtonOpen;
    QLabel *label_6;
    QLineEdit *lineEditConfig;
    QCheckBox *checkBoxCalibration;
    QDialogButtonBox *buttonBoxOptions;

    void setupUi(QMainWindow *Options)
    {
        if (Options->objectName().isEmpty())
            Options->setObjectName(QStringLiteral("Options"));
        Options->resize(300, 297);
        Options->setMinimumSize(QSize(300, 275));
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
        label_2 = new QLabel(groupBoxSize);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        doubleSpinBoxWidth = new QDoubleSpinBox(groupBoxSize);
        doubleSpinBoxWidth->setObjectName(QStringLiteral("doubleSpinBoxWidth"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(doubleSpinBoxWidth->sizePolicy().hasHeightForWidth());
        doubleSpinBoxWidth->setSizePolicy(sizePolicy);
        doubleSpinBoxWidth->setMaximum(200);
        doubleSpinBoxWidth->setSingleStep(0.01);
        doubleSpinBoxWidth->setValue(41);

        gridLayout->addWidget(doubleSpinBoxWidth, 3, 0, 1, 1);

        label = new QLabel(groupBoxSize);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        doubleSpinBoxLength = new QDoubleSpinBox(groupBoxSize);
        doubleSpinBoxLength->setObjectName(QStringLiteral("doubleSpinBoxLength"));
        sizePolicy.setHeightForWidth(doubleSpinBoxLength->sizePolicy().hasHeightForWidth());
        doubleSpinBoxLength->setSizePolicy(sizePolicy);
        doubleSpinBoxLength->setMaximum(200);
        doubleSpinBoxLength->setSingleStep(0.01);
        doubleSpinBoxLength->setValue(39);

        gridLayout->addWidget(doubleSpinBoxLength, 3, 1, 1, 1);


        verticalLayout_2->addWidget(groupBoxSize);

        groupBoxProperties = new QGroupBox(centralwidget);
        groupBoxProperties->setObjectName(QStringLiteral("groupBoxProperties"));
        gridLayout_3 = new QGridLayout(groupBoxProperties);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_4 = new QLabel(groupBoxProperties);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(groupBoxProperties);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 1, 1, 1);

        doubleSpinBoxDiameter = new QDoubleSpinBox(groupBoxProperties);
        doubleSpinBoxDiameter->setObjectName(QStringLiteral("doubleSpinBoxDiameter"));
        doubleSpinBoxDiameter->setValue(2.75);

        gridLayout_3->addWidget(doubleSpinBoxDiameter, 1, 0, 1, 1);

        doubleSpinBoxAngle = new QDoubleSpinBox(groupBoxProperties);
        doubleSpinBoxAngle->setObjectName(QStringLiteral("doubleSpinBoxAngle"));
        doubleSpinBoxAngle->setDecimals(2);
        doubleSpinBoxAngle->setValue(45);

        gridLayout_3->addWidget(doubleSpinBoxAngle, 1, 1, 1, 1);


        verticalLayout_2->addWidget(groupBoxProperties);

        groupBoxReference = new QGroupBox(centralwidget);
        groupBoxReference->setObjectName(QStringLiteral("groupBoxReference"));
        gridLayout_4 = new QGridLayout(groupBoxReference);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        pushButtonOpen = new QPushButton(groupBoxReference);
        pushButtonOpen->setObjectName(QStringLiteral("pushButtonOpen"));
        pushButtonOpen->setMaximumSize(QSize(30, 16777215));

        gridLayout_4->addWidget(pushButtonOpen, 2, 1, 1, 1);

        label_6 = new QLabel(groupBoxReference);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_4->addWidget(label_6, 1, 0, 1, 1);

        lineEditConfig = new QLineEdit(groupBoxReference);
        lineEditConfig->setObjectName(QStringLiteral("lineEditConfig"));

        gridLayout_4->addWidget(lineEditConfig, 2, 0, 1, 1);

        checkBoxCalibration = new QCheckBox(groupBoxReference);
        checkBoxCalibration->setObjectName(QStringLiteral("checkBoxCalibration"));

        gridLayout_4->addWidget(checkBoxCalibration, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBoxReference);

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
        label_2->setText(QApplication::translate("Options", "Width (mm):", 0));
        label->setText(QApplication::translate("Options", " Length (mm):", 0));
        groupBoxProperties->setTitle(QApplication::translate("Options", "Properties", 0));
        label_4->setText(QApplication::translate("Options", "Hole Radius (mm):", 0));
        label_5->setText(QApplication::translate("Options", "Angle (\302\260):", 0));
        groupBoxReference->setTitle(QApplication::translate("Options", "Camera Configuration", 0));
        pushButtonOpen->setText(QApplication::translate("Options", "...", 0));
        label_6->setText(QApplication::translate("Options", "Path:", 0));
        lineEditConfig->setText(QApplication::translate("Options", "\\camera\\config.ini", 0));
#ifndef QT_NO_TOOLTIP
        checkBoxCalibration->setToolTip(QApplication::translate("Options", "If checked the intrinsic and extrinsic camera parameters are used to calculate the pixel-mm-ratio. Otherwise the Shape verification method is used (calibration with object of known size).", 0));
#endif // QT_NO_TOOLTIP
        checkBoxCalibration->setText(QApplication::translate("Options", "Use OpenCV calibration", 0));
    } // retranslateUi

};

namespace Ui {
    class Options: public Ui_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
