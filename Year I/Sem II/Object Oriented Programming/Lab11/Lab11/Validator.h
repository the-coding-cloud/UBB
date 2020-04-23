#pragma once
#include "Domain.h"
#include "Repo.h"
#include <string>

class MovieException : public std::exception {
private:
	std::string errorMessage;
public:
	MovieException(std::string errorMessage);
	std::string getError() const noexcept;
};

class MovieValidator {
public:
	static void validateMovie(Movie& movie);
};

class RepositoryValidator {
public:
	void validateAdd(Movie& movie, std::vector<Movie> movieList);
	void validateUpdate(Movie& movie, std::vector<Movie> movieList);
	void validateDelete(std::string movieTitle, std::vector<Movie> movieList);
	bool existingElement(Movie movie, std::vector<Movie> vectorOfElements);
};