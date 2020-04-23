#include "Controller.h"

Controller::Controller()
{
	this->adminList = new TXTRepository();
	this->userList = new TXTRepository();
	this->movieValidator = MovieValidator();
	this->repoValidator = RepositoryValidator();
	this->currentMoviePosition = 0;
}

void Controller::addMovie(Movie movie)
{
	this->movieValidator.validateMovie(movie);
	this->repoValidator.validateAdd(movie, adminList->getAllMovies());
	adminList->addMovie(movie);
	adminList->writeToFile();
}

void Controller::updateMovie(Movie movie)
{
	this->movieValidator.validateMovie(movie);
	this->repoValidator.validateUpdate(movie, adminList->getAllMovies());
	adminList->updateMovie(movie);
	adminList->writeToFile();
}

void Controller::deleteMovie(std::string movieTitle)
{
	this->repoValidator.validateDelete(movieTitle, adminList->getAllMovies());
	Movie movieToDelete = Movie(movieTitle);
	adminList->deleteMovie(movieToDelete);
	adminList->writeToFile();
}

std::vector<Movie> Controller::getAllMovies() const
{
	return adminList->getAllMovies();
}

void Controller::loadMovieRepo(std::string filePath)
{
	this->adminList->readFromFile(filePath);
}

Movie Controller::nextMovie()
{
	currentMoviePosition++;
	if (currentMoviePosition < adminList->getNumberOfMovies())
		return adminList->getMovieByPosition(currentMoviePosition);
	else
	{
		currentMoviePosition = 0;
		return adminList->getMovieByPosition(currentMoviePosition);
	}
}

void Controller::saveMovie(std::string movieTitle)
{
	Movie movieToWatch = adminList->getMovieByTitle(movieTitle);
	this->repoValidator.validateAdd(movieToWatch, userList->getAllMovies());
	userList->addMovie(movieToWatch);
	userList->writeToFile();
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
	if (fileExtension == "csv") 
	{
		delete this->userList;
		this->userList = new CSVRepository();
	}
	else 
	{
		if (fileExtension == "html") 
		{
			delete this->userList;
			this->userList = new HTMLRepository();
		}
	}
	userList->setPath(filePath);
}