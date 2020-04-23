#pragma once
#include "Domain.h"
#include <vector>

class MovieRepository {
protected:
	std::vector<Movie> movieList;
public:
	MovieRepository() {};

	void addMovie(Movie newMovie);

	void updateMovie(Movie newMovie);

	void deleteMovie(Movie movieToDelete);

	std::vector<Movie> getAllMovies() const;

	int getNumberOfMovies();

	std::vector<Movie> filterMoviesByGenreLikes(std::string genre, int likes);

	virtual std::vector<Movie> filterMoviesByLikes(int likes);

	Movie getMovieByPosition(int position);

	Movie getMovieByTitle(std::string movieTitle);
};

class FileRepository : public MovieRepository {
protected:
	std::string filePath;
public:
	void setPath(std::string filePath);
	void openFile();
	virtual void readFromFile(std::string filePath) = 0;
	virtual void writeToFile() = 0;
};

class TXTRepository : public FileRepository {
public:
	void readFromFile(std::string filePath);
	void writeToFile();
};

class CSVRepository : public FileRepository {
public:
	void readFromFile(std::string filePath) { return; }
	void writeToFile();
};

class HTMLRepository : public FileRepository {
public:
	void readFromFile(std::string filePath) { return; }
	void writeToFile();
};

class FakeRepository : public FileRepository {
public:
	void readFromFile(std::string filePath) { return; }
	void writeToFile() { return; }
	std::vector<Movie> filterMoviesByLikes(int likes);
};