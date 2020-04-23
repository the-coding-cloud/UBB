#pragma once
#include "Controller.h"
#include "Domain.h"
#include <iostream>
#include <string>

class UI
{
private:
	Controller controller;
	int mode;

public:

	UI() : mode(0) {}

	bool checkIfNumber(std::string& stringToCheck);

	void UIAddMovieAsAdmin(Movie& movieToAdd);

	void UIUpdateMovie(std::string& movieTitle, std::string& movieGenre, int releaseYear, int likes, std::string& trailer);

	void UIDeleteMovie(std::string & movieTitle);

	void UIAddMovieToWatchList(std::string & movieTitle);

	void UIListAll();

	void UIListGenreLikes(std::string & movieGenre, int likes);

	void UIListWatchList();

	void UINext();

	void UIPrintAdminMenu();

	void UIPrintUserMenu();

	void run();

};