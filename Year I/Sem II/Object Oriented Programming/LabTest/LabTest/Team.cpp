#include "Team.h"

Team::Team()
{

}

Team::Team(std::string &name, std::string &country, int score)
{
	this->name = name;
	this->country = country;
	this->score = score;
}

int Team::getScore()
{
	return this->score;
}

std::string Team::getName()
{
	return this->name;
}

std::string Team::getCountry()
{
	return this->country;
}

void Team::setScore()
{
	this->score += 1;
}

std::string Team::toStringTeam()
{
	std::string stringToPrint;
	stringToPrint = this->name;
	stringToPrint += "; ";
	stringToPrint += this->country;
	stringToPrint += "; ";
	stringToPrint += std::to_string(this->score);
	stringToPrint += "\n";

	return stringToPrint;
}