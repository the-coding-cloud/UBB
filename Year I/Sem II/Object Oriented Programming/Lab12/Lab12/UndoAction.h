#pragma once
#include "Domain.h"
#include "Repo.h"
class UndoRedoAction
{
public:
	virtual ~UndoRedoAction();
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
};

class UndoRedoAdd : public UndoRedoAction
{
private:
	Movie addedMovie;
	MovieRepository & repository;

public:
	UndoRedoAdd(Movie movie, MovieRepository & repo);
	void executeUndo();
	void executeRedo();
};

class UndoRedoDelete : public UndoRedoAction
{
private:
	Movie deletedMovie;
	MovieRepository & repository;

public:
	UndoRedoDelete(Movie movie, MovieRepository & repo);
	void executeUndo();
	void executeRedo();
};

class UndoRedoUpdate : public UndoRedoAction
{
private:
	Movie oldMovie, newMovie;
	MovieRepository & repository;

public:
	UndoRedoUpdate(Movie movie1, Movie movie2, MovieRepository & repo);
	void executeUndo();
	void executeRedo();
};