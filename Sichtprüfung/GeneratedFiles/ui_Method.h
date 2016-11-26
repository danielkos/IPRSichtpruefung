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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Method
{
public:
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBoxMethod;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioButtonBoolInput;
    QComboBox *comboBoxParams;
    QLineEdit *lineEditNumInput;

    void setupUi(QWidget *Method)
    {
        if (Method->objectName().isEmpty())
            Method->setObjectName(QStringLiteral("Method"));
        Method->resize(318, 53);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Method->sizePolicy().hasHeightForWidth());
        Method->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(Method);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBoxMethod = new QGroupBox(Method);
        groupBoxMethod->setObjectName(QStringLiteral("groupBoxMethod"));
        groupBoxMethod->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBoxMethod->setFlat(false);
        groupBoxMethod->setCheckable(true);
        groupBoxMethod->setChecked(false);
        horizontalLayout_4 = new QHBoxLayout(groupBoxMethod);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 15, -1, 9);
        radioButtonBoolInput = new QRadioButton(groupBoxMethod);
        radioButtonBoolInput->setObjectName(QStringLiteral("radioButtonBoolInput"));

        horizontalLayout_4->addWidget(radioButtonBoolInput);

        comboBoxParams = new QComboBox(groupBoxMethod);
        comboBoxParams->setObjectName(QStringLiteral("comboBoxParams"));
        comboBoxParams->setMinimumSize(QSize(140, 0));

        horizontalLayout_4->addWidget(comboBoxParams);

        lineEditNumInput = new QLineEdit(groupBoxMethod);
        lineEditNumInput->setObjectName(QStringLiteral("lineEditNumInput"));

        horizontalLayout_4->addWidget(lineEditNumInput);


        horizontalLayout_2->addWidget(groupBoxMethod);


        retranslateUi(Method);

        QMetaObject::connectSlotsByName(Method);
    } // setupUi

    void retranslateUi(QWidget *Method)
    {
        Method->setWindowTitle(QApplication::translate("Method", "Form", 0));
        groupBoxMethod->setTitle(QApplication::translate("Method", "GroupBox", 0));
        radioButtonBoolInput->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Method: public Ui_Method {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_METHOD_H
