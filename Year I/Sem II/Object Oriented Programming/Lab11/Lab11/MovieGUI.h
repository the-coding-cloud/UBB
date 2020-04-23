#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MovieGUI.h"
#include "Controller.h"
#include "Domain.h"
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qbuttongroup.h>
#include "C:\Qt\5.12.3\msvc2017_64\include\QtWidgets\qwidget.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <iostream>
#include <vector>
#include <algorithm>

class MovieGUI : public QMainWindow
{
	Q_OBJECT

private:

public:
	MovieGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::MovieGUIClass ui;
};

class basicGUI : public QWidget
{
private:
	Controller & movieController;
	QListWidget *movieData, *userData;
	QLineEdit *movieTitle, *movieGenre, *releaseYear, *likes, *trailer;
	QPushButton *addButton, *removeButton, *updateButton;
	void makeLayout();
	void retrieveAdminData();
public:
	basicGUI(Controller & controller);
	~basicGUI();
};
