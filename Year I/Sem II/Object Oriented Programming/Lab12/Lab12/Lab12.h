#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab12.h"
#include "Controller.h"
#include "UserModel.h"
#include "UserView.h"

class Lab12 : public QMainWindow
{
	Q_OBJECT

public:
	Lab12(Controller & controller, QWidget *parent = Q_NULLPTR);

private:
	Controller & movieController;
	UserModel *watchlistModel;
	UserView *watchlistView;

private slots:
	void handleAddButton();
	void handleUpdateButton();
	void handleRemoveButton();
	void handleSaveIDButton();
	void handleSaveButton();
	void handleOpenExternallyButton();
	void handleNextButton();
	void handleFilterByLikesButton();
	void handleFilterByLikesGenreButton();
	void handleLoadFileButton();
	void handleUndoButton();
	void handleRedoButton();

	void handleShowWatchlist();

private:
	Ui::Lab12Class ui;

	void populateAdminDatabase();
};
