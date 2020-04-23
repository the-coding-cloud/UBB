#include "UI.h"

using namespace std;

void UI::UIAdd()
{
	cout << "pick the type\n";
	char token[100];
	cin.getline(token, 100);
	if (strcmp(token, "block") == 0)
	{
		std::string address;
		int year, totalApt, occupiedApt;

		cin.getline(token,100);
		address = token;
		cin.getline(token, 100);
		year = atoi(token);
		cin.getline(token, 100);
		totalApt = atoi(token);
		cin.getline(token, 100);
		occupiedApt = atoi(token);

		Block * block = new Block(address, year, totalApt, occupiedApt);

		controller.addBuilding(block);
	}

	else if (strcmp(token, "house") == 0)
	{
		std::string address, type;
		int year;
		bool isHistorical;

		cin.getline(token, 100);
		address = token;
		cin.getline(token, 100);
		year = atoi(token);
		cin.getline(token, 100);
		type = token;
		cin.getline(token, 100);
		if (strcmp(token, "yes") == 0)
			isHistorical = true;
		else
			isHistorical = false;

		House * house = new House(address, year, type, isHistorical);

		controller.addBuilding(house);
	}


}

void UI::UIShowAll()
{
	for (auto building : this->controller.getAllBuildings())
		cout << building->toString().c_str() << endl;
}

void UI::UIFilter()
{
	for (auto building : this->controller.getAllToBeRestored())
		cout << building->toString().c_str() << endl;
}

void UI::UIWriteToFile()
{
	char token[100];
	cin.getline(token, 100);
	std::string firstPath = token;
	controller.writeToFile(firstPath, controller.getAllToBeRestored());
	cin.getline(token, 100);
	std::string secondPath = token;
	controller.writeToFile(secondPath, controller.getAllToBeDemolished());

}

void UI::run()
{
	char command[256];
	cout << "App started, enter command\n";
	while (true)
	{
		cin.getline(command, 256);
		if (strcmp(command, "add") == 0)
			UIAdd();
		else if (strcmp(command, "show all") == 0)
			UIShowAll();
		else if (strcmp(command, "filter") == 0)
			UIFilter();
		else if (strcmp(command, "write") == 0)
			UIWriteToFile();
		else
			return;
	}
}
