/********************************************************************************
** Form generated from reading UI file 'QtGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUI_H
#define UI_QTGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGUIClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QListWidget *weatherData;
    QHBoxLayout *horizontalLayout;
    QLineEdit *precipitationEdit;
    QPushButton *showAllButton;
    QPushButton *precipitationButton;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *descriptionEdit;
    QPushButton *descriptionButton;
    QLabel *timeData;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGUIClass)
    {
        if (QtGUIClass->objectName().isEmpty())
            QtGUIClass->setObjectName(QString::fromUtf8("QtGUIClass"));
        QtGUIClass->resize(600, 400);
        centralWidget = new QWidget(QtGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        weatherData = new QListWidget(centralWidget);
        weatherData->setObjectName(QString::fromUtf8("weatherData"));

        verticalLayout->addWidget(weatherData);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        precipitationEdit = new QLineEdit(centralWidget);
        precipitationEdit->setObjectName(QString::fromUtf8("precipitationEdit"));

        horizontalLayout->addWidget(precipitationEdit);

        showAllButton = new QPushButton(centralWidget);
        showAllButton->setObjectName(QString::fromUtf8("showAllButton"));

        horizontalLayout->addWidget(showAllButton);

        precipitationButton = new QPushButton(centralWidget);
        precipitationButton->setObjectName(QString::fromUtf8("precipitationButton"));

        horizontalLayout->addWidget(precipitationButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        descriptionEdit = new QLineEdit(centralWidget);
        descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));

        horizontalLayout_2->addWidget(descriptionEdit);

        descriptionButton = new QPushButton(centralWidget);
        descriptionButton->setObjectName(QString::fromUtf8("descriptionButton"));

        horizontalLayout_2->addWidget(descriptionButton);

        timeData = new QLabel(centralWidget);
        timeData->setObjectName(QString::fromUtf8("timeData"));
        timeData->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(timeData);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        QtGUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtGUIClass->setStatusBar(statusBar);

        retranslateUi(QtGUIClass);

        QMetaObject::connectSlotsByName(QtGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGUIClass)
    {
        QtGUIClass->setWindowTitle(QApplication::translate("QtGUIClass", "QtGUI", nullptr));
        showAllButton->setText(QApplication::translate("QtGUIClass", "Show All", nullptr));
        precipitationButton->setText(QApplication::translate("QtGUIClass", "Filter by Precipitation", nullptr));
        descriptionButton->setText(QApplication::translate("QtGUIClass", "Get Total Time", nullptr));
        timeData->setText(QApplication::translate("QtGUIClass", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGUIClass: public Ui_QtGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUI_H
