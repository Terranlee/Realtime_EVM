/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *Set;
    QPushButton *Begin;
    QLabel *show_area;
    QLabel *if_face;
    QPushButton *Stop;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(550, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Set = new QPushButton(centralWidget);
        Set->setObjectName(QStringLiteral("Set"));
        Set->setGeometry(QRect(449, 20, 91, 23));
        Begin = new QPushButton(centralWidget);
        Begin->setObjectName(QStringLiteral("Begin"));
        Begin->setGeometry(QRect(449, 60, 91, 23));
        show_area = new QLabel(centralWidget);
        show_area->setObjectName(QStringLiteral("show_area"));
        show_area->setGeometry(QRect(50, 30, 350, 350));
        if_face = new QLabel(centralWidget);
        if_face->setObjectName(QStringLiteral("if_face"));
        if_face->setGeometry(QRect(450, 160, 81, 81));
        Stop = new QPushButton(centralWidget);
        Stop->setObjectName(QStringLiteral("Stop"));
        Stop->setGeometry(QRect(450, 100, 91, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 550, 28));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Set->setText(QApplication::translate("MainWindow", "Set", 0));
        Begin->setText(QApplication::translate("MainWindow", "Begin", 0));
        show_area->setText(QString());
        if_face->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        Stop->setText(QApplication::translate("MainWindow", "Stop", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
