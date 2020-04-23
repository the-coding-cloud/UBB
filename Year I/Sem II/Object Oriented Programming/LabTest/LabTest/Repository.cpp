#include "Repository.h"

Repository::Repository()
{
}

int Repository::addTeam(Team team)
/*
Function that adds a new team to the repo; checks if the team already exists
*/
{
	for (int index = 0; index < teamList.getSize(); index++)
		if (teamList[index].getName() == team.getName())
			return 0;

	teamList.addElement(team);
	return 1;
}

int Repository::getTeamByName(std::string name)
{
	for (int index = 0; index < teamList.getSize(); index++)
		if (teamList[index].getName() == name)
		{
			return index;
		}

	return -1;
}

DynamicVector<Team> Repository::getAllTeams()
{
	return teamList;
}

int Repository::checkEqualScores(int index1, int index2)
{
	if (teamList[index1].getScore() == teamList[index2].getScore())
		return 1;
	else
		return 0;
}

void Repository::setScore(int index)
{
	teamList[index].setScore();
}
