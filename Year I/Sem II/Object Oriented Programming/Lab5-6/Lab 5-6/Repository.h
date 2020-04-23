#pragma once
#include "DynamicVectorIterator.h"
#include "DynamicVector.h"
#include "Domain.h"

class MovieRepository
{
private:
	DynamicVector<Movie> adminMovieList;
	DynamicVector<Movie> userWatchList;
	int currentIndex;

public:

	MovieRepository(): currentIndex(0) {}
	
	void addMovieAsAdmin(Movie movieToAdd);

	void updateMovie(std::string& movieTitle, std::string& movieGenre, int releaseYear, int likes, std::string& trailer);

	void deleteMovie(std::string& movieTitle);

	int searchMovieInAdminList(Movie& movie);

	int searchMovieInWatchList(Movie& movie);

	void addMovieToWatchList(std::string & movieTitle);

	void nextMovie();

	Movie getCurrentMovie();

	Movie getMovieByTitle(std::string& movieTitle);

	DynamicVector<Movie> getAllMovies();

	DynamicVector<Movie> getWatchList();

};