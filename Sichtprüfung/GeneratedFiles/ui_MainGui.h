/********************************************************************************
** Form generated from reading UI file 'MainGui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINGUI_H
#define UI_MAINGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainGui
{
public:
    QAction *action_About;
    QAction *action_Exit;
    QAction *actionTest_Object;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabTestMethods;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBoxMethods;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *groupBoxResults;
    QVBoxLayout *verticalLayout_11;
    QListWidget *listWidgetResults;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBoxMethods;
    QSpacerItem *verticalSpacer_2;
    QWidget *tabInputImages;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QTreeView *treeViewInput;
    QDialogButtonBox *buttonBoxInputs;
    QWidget *tabLog;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_12;
    QListWidget *listWidgetLog;
    QHBoxLayout *horizontalLayout;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QWidget *gridWidget;
    QGridLayout *gridLayout;
    QLabel *labelPreprocessed;
    QLabel *labelInput;
    QFrame *widInputImage;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_9;
    QTabWidget *tabWidgetProcessed;
    QWidget *tab_5;
    QWidget *tab_6;
    QLabel *labelResult;
    QTabWidget *tabWidgetResult;
    QWidget *tab_3;
    QWidget *tab_4;
    QLabel *labelProgress;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainGui)
    {
        if (MainGui->objectName().isEmpty())
            MainGui->setObjectName(QStringLiteral("MainGui"));
        MainGui->resize(1247, 1000);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainGui->sizePolicy().hasHeightForWidth());
        MainGui->setSizePolicy(sizePolicy);
        MainGui->setMinimumSize(QSize(0, 0));
        MainGui->setMaximumSize(QSize(16777215, 16777215));
        MainGui->setToolButtonStyle(Qt::ToolButtonIconOnly);
        action_About = new QAction(MainGui);
        action_About->setObjectName(QStringLiteral("action_About"));
        action_Exit = new QAction(MainGui);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        actionTest_Object = new QAction(MainGui);
        actionTest_Object->setObjectName(QStringLiteral("actionTest_Object"));
        centralWidget = new QWidget(MainGui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(6);
        gridLayout_2->setContentsMargins(5, 3, 5, 5);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(400, 0));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideLeft);
        tabTestMethods = new QWidget();
        tabTestMethods->setObjectName(QStringLiteral("tabTestMethods"));
        sizePolicy.setHeightForWidth(tabTestMethods->sizePolicy().hasHeightForWidth());
        tabTestMethods->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(tabTestMethods);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBoxMethods = new QGroupBox(tabTestMethods);
        groupBoxMethods->setObjectName(QStringLiteral("groupBoxMethods"));
        groupBoxMethods->setFlat(true);
        verticalLayout_14 = new QVBoxLayout(groupBoxMethods);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));

        verticalLayout_5->addWidget(groupBoxMethods);

        groupBoxResults = new QGroupBox(tabTestMethods);
        groupBoxResults->setObjectName(QStringLiteral("groupBoxResults"));
        groupBoxResults->setFlat(true);
        verticalLayout_11 = new QVBoxLayout(groupBoxResults);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        listWidgetResults = new QListWidget(groupBoxResults);
        listWidgetResults->setObjectName(QStringLiteral("listWidgetResults"));
        listWidgetResults->setMinimumSize(QSize(0, 0));

        verticalLayout_11->addWidget(listWidgetResults);


        verticalLayout_5->addWidget(groupBoxResults);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer);

        buttonBoxMethods = new QDialogButtonBox(tabTestMethods);
        buttonBoxMethods->setObjectName(QStringLiteral("buttonBoxMethods"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(buttonBoxMethods->sizePolicy().hasHeightForWidth());
        buttonBoxMethods->setSizePolicy(sizePolicy2);
        buttonBoxMethods->setStandardButtons(QDialogButtonBox::Apply);

        verticalLayout_5->addWidget(buttonBoxMethods);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        tabWidget->addTab(tabTestMethods, QString());
        tabInputImages = new QWidget();
        tabInputImages->setObjectName(QStringLiteral("tabInputImages"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabInputImages->sizePolicy().hasHeightForWidth());
        tabInputImages->setSizePolicy(sizePolicy3);
        verticalLayout_3 = new QVBoxLayout(tabInputImages);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        treeViewInput = new QTreeView(tabInputImages);
        treeViewInput->setObjectName(QStringLiteral("treeViewInput"));
        treeViewInput->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        treeViewInput->header()->setDefaultSectionSize(100);
        treeViewInput->header()->setMinimumSectionSize(100);
        treeViewInput->header()->setStretchLastSection(false);

        verticalLayout_2->addWidget(treeViewInput);

        buttonBoxInputs = new QDialogButtonBox(tabInputImages);
        buttonBoxInputs->setObjectName(QStringLiteral("buttonBoxInputs"));
        sizePolicy2.setHeightForWidth(buttonBoxInputs->sizePolicy().hasHeightForWidth());
        buttonBoxInputs->setSizePolicy(sizePolicy2);
        buttonBoxInputs->setMinimumSize(QSize(0, 0));
        buttonBoxInputs->setLayoutDirection(Qt::LeftToRight);
        buttonBoxInputs->setOrientation(Qt::Horizontal);
        buttonBoxInputs->setStandardButtons(QDialogButtonBox::Discard|QDialogButtonBox::Open);
        buttonBoxInputs->setCenterButtons(true);

        verticalLayout_2->addWidget(buttonBoxInputs);


        verticalLayout_3->addLayout(verticalLayout_2);

        tabWidget->addTab(tabInputImages, QString());
        tabLog = new QWidget();
        tabLog->setObjectName(QStringLiteral("tabLog"));
        sizePolicy.setHeightForWidth(tabLog->sizePolicy().hasHeightForWidth());
        tabLog->setSizePolicy(sizePolicy);
        verticalLayout_13 = new QVBoxLayout(tabLog);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        listWidgetLog = new QListWidget(tabLog);
        listWidgetLog->setObjectName(QStringLiteral("listWidgetLog"));

        verticalLayout_12->addWidget(listWidgetLog);


        verticalLayout_13->addLayout(verticalLayout_12);

        tabWidget->addTab(tabLog, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        verticalFrame = new QFrame(centralWidget);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        sizePolicy.setHeightForWidth(verticalFrame->sizePolicy().hasHeightForWidth());
        verticalFrame->setSizePolicy(sizePolicy);
        verticalFrame->setFrameShape(QFrame::StyledPanel);
        verticalFrame->setFrameShadow(QFrame::Sunken);
        verticalFrame->setLineWidth(0);
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, 6);
        gridWidget = new QWidget(verticalFrame);
        gridWidget->setObjectName(QStringLiteral("gridWidget"));
        sizePolicy.setHeightForWidth(gridWidget->sizePolicy().hasHeightForWidth());
        gridWidget->setSizePolicy(sizePolicy);
        gridWidget->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(gridWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(3);
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(0, 6, 0, 6);
        labelPreprocessed = new QLabel(gridWidget);
        labelPreprocessed->setObjectName(QStringLiteral("labelPreprocessed"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(labelPreprocessed->sizePolicy().hasHeightForWidth());
        labelPreprocessed->setSizePolicy(sizePolicy4);
        labelPreprocessed->setMinimumSize(QSize(400, 0));
        labelPreprocessed->setMaximumSize(QSize(16777215, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        labelPreprocessed->setFont(font);
        labelPreprocessed->setFrameShape(QFrame::WinPanel);
        labelPreprocessed->setFrameShadow(QFrame::Plain);
        labelPreprocessed->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelPreprocessed, 1, 1, 1, 1);

        labelInput = new QLabel(gridWidget);
        labelInput->setObjectName(QStringLiteral("labelInput"));
        sizePolicy4.setHeightForWidth(labelInput->sizePolicy().hasHeightForWidth());
        labelInput->setSizePolicy(sizePolicy4);
        labelInput->setMinimumSize(QSize(400, 0));
        labelInput->setMaximumSize(QSize(16777215, 30));
        labelInput->setFont(font);
        labelInput->setLayoutDirection(Qt::LeftToRight);
        labelInput->setFrameShape(QFrame::WinPanel);
        labelInput->setFrameShadow(QFrame::Plain);
        labelInput->setLineWidth(1);
        labelInput->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelInput, 1, 0, 1, 1);

        widInputImage = new QFrame(gridWidget);
        widInputImage->setObjectName(QStringLiteral("widInputImage"));
        sizePolicy.setHeightForWidth(widInputImage->sizePolicy().hasHeightForWidth());
        widInputImage->setSizePolicy(sizePolicy);
        widInputImage->setMinimumSize(QSize(0, 0));
        widInputImage->setMaximumSize(QSize(16777215, 16777215));
        widInputImage->setFrameShape(QFrame::StyledPanel);
        horizontalLayout_4 = new QHBoxLayout(widInputImage);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));

        horizontalLayout_4->addLayout(verticalLayout_9);


        gridLayout->addWidget(widInputImage, 2, 0, 1, 1);

        tabWidgetProcessed = new QTabWidget(gridWidget);
        tabWidgetProcessed->setObjectName(QStringLiteral("tabWidgetProcessed"));
        tabWidgetProcessed->setTabShape(QTabWidget::Triangular);
        tabWidgetProcessed->setMovable(true);
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        tabWidgetProcessed->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        tabWidgetProcessed->addTab(tab_6, QString());

        gridLayout->addWidget(tabWidgetProcessed, 2, 1, 1, 1);


        verticalLayout->addWidget(gridWidget);

        labelResult = new QLabel(verticalFrame);
        labelResult->setObjectName(QStringLiteral("labelResult"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(labelResult->sizePolicy().hasHeightForWidth());
        labelResult->setSizePolicy(sizePolicy5);
        labelResult->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        labelResult->setFont(font1);
        labelResult->setFrameShape(QFrame::WinPanel);
        labelResult->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelResult);

        tabWidgetResult = new QTabWidget(verticalFrame);
        tabWidgetResult->setObjectName(QStringLiteral("tabWidgetResult"));
        tabWidgetResult->setTabShape(QTabWidget::Triangular);
        tabWidgetResult->setMovable(true);
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidgetResult->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidgetResult->addTab(tab_4, QString());

        verticalLayout->addWidget(tabWidgetResult);

        labelProgress = new QLabel(verticalFrame);
        labelProgress->setObjectName(QStringLiteral("labelProgress"));
        labelProgress->setMaximumSize(QSize(16777215, 20));
        labelProgress->setFrameShape(QFrame::Box);
        labelProgress->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(labelProgress);


        horizontalLayout->addWidget(verticalFrame);


        gridLayout_2->addLayout(horizontalLayout, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(1, 1, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        MainGui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainGui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1247, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainGui->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(action_Exit);
        menuOptions->addAction(actionTest_Object);
        menuHelp->addAction(action_About);

        retranslateUi(MainGui);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainGui);
    } // setupUi

    void retranslateUi(QMainWindow *MainGui)
    {
        MainGui->setWindowTitle(QApplication::translate("MainGui", "Sichtpr\303\274fung", 0));
        action_About->setText(QApplication::translate("MainGui", "&About", 0));
        action_Exit->setText(QApplication::translate("MainGui", "&Exit", 0));
        actionTest_Object->setText(QApplication::translate("MainGui", "Configuration", 0));
        groupBoxMethods->setTitle(QApplication::translate("MainGui", "Methods", 0));
        groupBoxResults->setTitle(QApplication::translate("MainGui", "Results", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabTestMethods), QApplication::translate("MainGui", "Test Methods", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabInputImages), QApplication::translate("MainGui", "Input Images", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabLog), QApplication::translate("MainGui", "Log", 0));
        labelPreprocessed->setText(QApplication::translate("MainGui", "Preprocessed Image", 0));
        labelInput->setText(QApplication::translate("MainGui", "Input Image", 0));
        tabWidgetProcessed->setTabText(tabWidgetProcessed->indexOf(tab_5), QApplication::translate("MainGui", "Tab 1", 0));
        tabWidgetProcessed->setTabText(tabWidgetProcessed->indexOf(tab_6), QApplication::translate("MainGui", "Tab 2", 0));
        labelResult->setText(QApplication::translate("MainGui", "Detection Result", 0));
        tabWidgetResult->setTabText(tabWidgetResult->indexOf(tab_3), QApplication::translate("MainGui", "Tab 1", 0));
        tabWidgetResult->setTabText(tabWidgetResult->indexOf(tab_4), QApplication::translate("MainGui", "Tab 2", 0));
        labelProgress->setText(QString());
        menuFile->setTitle(QApplication::translate("MainGui", "File", 0));
        menuOptions->setTitle(QApplication::translate("MainGui", "Options", 0));
        menuHelp->setTitle(QApplication::translate("MainGui", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainGui: public Ui_MainGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINGUI_H
