#include "Controller.h"
#include <algorithm>
#include <fstream>

using namespace std;

void Controller::addBuilding(Building * building)
{
	this->buildings.push_back(building);
}

std::vector<Building*> Controller::getAllBuildings()
{
	return this->buildings;
}

std::vector<Building*> Controller::getAllToBeRestored()
{
	std::vector<Building*> toRestore;
	auto it = std::copy_if(this->buildings.begin(), this->buildings.end(), toRestore.begin(), [](Building * building) { return building->toRestore(); });
	toRestore.resize(std::distance(toRestore.begin(), it));

	return toRestore;
}

std::vector<Building*> Controller::getAllToBeDemolished()
{
	std::vector<Building*> toDemolish;
	auto it = std::copy_if(this->buildings.begin(), this->buildings.end(), toDemolish.begin(), [](Building * building) { return building->canBeDemolished(); });
	toDemolish.resize(std::distance(toDemolish.begin(), it));

	return toDemolish;
}

std::vector<Building*> Controller::filterToBeRestored(int year, std::string street)
{
	return std::vector<Building*>();
}

void Controller::writeToFile(std::string path, std::vector<Building*> buildings)
{
	ofstream file(path);
	if (file.is_open())return;

	for (auto building : buildings)
		file << building->toString().c_str() << endl;

	file.close();
}
