#pragma once

#include "Domain.h"
#include "Repo.h"
#include "Validator.h"

class Controller
{
private:
	FileRepository* adminList;
	FileRepository* userList;
	MovieValidator movieValidator;
	RepositoryValidator repoValidator;
	int currentMoviePosition;

public:
	// Mode A

	Controller();

	Controller(FileRepository* adminList);

	void addMovie(Movie movie);

	void updateMovie(Movie movie);

	void deleteMovie(std::string movieTitle);

	std::vector<Movie> getAllMovies() const;

	void loadMovieRepo(std::string filePath);

	// Mode B

	Movie nextMovie();

	void saveMovie(std::string movieTitle);

	std::vector<Movie> filterMoviesByGenreLikes(std::string genre, int likes);

	std::vector<Movie> filterMovieByLikes(int likes);

	std::vector<Movie> getWatchlist() const;

	void openWatchlist();

	void setUserListType(std::string filePath, std::string fileExtension);

};