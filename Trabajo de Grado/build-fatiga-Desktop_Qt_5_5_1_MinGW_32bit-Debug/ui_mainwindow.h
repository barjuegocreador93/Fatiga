/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QWidget *centralWidget;
    QCustomPlot *customPlot;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *LoadButton;
    QPushButton *RCCButton;
    QPushButton *SLFButton;
    QPushButton *pushButton;
    QPushButton *closeButtom;
    QLabel *label;
    QCustomPlot *HistPressPlot;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(877, 480);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(10, 60, 631, 161));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        customPlot->setFont(font);
        customPlot->setMouseTracking(false);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 0, 561, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        LoadButton = new QPushButton(horizontalLayoutWidget);
        LoadButton->setObjectName(QStringLiteral("LoadButton"));
        QIcon icon;
        icon.addFile(QStringLiteral("yellow-open-file-th.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoadButton->setIcon(icon);

        horizontalLayout->addWidget(LoadButton);

        RCCButton = new QPushButton(horizontalLayoutWidget);
        RCCButton->setObjectName(QStringLiteral("RCCButton"));
        RCCButton->setEnabled(true);

        horizontalLayout->addWidget(RCCButton);

        SLFButton = new QPushButton(horizontalLayoutWidget);
        SLFButton->setObjectName(QStringLiteral("SLFButton"));
        SLFButton->setEnabled(false);

        horizontalLayout->addWidget(SLFButton);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        closeButtom = new QPushButton(horizontalLayoutWidget);
        closeButtom->setObjectName(QStringLiteral("closeButtom"));

        horizontalLayout->addWidget(closeButtom);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 131, 17));
        HistPressPlot = new QCustomPlot(centralWidget);
        HistPressPlot->setObjectName(QStringLiteral("HistPressPlot"));
        HistPressPlot->setGeometry(QRect(650, 60, 211, 161));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(650, 40, 151, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 877, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "F-SNKE(R)", 0));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0));
        LoadButton->setText(QApplication::translate("MainWindow", "Load", 0));
        RCCButton->setText(QApplication::translate("MainWindow", "RCC Analysis", 0));
        SLFButton->setText(QApplication::translate("MainWindow", "SLF Analysis", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Reset", 0));
        closeButtom->setText(QApplication::translate("MainWindow", "Exit", 0));
        label->setText(QApplication::translate("MainWindow", "Pressure Spectrum", 0));
        label_2->setText(QApplication::translate("MainWindow", "Pressure Histogram", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
