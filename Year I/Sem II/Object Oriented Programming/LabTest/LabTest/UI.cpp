#include "UI.h"

using namespace std;

UI::UI()
{
}

void UI::UIAdd()
{
	char command[256];
	cout << "Enter name: ";
	fgets(command, sizeof(command), stdin);
	std::string name = command;
	
	cout << "Enter country: ";
	fgets(command, sizeof(command), stdin);
	std::string country = command;

	if (controller.addTeam(name, country) == 1)
		cout << "Team was added\n";
	else
		cout << "Incorrect input\n";

}

void UI::UIShowAll()
{
	DynamicVector<Team> allTeams = controller.getAllTeams();
	for (int index = 0; index < allTeams.getSize(); index++)
		cout << allTeams[index].toStringTeam();
}

void UI::UIPair()
{
	char command[256];
	cout << "Enter team 1: ";
	fgets(command, sizeof(command), stdin);
	std::string team1 = command;

	cout << "Enter team 2: ";
	fgets(command, sizeof(command), stdin);
	std::string team2 = command;

	cout << "Enter winning team: ";
	fgets(command, sizeof(command), stdin);
	std::string winningTeam = command;

	if (controller.pairTeams(team1, team2, winningTeam) == 1)
		cout << "Paired";
	else
		cout << "Wrong input";
}

void UI::run()
{
	while (true)
	{
		cout << "1. Add team\n2. Show all teams\n3. Pair 2 teams\nEnter command: ";
		char command[10];
		fgets(command, sizeof(command), stdin);

		if (command[0] == '1')
			UIAdd();
		else if (command[0] == '2')
			UIShowAll();
		else if (command[0] == '3')
			UIPair();
		else
			return;
	}
}
