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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainGui
{
public:
    QAction *action_About;
    QAction *action_Exit;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QProgressBar *barStatus;
    QHBoxLayout *horizontalLayout;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QWidget *gridWidget;
    QGridLayout *gridLayout;
    QWidget *widInputImage;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_9;
    QLabel *labelPreprocessed;
    QLabel *labelInput;
    QWidget *widPreprocessed;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_10;
    QLabel *labelResult;
    QWidget *widResult;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget;
    QWidget *tabTestMethods;
    QVBoxLayout *verticalLayout_5;
    QWidget *widMethods;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBoxMethods;
    QWidget *tabInputImages;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBoxInputs;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainGui)
    {
        if (MainGui->objectName().isEmpty())
            MainGui->setObjectName(QStringLiteral("MainGui"));
        MainGui->resize(1200, 1000);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainGui->sizePolicy().hasHeightForWidth());
        MainGui->setSizePolicy(sizePolicy);
        MainGui->setMinimumSize(QSize(1200, 1000));
        MainGui->setMaximumSize(QSize(16777215, 16777215));
        MainGui->setToolButtonStyle(Qt::ToolButtonIconOnly);
        action_About = new QAction(MainGui);
        action_About->setObjectName(QStringLiteral("action_About"));
        action_Exit = new QAction(MainGui);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        centralWidget = new QWidget(MainGui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(6);
        gridLayout_2->setContentsMargins(5, 3, 5, 5);
        barStatus = new QProgressBar(centralWidget);
        barStatus->setObjectName(QStringLiteral("barStatus"));
        barStatus->setValue(24);
        barStatus->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(barStatus, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        verticalFrame = new QFrame(centralWidget);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
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
        gridWidget->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(gridWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(3);
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(0, 6, 0, 6);
        widInputImage = new QWidget(gridWidget);
        widInputImage->setObjectName(QStringLiteral("widInputImage"));
        sizePolicy1.setHeightForWidth(widInputImage->sizePolicy().hasHeightForWidth());
        widInputImage->setSizePolicy(sizePolicy1);
        widInputImage->setMinimumSize(QSize(400, 300));
        widInputImage->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_4 = new QHBoxLayout(widInputImage);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));

        horizontalLayout_4->addLayout(verticalLayout_9);


        gridLayout->addWidget(widInputImage, 2, 0, 1, 1);

        labelPreprocessed = new QLabel(gridWidget);
        labelPreprocessed->setObjectName(QStringLiteral("labelPreprocessed"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelPreprocessed->sizePolicy().hasHeightForWidth());
        labelPreprocessed->setSizePolicy(sizePolicy2);
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
        sizePolicy2.setHeightForWidth(labelInput->sizePolicy().hasHeightForWidth());
        labelInput->setSizePolicy(sizePolicy2);
        labelInput->setMinimumSize(QSize(400, 0));
        labelInput->setMaximumSize(QSize(16777215, 30));
        labelInput->setFont(font);
        labelInput->setLayoutDirection(Qt::LeftToRight);
        labelInput->setFrameShape(QFrame::WinPanel);
        labelInput->setFrameShadow(QFrame::Plain);
        labelInput->setLineWidth(1);
        labelInput->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelInput, 1, 0, 1, 1);

        widPreprocessed = new QWidget(gridWidget);
        widPreprocessed->setObjectName(QStringLiteral("widPreprocessed"));
        verticalLayout_7 = new QVBoxLayout(widPreprocessed);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(9, 9, 9, 9);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));

        verticalLayout_7->addLayout(verticalLayout_10);


        gridLayout->addWidget(widPreprocessed, 2, 1, 1, 1);


        verticalLayout->addWidget(gridWidget);

        labelResult = new QLabel(verticalFrame);
        labelResult->setObjectName(QStringLiteral("labelResult"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelResult->sizePolicy().hasHeightForWidth());
        labelResult->setSizePolicy(sizePolicy3);
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

        widResult = new QWidget(verticalFrame);
        widResult->setObjectName(QStringLiteral("widResult"));
        sizePolicy.setHeightForWidth(widResult->sizePolicy().hasHeightForWidth());
        widResult->setSizePolicy(sizePolicy);
        widResult->setMinimumSize(QSize(0, 400));
        widResult->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_8 = new QVBoxLayout(widResult);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));

        verticalLayout_8->addLayout(verticalLayout_6);


        verticalLayout->addWidget(widResult);


        horizontalLayout->addWidget(verticalFrame);


        gridLayout_2->addLayout(horizontalLayout, 0, 1, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy4);
        tabWidget->setMinimumSize(QSize(300, 0));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideLeft);
        tabTestMethods = new QWidget();
        tabTestMethods->setObjectName(QStringLiteral("tabTestMethods"));
        verticalLayout_5 = new QVBoxLayout(tabTestMethods);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        widMethods = new QWidget(tabTestMethods);
        widMethods->setObjectName(QStringLiteral("widMethods"));
        verticalLayout_11 = new QVBoxLayout(widMethods);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(6, 3, 6, 3);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_4->setContentsMargins(10, 3, 6, 3);

        verticalLayout_11->addLayout(verticalLayout_4);


        verticalLayout_5->addWidget(widMethods);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        buttonBoxMethods = new QDialogButtonBox(tabTestMethods);
        buttonBoxMethods->setObjectName(QStringLiteral("buttonBoxMethods"));
        buttonBoxMethods->setLayoutDirection(Qt::LeftToRight);
        buttonBoxMethods->setStandardButtons(QDialogButtonBox::NoButton);
        buttonBoxMethods->setCenterButtons(true);

        verticalLayout_5->addWidget(buttonBoxMethods);

        tabWidget->addTab(tabTestMethods, QString());
        tabInputImages = new QWidget();
        tabInputImages->setObjectName(QStringLiteral("tabInputImages"));
        verticalLayout_3 = new QVBoxLayout(tabInputImages);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        tableWidget = new QTableWidget(tabInputImages);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        font2.setKerning(false);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignTop);
        __qtablewidgetitem->setFont(font2);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignLeading|Qt::AlignBottom);
        __qtablewidgetitem1->setFont(font2);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setFrameShape(QFrame::StyledPanel);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        tableWidget->setProperty("showDropIndicator", QVariant(false));
        tableWidget->setTextElideMode(Qt::ElideLeft);
        tableWidget->setShowGrid(true);
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->setSortingEnabled(true);
        tableWidget->setWordWrap(true);
        tableWidget->setRowCount(0);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(135);
        tableWidget->horizontalHeader()->setMinimumSectionSize(135);
        tableWidget->horizontalHeader()->setStretchLastSection(false);
        tableWidget->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget->verticalHeader()->setDefaultSectionSize(25);
        tableWidget->verticalHeader()->setMinimumSectionSize(25);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        verticalLayout_2->addWidget(tableWidget);

        buttonBoxInputs = new QDialogButtonBox(tabInputImages);
        buttonBoxInputs->setObjectName(QStringLiteral("buttonBoxInputs"));
        buttonBoxInputs->setMinimumSize(QSize(0, 0));
        buttonBoxInputs->setLayoutDirection(Qt::LeftToRight);
        buttonBoxInputs->setOrientation(Qt::Horizontal);
        buttonBoxInputs->setStandardButtons(QDialogButtonBox::Discard|QDialogButtonBox::Open);
        buttonBoxInputs->setCenterButtons(true);

        verticalLayout_2->addWidget(buttonBoxInputs);


        verticalLayout_3->addLayout(verticalLayout_2);

        tabWidget->addTab(tabInputImages, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        MainGui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainGui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 21));
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
        menuHelp->addAction(action_About);

        retranslateUi(MainGui);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainGui);
    } // setupUi

    void retranslateUi(QMainWindow *MainGui)
    {
        MainGui->setWindowTitle(QApplication::translate("MainGui", "Sichtpr\303\274fung", 0));
        action_About->setText(QApplication::translate("MainGui", "&About", 0));
        action_Exit->setText(QApplication::translate("MainGui", "&Exit", 0));
        labelPreprocessed->setText(QApplication::translate("MainGui", "Preprocessed Image", 0));
        labelInput->setText(QApplication::translate("MainGui", "Input Image", 0));
        labelResult->setText(QApplication::translate("MainGui", "Detection Result", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabTestMethods), QApplication::translate("MainGui", "Test Methods", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainGui", "Filename", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainGui", "Path", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabInputImages), QApplication::translate("MainGui", "Input Images", 0));
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
