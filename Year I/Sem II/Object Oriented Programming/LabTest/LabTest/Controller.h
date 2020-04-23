#pragma once
#include "Repository.h"

class Controller
{
private:
	Repository teamRepo;

public:
	Controller();
	int addTeam(std::string name, std::string country);
	DynamicVector<Team> getAllTeams();
	int pairTeams(std::string teamName1, std::string teamName2, std::string winningTeam);

};