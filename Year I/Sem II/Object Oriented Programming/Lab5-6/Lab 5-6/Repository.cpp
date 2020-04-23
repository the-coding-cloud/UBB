#include "Repository.h"

void MovieRepository::addMovieAsAdmin(Movie movieToAdd)
{
	int index = this->searchMovieInAdminList(movieToAdd);

	if (index == -1)
		adminMovieList.addElement(movieToAdd);
}

void MovieRepository::updateMovie(std::string & movieTitle, std::string & movieGenre, int releaseYear, int likes, std::string & trailer)
{
	for (int index = 0; index < this->adminMovieList.getSize(); index++)
		if (this->adminMovieList[index].getTitle() == movieTitle)
		{
			this->adminMovieList[index].setGenre(movieGenre);
			this->adminMovieList[index].setReleaseYear(releaseYear);
			this->adminMovieList[index].setLikes(likes);
			this->adminMovieList[index].setTrailer(trailer);
			break;
		}
}

void MovieRepository::deleteMovie(std::string & movieTitle)
{
	for (int index = 0; index < this->adminMovieList.getSize(); index++)
		if (this->adminMovieList[index].getTitle() == movieTitle)
		{
			this->adminMovieList.deleteElement(this->adminMovieList[index]);
			break;
		}
}
int MovieRepository::searchMovieInAdminList(Movie& movie)
{

	for (int index = 0; index < this->adminMovieList.getSize(); index++)
		if (this->adminMovieList[index] == movie)
			return index;

	return -1;
}

int MovieRepository::searchMovieInWatchList(Movie& movie)
{
	for (int index = 0; index < this->userWatchList.getSize(); index++)
		if (this->userWatchList[index] == movie)
			return index;

	return -1;
}

void MovieRepository::addMovieToWatchList(std::string & movieTitle)
{
	Movie movieToAdd = getMovieByTitle(movieTitle);
	int index = this->searchMovieInWatchList(movieToAdd);

	if (index == -1)
		userWatchList.addElement(movieToAdd);
}

void MovieRepository::nextMovie()
{
	currentIndex++;

	if (currentIndex >= adminMovieList.getSize())
		currentIndex = 0;
}

Movie MovieRepository::getCurrentMovie()
{
	return adminMovieList[currentIndex];
}


Movie MovieRepository::getMovieByTitle(std::string & movieTitle)
{
	for (int index = 0; index < this->adminMovieList.getSize(); index++)
		if (this->adminMovieList[index].getTitle() == movieTitle)
			return this->adminMovieList[index];
}

DynamicVector<Movie> MovieRepository::getAllMovies()
{
	return DynamicVector<Movie>(adminMovieList);
}

DynamicVector<Movie> MovieRepository::getWatchList()
{
	return DynamicVector<Movie>(userWatchList);
}
