#pragma once
#include "Repository.h"
#include "Domain.h"

class Controller
{
private:
	MovieRepository movieRepo;

public:
	Controller() {};

	void addMovieAsAdmin(Movie& movieToAdd);

	void updateMovie(std::string & movieTitle, std::string & movieGenre, int releaseYear, int likes, std::string & trailer);

	void deleteMovie(std::string & movieTitle);

	void addMovieToWatchList(std::string & movieTitle);

	void nextMovie();

	DynamicVector<Movie> getAllMovies();

	DynamicVector<Movie> getWatchList();

	Movie getCurrentMovie();
};