/********************************************************************************
** Form generated from reading UI file 'MovieGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOVIEGUI_H
#define UI_MOVIEGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MovieGUIClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MovieGUIClass)
    {
        if (MovieGUIClass->objectName().isEmpty())
            MovieGUIClass->setObjectName(QString::fromUtf8("MovieGUIClass"));
        MovieGUIClass->resize(600, 400);
        centralWidget = new QWidget(MovieGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MovieGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MovieGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 18));
        MovieGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MovieGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MovieGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MovieGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MovieGUIClass->setStatusBar(statusBar);

        retranslateUi(MovieGUIClass);

        QMetaObject::connectSlotsByName(MovieGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *MovieGUIClass)
    {
        MovieGUIClass->setWindowTitle(QApplication::translate("MovieGUIClass", "MovieGUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MovieGUIClass: public Ui_MovieGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOVIEGUI_H
