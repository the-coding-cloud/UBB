#pragma once
#include <iostream>
#include <vector>

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

	Movie(std::string& movieTitle);

	Movie(const Movie& movie);

	Movie operator= (const Movie& movie);

	bool operator== (const Movie& movie);

	void setTitle(std::string newMovieTitle);

	void setGenre(std::string& newMovieGenre);

	void setReleaseYear(int newReleaseYear);

	void setLikes(int newLikes);

	void setTrailer(std::string& newTrailer);

	std::string getTitle();

	std::string getGenre();

	int getReleaseYear();

	int getLikes();

	std::string getTrailer();
	
	std::string toStringMovie();

	friend std::istream& operator>>(std::istream& inputStream, Movie& movie);

};