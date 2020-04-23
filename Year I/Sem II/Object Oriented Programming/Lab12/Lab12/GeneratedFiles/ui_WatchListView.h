/********************************************************************************
** Form generated from reading UI file 'WatchListView.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WATCHLISTVIEW_H
#define UI_WATCHLISTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WatchList
{
public:
    QGridLayout *gridLayout;
    QTableView *watchlistData;

    void setupUi(QWidget *WatchList)
    {
        if (WatchList->objectName().isEmpty())
            WatchList->setObjectName(QString::fromUtf8("WatchList"));
        WatchList->resize(732, 476);
        gridLayout = new QGridLayout(WatchList);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        watchlistData = new QTableView(WatchList);
        watchlistData->setObjectName(QString::fromUtf8("watchlistData"));

        gridLayout->addWidget(watchlistData, 0, 0, 1, 1);


        retranslateUi(WatchList);

        QMetaObject::connectSlotsByName(WatchList);
    } // setupUi

    void retranslateUi(QWidget *WatchList)
    {
        WatchList->setWindowTitle(QApplication::translate("WatchList", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WatchList: public Ui_WatchList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WATCHLISTVIEW_H
