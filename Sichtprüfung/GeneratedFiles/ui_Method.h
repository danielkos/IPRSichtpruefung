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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
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
    QFrame *frameMethod;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxMethod;
    QFrame *frame;
    QRadioButton *radioButtonBoolInput;
    QComboBox *comboBoxParams;
    QLineEdit *lineEditNumInput;

    void setupUi(QWidget *Method)
    {
        if (Method->objectName().isEmpty())
            Method->setObjectName(QStringLiteral("Method"));
        Method->resize(392, 22);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Method->sizePolicy().hasHeightForWidth());
        Method->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(Method);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        frameMethod = new QFrame(Method);
        frameMethod->setObjectName(QStringLiteral("frameMethod"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frameMethod->sizePolicy().hasHeightForWidth());
        frameMethod->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(frameMethod);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        checkBoxMethod = new QCheckBox(frameMethod);
        checkBoxMethod->setObjectName(QStringLiteral("checkBoxMethod"));

        horizontalLayout->addWidget(checkBoxMethod);

        frame = new QFrame(frameMethod);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::VLine);
        frame->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frame);

        radioButtonBoolInput = new QRadioButton(frameMethod);
        radioButtonBoolInput->setObjectName(QStringLiteral("radioButtonBoolInput"));

        horizontalLayout->addWidget(radioButtonBoolInput);

        comboBoxParams = new QComboBox(frameMethod);
        comboBoxParams->setObjectName(QStringLiteral("comboBoxParams"));
        comboBoxParams->setMinimumSize(QSize(140, 0));

        horizontalLayout->addWidget(comboBoxParams);

        lineEditNumInput = new QLineEdit(frameMethod);
        lineEditNumInput->setObjectName(QStringLiteral("lineEditNumInput"));

        horizontalLayout->addWidget(lineEditNumInput);


        horizontalLayout_2->addWidget(frameMethod);


        retranslateUi(Method);

        QMetaObject::connectSlotsByName(Method);
    } // setupUi

    void retranslateUi(QWidget *Method)
    {
        Method->setWindowTitle(QApplication::translate("Method", "Form", 0));
        checkBoxMethod->setText(QApplication::translate("Method", "CheckBox", 0));
        radioButtonBoolInput->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Method: public Ui_Method {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_METHOD_H
