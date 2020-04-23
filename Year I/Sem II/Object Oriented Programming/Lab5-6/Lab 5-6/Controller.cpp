#include "Controller.h"

void Controller::addMovieAsAdmin(Movie & movieToAdd)
{
	movieRepo.addMovieAsAdmin(movieToAdd);
}

void Controller::updateMovie(std::string & movieTitle, std::string & movieGenre, int releaseYear, int likes, std::string & trailer)
{
	movieRepo.updateMovie(movieTitle, movieGenre, releaseYear, likes, trailer);
}

void Controller::deleteMovie(std::string & movieTitle)
{
	movieRepo.deleteMovie(movieTitle);
}

void Controller::addMovieToWatchList(std::string & movieTitle)
{
	movieRepo.addMovieToWatchList(movieTitle);
}

void Controller::nextMovie()
{
	movieRepo.nextMovie();
}

DynamicVector<Movie> Controller::getAllMovies()
{
	return movieRepo.getAllMovies();
}

DynamicVector<Movie> Controller::getWatchList()
{
	return movieRepo.getWatchList();
}

Movie Controller::getCurrentMovie()
{
	return movieRepo.getCurrentMovie();
}
