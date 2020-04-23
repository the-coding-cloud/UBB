#include "Repo.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <fstream>

using namespace std;

void MovieRepository::addMovie(Movie newMovie)
{
	this->movieList.push_back(newMovie);
}

void MovieRepository::updateMovie(Movie newMovie)
{
	auto movieIterator = std::find(this->movieList.begin(), this->movieList.end(), newMovie);

	if (movieIterator != this->movieList.end())
	{
		this->movieList.at(movieIterator - this->movieList.begin()) = newMovie;
	}
}

void MovieRepository::deleteMovie(Movie movieToDelete)
{
	auto movieIterator = std::find(this->movieList.begin(), this->movieList.end(), movieToDelete);

	if (movieIterator != this->movieList.end())
	{
		this->movieList.erase(movieIterator);
	}
}

std::vector<Movie> MovieRepository::getAllMovies() const
{
	return this->movieList;
}

int MovieRepository::getNumberOfMovies()
{
	return this->movieList.size();
}

std::vector<Movie> MovieRepository::filterMoviesByGenreLikes(std::string genre, int likes)
{
	std::vector<Movie> filteredMovies(this->movieList.size());
	auto movieIterator = std::copy_if(this->movieList.begin(), this->movieList.end(), filteredMovies.begin(), [genre, likes](Movie movie) {return (movie.getGenre().find(genre) != string::npos && movie.getLikes() >= likes); });
	filteredMovies.resize(std::distance(filteredMovies.begin(), movieIterator));
	return filteredMovies;
}

std::vector<Movie> MovieRepository::filterMoviesByLikes(int likes)
{
	std::vector<Movie> filteredMovies(this->movieList.size());
	auto movieIterator = std::copy_if(this->movieList.begin(), this->movieList.end(), filteredMovies.begin(), [likes](Movie movie) {return (movie.getLikes() >= likes); });
	filteredMovies.resize(std::distance(filteredMovies.begin(), movieIterator));
	return filteredMovies;
}

Movie MovieRepository::getMovieByPosition(int position)
{
	return this->movieList[position];
}

Movie MovieRepository::getMovieByTitle(std::string movieTitle)
{
	for (Movie element : movieList)
	{
		if (movieTitle == element.getTitle())
			return element;
	}
}

void FileRepository::setPath(std::string filePath)
{
	this->filePath = filePath;
}

void FileRepository::openFile()
{
	system(this->filePath.c_str());
}

void TXTRepository::readFromFile(std::string filePath)
{
	/*
	this->filePath = filePath;
	bool exists;

	//checks if the file exists
	if (FILE *file = fopen(filePath.c_str(), "r")) {
		fclose(file);
		exists = true;
	}
	else {
		exists = false;
	}

	//reads from it if it exists
	if (exists)
	{
		ifstream file(filePath);
		if (!file.is_open())return;

		Movie movie = Movie();
		while (file >> movie)
		{
			addMovie(movie);
		}
		file.close();
	}

	//creates new file otherwise
	else
	{
		ofstream file;
		file.open(filePath.c_str());
		file.close();
	}
	*/

	this->filePath = filePath;
	ifstream file(filePath);
	if (!file.is_open())return;

	Movie movie = Movie();
	while (file >> movie)
	{
		addMovie(movie);
	}
	file.close();
}

void TXTRepository::writeToFile()
{
	ofstream file(this->filePath);
	if (!file.is_open())return;

	for (auto movie : getAllMovies())
	{
		file << movie.getTitle().c_str() << "," << movie.getGenre().c_str() << "," << movie.getReleaseYear() << "," << movie.getLikes() << "," << movie.getTrailer().c_str() << "\n";
	}

	file.close();
}

void CSVRepository::writeToFile()
{
	ofstream file(this->filePath);
	if (!file.is_open())return;

	for (auto movie : getAllMovies())
	{
		file << movie.getTitle().c_str() << "," << movie.getGenre().c_str() << "," << movie.getReleaseYear() << "," << movie.getLikes() << "," << movie.getTrailer().c_str() << "\n";
	}

	file.close();
}

void HTMLRepository::writeToFile()
{
	ofstream file(this->filePath);
	if (!file.is_open()) return;

	file << "<!DOCTYPE html>";
	file << "<html>";
	file << "	<head>";
	file << "		<title>Movies</title>";
	file << "	</head>";
	file << "	<body>";
	file << "		<table border=" << char(34) << "1" << char(34) << ">";
	file << "		<tr>";
	file << "			<td>Title</td>";
	file << "			<td>Genre</td>";
	file << "			<td>Release Year</td>";
	file << "			<td>Likes</td>";
	file << "			<td>Trailer</td>";
	file << "		</tr>";

	for (auto movie : getAllMovies()) {
		file << "		<tr>";
		file << "			<td>" << movie.getTitle().c_str() << "</td>";
		file << "			<td>" << movie.getGenre().c_str() << "</td>";
		file << "			<td>" << movie.getReleaseYear() << "</td>";
		file << "			<td>" << movie.getLikes() << "</td>";
		file << "			<td>" << movie.getTrailer().c_str() << "</td>";
		file << "		</tr>";
	}
	file << "		</table>";
	file << "	</body>";
	file << "</html>";
	file.close();

}
