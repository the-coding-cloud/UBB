#include "Validator.h"

MovieException::MovieException(std::string errorMessage)
{
	this->errorMessage = errorMessage;
}

std::string MovieException::getError() const noexcept
{
	return this->errorMessage;
}

void MovieValidator::validateMovie(Movie & movie)
{
	if (movie.getReleaseYear() <= 0 || movie.getTrailer().size() == 0)
		throw MovieException("Invalid movie");
}

void RepositoryValidator::validateAdd(Movie & movie, std::vector<Movie> movieList)
{
	if (existingElement(movie, movieList))
		throw MovieException("Existing movie");
}

void RepositoryValidator::validateUpdate(Movie & movie, std::vector<Movie> movieList)
{
	if (!existingElement(movie, movieList))
		throw MovieException("Inexisting movie");
}

void RepositoryValidator::validateDelete(std::string movieTitle, std::vector<Movie> movieList)
{
	for (Movie element : movieList)
	{
		if (movieTitle == element.getTitle())
			return;
	}

	throw MovieException("Inexisting movie"); }

bool RepositoryValidator::existingElement(Movie movie, std::vector<Movie> movieList)
{
	for (Movie element : movieList)
	{
		if (movie == element)
			return true;
	}

	return false;
}
