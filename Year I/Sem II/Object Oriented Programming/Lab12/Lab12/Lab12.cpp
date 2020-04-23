#include "Lab12.h"
#include <iostream>
#include "Domain.h"
#include "Validator.h"
#include <qshortcut.h>


using namespace std;

Lab12::Lab12(Controller & controller, QWidget *parent)
	: QMainWindow(parent), movieController(controller)
{
	this->watchlistModel = new UserModel{ movieController };

	ui.setupUi(this);

	QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QShortcut *shortcut2 = new QShortcut(QKeySequence("Ctrl+Y"), this);
	connect(shortcut, SIGNAL(activated()), this, SLOT(handleUndoButton()));
	connect(shortcut2, SIGNAL(activated()), this, SLOT(handleRedoButton()));

	connect(ui.addButton, SIGNAL(released()), this, SLOT(handleAddButton()));
	connect(ui.updateButton, SIGNAL(released()), this, SLOT(handleUpdateButton()));
	connect(ui.removeButton, SIGNAL(released()), this, SLOT(handleRemoveButton()));
	connect(ui.saveIDButton, SIGNAL(released()), this, SLOT(handleSaveIDButton()));
	connect(ui.saveFilepath, SIGNAL(released()), this, SLOT(handleSaveButton()));
	connect(ui.openExternallyButton, SIGNAL(released()), this, SLOT(handleOpenExternallyButton()));
	connect(ui.nextButton, SIGNAL(released()), this, SLOT(handleNextButton()));
	connect(ui.filterByLikesButton, SIGNAL(released()), this, SLOT(handleFilterByLikesButton()));
	connect(ui.filterByLikesGenreButton, SIGNAL(released()), this, SLOT(handleFilterByLikesGenreButton()));
	connect(ui.loadFilepathButton, SIGNAL(released()), this, SLOT(handleLoadFileButton()));

	connect(ui.showWatchlistButton, SIGNAL(released()), this, SLOT(handleShowWatchlist()));

	connect(ui.undoButton, SIGNAL(released()), this, SLOT(handleUndoButton()));
	connect(ui.redoButton, SIGNAL(released()), this, SLOT(handleRedoButton()));
}


void Lab12::handleAddButton()
{
	std::string movieTitle, movieGenre, trailer;
	int releaseYear, likes;

	movieTitle = ui.movieTitleEdit->text().toStdString();
	movieGenre = ui.movieGenreEdit->text().toStdString();
	releaseYear = ui.releaseYearEdit->text().toInt();
	likes = ui.likesEdit->text().toInt();
	trailer = ui.trailerEdit->text().toStdString();

	Movie movieToAdd{ movieTitle, movieGenre, releaseYear, likes, trailer };
	try
	{
		movieController.addMovie(movieToAdd);
	}
	catch (MovieException &exception)
	{
	}

	ui.movieDatabaseWidget->clear();
	populateAdminDatabase();

	ui.movieTitleEdit->clear();
	ui.movieGenreEdit->clear();
	ui.releaseYearEdit->clear();
	ui.likesEdit->clear();
	ui.trailerEdit->clear();

}

void Lab12::handleUpdateButton()
{
	std::string movieTitle, movieGenre, trailer;
	int releaseYear, likes;

	movieTitle = ui.movieTitleEdit->text().toStdString();
	movieGenre = ui.movieGenreEdit->text().toStdString();
	releaseYear = ui.releaseYearEdit->text().toInt();
	likes = ui.likesEdit->text().toInt();
	trailer = ui.trailerEdit->text().toStdString();

	Movie movieToUpdate{ movieTitle, movieGenre, releaseYear, likes, trailer };
	try
	{
		movieController.updateMovie(movieToUpdate);
	}
	catch (MovieException &exception)
	{
	}

	ui.movieDatabaseWidget->clear();
	populateAdminDatabase();

	ui.movieTitleEdit->clear();
	ui.movieGenreEdit->clear();
	ui.releaseYearEdit->clear();
	ui.likesEdit->clear();
	ui.trailerEdit->clear();
}

