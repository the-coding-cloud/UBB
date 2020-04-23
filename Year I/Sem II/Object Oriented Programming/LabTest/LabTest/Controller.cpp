#include "Controller.h"

Controller::Controller()
{
}

int Controller::addTeam(std::string name, std::string country)
{
	Team newTeam = Team(name, country, 0);
	return teamRepo.addTeam(newTeam);
	
}

DynamicVector<Team> Controller::getAllTeams()
// function that retrieves all teams
{
	return teamRepo.getAllTeams();
}

int Controller::pairTeams(std::string teamName1, std::string teamName2, std::string winningTeam)
{
	int index1 = teamRepo.getTeamByName(teamName1);
	int index2 = teamRepo.getTeamByName(teamName2);

	if (teamRepo.checkEqualScores(index1, index2) == 1)
	{
		teamRepo.setScore(teamRepo.getTeamByName(winningTeam));
		return 1;
	}
	else
		return 0;

}