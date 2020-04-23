#pragma once
#include <iostream>
#include <string>

class Team
{
private:
	std::string name;
	std::string country;
	int score;

public:
	Team(); 

	Team(std::string &name, std::string &country, int score);

	int getScore();

	std::string getName();

	std::string getCountry();

	void setScore();

	std::string toStringTeam();

};