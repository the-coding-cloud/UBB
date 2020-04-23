#include "Domain.h"
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

Movie::Movie() : movieTitle(""), movieGenre(""), releaseYear(0), likes(0), trailer("")
{
}

Movie::Movie(std::string & movieTitle, std::string & movieGenre, int releaseYear, int likes, std::string & trailer)
{
	this->movieTitle = movieTitle;
	this->movieGenre = movieGenre;
	this->releaseYear = releaseYear;
	this->likes = likes;
	this->trailer = trailer;
}

Movie::Movie(std::string & movieTitle)
{
	this->movieTitle = movieTitle;
	this->movieGenre = "";
	this->releaseYear = 0;
	this->likes = 0;
	this->trailer = "";
}

Movie::Movie(const Movie & movie)
{
	this->movieTitle = movie.movieTitle;
	this->movieGenre = movie.movieGenre;
	this->releaseYear = movie.releaseYear;
	this->likes = movie.likes;
	this->trailer = movie.trailer;
}

Movie Movie::operator=(const Movie & movie)
{
	this->movieTitle = movie.movieTitle;
	this->movieGenre = movie.movieGenre;
	this->releaseYear = movie.releaseYear;
	this->likes = movie.likes;
	this->trailer = movie.trailer;

	return *this;
}

bool Movie::operator==(const Movie & movie)
{
	if (this->movieTitle == movie.movieTitle)
		return true;

	return false;
}

void Movie::setGenre(std::string & newMovieGenre)
{
	this->movieGenre = newMovieGenre;
}

void Movie::setReleaseYear(int newReleaseYear)
{
	this->releaseYear = newReleaseYear;
}

void Movie::setLikes(int newLikes)
{
	this->likes = newLikes;
}

void Movie::setTrailer(std::string & newTrailer)
{
	this->trailer = newTrailer;
}

std::string Movie::getTitle()
{
	return this->movieTitle;
}

std::string Movie::getGenre()
{
	return this->movieGenre;
}

int Movie::getReleaseYear()
{
	return this->releaseYear;
}

int Movie::getLikes()
{
	return this->likes;
}

std::string Movie::getTrailer()
{
	return this->trailer;
}

std::string Movie::toStringMovie()
{
	std::string movieData = "";

	movieData += this->movieTitle;
	movieData += "; ";
	movieData += this->movieGenre;
	movieData += "; ";
	movieData += std::to_string(this->releaseYear);
	movieData += "; ";
	movieData += std::to_string(this->likes);
	movieData += "; ";
	movieData += this->trailer;

	return movieData;
}

std::vector<std::string> tokenize(std::string stringToBeRead, char delimiter)
{
	std::vector <std::string> result;
	std::stringstream ss(stringToBeRead);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream & operator>>(std::istream & inputStream, Movie & movie)
{
	std::string line;
	getline(inputStream, line);

	std::vector<std::string> tokens = tokenize(line, ',');
	if (tokens.size() != 5)
		return inputStream;
	movie.movieTitle = tokens[0];
	movie.movieGenre = tokens[1];
	std::string::size_type sizeType;
	movie.releaseYear = std::stoi(tokens[2], &sizeType);
	movie.likes = std::stoi(tokens[3], &sizeType);
	movie.trailer = tokens[4];

	return inputStream;
}
