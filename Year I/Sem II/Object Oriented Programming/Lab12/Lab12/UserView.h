#pragma once

#include <QWidget>
#include "ui_WatchListView.h"

class UserView : public QWidget
{
	Q_OBJECT
private:
	QAbstractItemModel* model;
public:
	UserView(QAbstractItemModel* model, QWidget *parent = Q_NULLPTR);
	~UserView();

private:
	Ui::WatchList ui;
};
