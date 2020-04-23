#pragma once

#include "Domain.h"
#include "Repo.h"
#include "Validator.h"
#include "UndoAction.h"

class Controller
{
private:
	FileRepository* adminList;
	FileRepository* userList;
	MovieValidator movieValidator;
	RepositoryValidator repoValidator;
	int currentMoviePosition;

	std::vector<std::unique_ptr<UndoRedoAction>> undoRedoActions;
	int currentActionPosition;
	void deleteRedo();

public:
	// Mode A

	Controller();

	void addMovie(Movie movie);

	void updateMovie(Movie movie);

	void deleteMovie(std::string movieTitle);

	std::vector<Movie> getAllMovies() const;

	void loadMovieRepo(std::string filePath);

	bool undo();

	bool redo();

	// Mode B

	Movie nextMovie();

	void saveMovie(std::string movieTitle);

	std::vector<Movie> filterMoviesByGenreLikes(std::string genre, int likes);

	std::vector<Movie> filterMovieByLikes(int likes);

	std::vector<Movie> getWatchlist() const;

	void openWatchlist();

	void setUserListType(std::string filePath, std::string fileExtension);

};