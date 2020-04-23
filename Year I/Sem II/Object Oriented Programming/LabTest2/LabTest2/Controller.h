#pragma once
#include "Domain.h"
#include <iostream>
#include <vector>

class Controller
{
private:
	std::vector<Building*> buildings;
public:
	void addBuilding(Building * building);
	std::vector<Building*> getAllBuildings();
	std::vector<Building*> getAllToBeRestored();
	std::vector<Building*> getAllToBeDemolished();
	std::vector<Building*> filterToBeRestored(int year, std::string street);
	void writeToFile(std::string path, std::vector<Building*> buildings);
};	