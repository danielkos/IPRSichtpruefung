/********************************************************************************
** Form generated from reading UI file 'Method.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_METHOD_H
#define UI_METHOD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Method
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxMethod;
    QGridLayout *gridLayout;
    QComboBox *comboBoxParams;
    QLabel *label;
    QLineEdit *lineEditProfile;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *openProfileButton;
    QPushButton *pushButtonSaveProfile;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButtonBoolInput;
    QDoubleSpinBox *doubleSpinBoxNumInput;
    QSpinBox *spinBoxNumInput;

    void setupUi(QWidget *Method)
    {
        if (Method->objectName().isEmpty())
            Method->setObjectName(QStringLiteral("Method"));
        Method->resize(411, 111);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Method->sizePolicy().hasHeightForWidth());
        Method->setSizePolicy(sizePolicy);
        Method->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(Method);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBoxMethod = new QGroupBox(Method);
        groupBoxMethod->setObjectName(QStringLiteral("groupBoxMethod"));
        groupBoxMethod->setEnabled(true);
        groupBoxMethod->setMaximumSize(QSize(16777215, 16777215));
        groupBoxMethod->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBoxMethod->setFlat(false);
        groupBoxMethod->setCheckable(true);
        groupBoxMethod->setChecked(false);
        gridLayout = new QGridLayout(groupBoxMethod);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, 15, -1, 9);
        comboBoxParams = new QComboBox(groupBoxMethod);
        comboBoxParams->setObjectName(QStringLiteral("comboBoxParams"));
        comboBoxParams->setMinimumSize(QSize(140, 0));

        gridLayout->addWidget(comboBoxParams, 0, 0, 1, 1);

        label = new QLabel(groupBoxMethod);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEditProfile = new QLineEdit(groupBoxMethod);
        lineEditProfile->setObjectName(QStringLiteral("lineEditProfile"));

        gridLayout->addWidget(lineEditProfile, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, -1, -1);
        openProfileButton = new QToolButton(groupBoxMethod);
        openProfileButton->setObjectName(QStringLiteral("openProfileButton"));

        horizontalLayout_3->addWidget(openProfileButton);

        pushButtonSaveProfile = new QPushButton(groupBoxMethod);
        pushButtonSaveProfile->setObjectName(QStringLiteral("pushButtonSaveProfile"));

        horizontalLayout_3->addWidget(pushButtonSaveProfile);


        gridLayout->addLayout(horizontalLayout_3, 2, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radioButtonBoolInput = new QRadioButton(groupBoxMethod);
        radioButtonBoolInput->setObjectName(QStringLiteral("radioButtonBoolInput"));

        horizontalLayout->addWidget(radioButtonBoolInput);

        doubleSpinBoxNumInput = new QDoubleSpinBox(groupBoxMethod);
        doubleSpinBoxNumInput->setObjectName(QStringLiteral("doubleSpinBoxNumInput"));
        doubleSpinBoxNumInput->setDecimals(1);
        doubleSpinBoxNumInput->setMaximum(1.11111e+60);
        doubleSpinBoxNumInput->setSingleStep(0.1);

        horizontalLayout->addWidget(doubleSpinBoxNumInput);

        spinBoxNumInput = new QSpinBox(groupBoxMethod);
        spinBoxNumInput->setObjectName(QStringLiteral("spinBoxNumInput"));
        spinBoxNumInput->setMinimumSize(QSize(133, 0));
        spinBoxNumInput->setMaximum(1111111111);

        horizontalLayout->addWidget(spinBoxNumInput);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBoxMethod);


        retranslateUi(Method);

        QMetaObject::connectSlotsByName(Method);
    } // setupUi

    void retranslateUi(QWidget *Method)
    {
        Method->setWindowTitle(QApplication::translate("Method", "Form", 0));
        groupBoxMethod->setTitle(QApplication::translate("Method", "GroupBox", 0));
        label->setText(QApplication::translate("Method", "Profile", 0));
        openProfileButton->setText(QApplication::translate("Method", "...", 0));
        pushButtonSaveProfile->setText(QApplication::translate("Method", "Save Profile", 0));
        pushButtonSaveProfile->setShortcut(QApplication::translate("Method", "Ctrl+S", 0));
        radioButtonBoolInput->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Method: public Ui_Method {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_METHOD_H