void Lab12::handleRemoveButton()
{
	std::string movieTitle;

	movieTitle = ui.movieTitleEdit->text().toStdString();

	try
	{
		movieController.deleteMovie(movieTitle);
	}
	catch (MovieException &exception)
	{
	}

	ui.movieDatabaseWidget->clear();
	populateAdminDatabase();

	ui.movieTitleEdit->clear();
	ui.movieGenreEdit->clear();
	ui.releaseYearEdit->clear();
	ui.likesEdit->clear();
	ui.trailerEdit->clear();
}

void Lab12::handleSaveIDButton()
{
	std::string movieTitle;

	movieTitle = ui.movieIDEdit->text().toStdString();

	try
	{
		movieController.saveMovie(movieTitle);

		this->watchlistModel->rowInserted();
	}
	catch (MovieException &exception)
	{
	}

	ui.movieIDEdit->clear();
}

void Lab12::handleSaveButton()
{
	std::string filePath;
	filePath = ui.filePathEdit->text().toStdString();
	std::string fileExtension = filePath.substr(filePath.find_last_of(".") + 1);
	movieController.setUserListType(filePath, fileExtension);

	ui.filePathEdit->clear();
}

void Lab12::handleOpenExternallyButton()
{
	movieController.openWatchlist();
}

void Lab12::handleNextButton()
{
	Movie currentMovie = movieController.nextMovie();
	ui.currentMovieData->clear();
	ui.currentMovieData->addItem(QString::fromStdString(currentMovie.toStringMovie()));
}

void Lab12::handleFilterByLikesButton()
{
	int likes = ui.likesFilterEdit->text().toInt();
	std::vector<Movie> filterResults = movieController.filterMovieByLikes(likes);
	ui.filterResultData->clear();
	for (Movie &movie : filterResults)
	{
		ui.filterResultData->addItem(QString::fromStdString(movie.toStringMovie()));
	}

	ui.likesFilterEdit->clear();
	ui.genreFilterEdit->clear();
}

void Lab12::handleFilterByLikesGenreButton()
{
	int likes = ui.likesEdit->text().toInt();
	std::string genre = ui.genreFilterEdit->text().toStdString();

	std::vector<Movie> filterResults = movieController.filterMoviesByGenreLikes(genre, likes);
	ui.filterResultData->clear();

	for (Movie &movie : filterResults)
	{
		ui.filterResultData->addItem(QString::fromStdString(movie.toStringMovie()));
	}

	ui.likesFilterEdit->clear();
	ui.genreFilterEdit->clear();
}

void Lab12::handleLoadFileButton()
{
	std::string filepath = ui.loadFilepathEdit->text().toStdString();

	movieController.loadMovieRepo(filepath);
	populateAdminDatabase();

	ui.loadFilepathEdit->clear();
}

void Lab12::handleUndoButton()
{
	bool executed = movieController.undo();

	if (!executed)
		ui.faceChestii->setText(QString::fromStdString("No more undo actions"));

	else
	{
		ui.movieDatabaseWidget->clear();
		populateAdminDatabase();
	}
}

void Lab12::handleRedoButton()
{
	bool executed = movieController.redo();

	if (!executed)
		ui.faceChestii->setText(QString::fromStdString("No more redo actions"));

	else
	{
		ui.movieDatabaseWidget->clear();
		populateAdminDatabase();
	}
}

void Lab12::handleShowWatchlist()
{
	watchlistModel = new UserModel(this->movieController);
	watchlistModel->reset();
	watchlistView = new UserView(watchlistModel);
	watchlistView->show();
}

void Lab12::populateAdminDatabase()
{
	for (Movie &movie : this->movieController.getAllMovies())
	{
		ui.movieDatabaseWidget->addItem(QString::fromStdString(movie.toStringMovie()));
	}
}
