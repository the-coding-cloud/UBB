#pragma once
#include "Controller.h"
#include "Domain.h"

class Console {
private:
	Controller controller;
public:
	bool checkIfNumber(std::string& stringToCheck);

	void UIAddMovie(char* parameters);

	void UIUpdateMovie(char* parameters);
	
	void UIDeleteMovie(char* parameters);
	
	void UIListAll();
	
	void UINext();
	
	void UIFilter(char* parameters);
	
	void UIAddToWatchlist(char* parameters);
	
	void UISetFilePath(char* parameters);
	
	void UIWatchlistLocation(char* parameters);
	
	void UIListWatchlist();
	
	void run();
};

//run the app
//set initial location
//set mylist location
//DECIDE TYPE OF WATCHLIST!!!
//ensure you write into the file each time you add smth into the watchlist