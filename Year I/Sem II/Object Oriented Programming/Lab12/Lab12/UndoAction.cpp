#include "UndoAction.h"

UndoRedoAdd::UndoRedoAdd(Movie movie, MovieRepository & repo) : repository(repo)
{
	this->addedMovie = movie;
}

void UndoRedoAdd::executeUndo()
{
	this->repository.deleteMovie(this->addedMovie);
}

void UndoRedoAdd::executeRedo()
{
	this->repository.addMovie(this->addedMovie);
}

UndoRedoDelete::UndoRedoDelete(Movie movie, MovieRepository & repo) : repository(repo)
{
	this->deletedMovie = movie;
}

void UndoRedoDelete::executeUndo()
{
	this->repository.addMovie(this->deletedMovie);
}

void UndoRedoDelete::executeRedo()
{
	this->repository.deleteMovie(this->deletedMovie);
}

UndoRedoAction::~UndoRedoAction()
{
}

UndoRedoUpdate::UndoRedoUpdate(Movie movie1, Movie movie2, MovieRepository & repo) : repository(repo)
{
	this->oldMovie = movie1;
	this->newMovie = movie2;
}

void UndoRedoUpdate::executeUndo()
{
	this->repository.updateMovie(this->oldMovie);
}

void UndoRedoUpdate::executeRedo()
{
	this->repository.updateMovie(this->newMovie);
}
