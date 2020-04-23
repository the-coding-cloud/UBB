#include "Controller.h"
#include <memory>

using namespace std;

void Controller::deleteRedo()
{
	if (undoRedoActions.size() > 0 && currentActionPosition < undoRedoActions.size())
	this->undoRedoActions.erase(this->undoRedoActions.begin() + currentActionPosition + 1, this->undoRedoActions.end());
}

Controller::Controller()
{
	this->adminList = new TXTRepository();
	this->userList = new TXTRepository();
	this->movieValidator = MovieValidator();
	this->repoValidator = RepositoryValidator();
	this->currentMoviePosition = 0;
	this->currentActionPosition = -1;
}

void Controller::addMovie(Movie movie)
{
	this->movieValidator.validateMovie(movie);
	this->repoValidator.validateAdd(movie, adminList->getAllMovies());
	adminList->addMovie(movie);

	this->deleteRedo();

	UndoRedoAdd undoRedoAddOperation = UndoRedoAdd(movie, *adminList);
	unique_ptr<UndoRedoAction> pointer = std::make_unique<UndoRedoAdd>(undoRedoAddOperation);
	this->undoRedoActions.push_back(std::move(pointer));
	this->currentActionPosition += 1;
	
}

void Controller::updateMovie(Movie movie)
{
	this->movieValidator.validateMovie(movie);
	this->repoValidator.validateUpdate(movie, adminList->getAllMovies());

	Movie oldMovie = adminList->getMovieByTitle(movie.getTitle());
	adminList->updateMovie(movie);


	this->deleteRedo();

	UndoRedoUpdate undoRedoAddOperation = UndoRedoUpdate(oldMovie, movie, *adminList);
	unique_ptr<UndoRedoAction> pointer = std::make_unique<UndoRedoUpdate>(undoRedoAddOperation);
	this->undoRedoActions.push_back(std::move(pointer));
	this->currentActionPosition += 1;
}

void Controller::deleteMovie(std::string movieTitle)
{
	this->repoValidator.validateDelete(movieTitle, adminList->getAllMovies());
	Movie movieToDelete = adminList->getMovieByTitle(movieTitle);
	adminList->deleteMovie(movieToDelete);

	this->deleteRedo();

	UndoRedoDelete undoRedoAddOperation = UndoRedoDelete(movieToDelete, *adminList);
	unique_ptr<UndoRedoAction> pointer = std::make_unique<UndoRedoDelete>(undoRedoAddOperation);
	this->undoRedoActions.push_back(std::move(pointer));
	this->currentActionPosition += 1;
}

std::vector<Movie> Controller::getAllMovies() const
{
	return adminList->getAllMovies();
}

void Controller::loadMovieRepo(std::string filePath)
{
	this->adminList->readFromFile(filePath);
}

bool Controller::undo()
{
	if (currentActionPosition >= 0)
	{
		this->undoRedoActions[currentActionPosition]->executeUndo();

		this->currentActionPosition -= 1;

		return true;
	}

	else
		return false;
}

bool Controller::redo()
{
	if (this->currentActionPosition != this->undoRedoActions.size() - 1)
	{
		this->currentActionPosition += 1;

		this->undoRedoActions[currentActionPosition]->executeRedo();

		return true;
	}

	else
		return false;
}

Movie Controller::nextMovie()
{
	currentMoviePosition++;
	if (currentMoviePosition < adminList->getNumberOfMovies())
		return adminList->getMovieByPosition(currentMoviePosition);

	currentMoviePosition = 0;
	return adminList->getMovieByPosition(currentMoviePosition);

}

void Controller::saveMovie(std::string movieTitle)
{
	Movie movieToWatch = adminList->getMovieByTitle(movieTitle);
	this->repoValidator.validateAdd(movieToWatch, userList->getAllMovies());
	userList->addMovie(movieToWatch);
}

std::vector<Movie> Controller::filterMoviesByGenreLikes(std::string genre, int likes)
{
	return adminList->filterMoviesByGenreLikes(genre, likes);
}

std::vector<Movie> Controller::filterMovieByLikes(int likes)
{
	return adminList->filterMoviesByLikes(likes);
}

std::vector<Movie> Controller::getWatchlist() const
{
	return userList->getAllMovies();
}

void Controller::openWatchlist()
{
	this->userList->openFile();
}

void Controller::setUserListType(std::string filePath, std::string fileExtension)
{
	if (strcmp(fileExtension.c_str(), "csv") == 0) 
	{
		//delete[] this->userList;
		this->userList = new CSVRepository();
	}
	else 
	{
		if (strcmp(fileExtension.c_str(), "html") == 0)
		{
			//delete[] this->userList;
			this->userList = new HTMLRepository();
		}
	}
	userList->setPath(filePath);
}