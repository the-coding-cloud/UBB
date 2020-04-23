#pragma once
#include "DynamicVector.h"
#include "Team.h"

class Repository
{
private:
	DynamicVector<Team> teamList;

public:
	Repository();
	int addTeam(Team team);

	void sortList();

	int getTeamByName(std::string name);

	DynamicVector<Team> getAllTeams();

	int checkEqualScores(int index1, int index2);

	void setScore(int index);


};