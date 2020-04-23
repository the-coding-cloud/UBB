#pragma once
#include <iostream>

class Movie
{
private:
	std::string movieTitle;
	std::string movieGenre;
	int releaseYear;
	int likes;
	std::string trailer;

public:
	Movie();

	Movie(std::string& movieTitle, std::string& movieGenre, int releaseYear, int likes, std::string& trailer);

	Movie(const Movie& movie);

	Movie operator= (const Movie& movie);

	bool operator== (const Movie& movie);

	void setGenre(std::string& newMovieGenre);

	void setReleaseYear(int newReleaseYear);

	void setLikes(int newLikes);

	void setTrailer(std::string& newTrailer);

	std::string getTitle();

	std::string getGenre();

	int getReleaseYear();

	int getLikes();
	
	std::string toStringMovie();

};