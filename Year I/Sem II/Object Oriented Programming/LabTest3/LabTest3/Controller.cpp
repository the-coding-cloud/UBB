#include "Controller.h"



Controller::Controller()
{
}

std::vector<Weather> Controller::getAllWeather()
{
	return weatherRepo.getAllWeather();
}

std::vector<Weather> Controller::getFilteredWeather(int precipitation)
{
	return weatherRepo.filterByPrecipitation(precipitation);
}

int Controller::getTotalTimeForType(std::string description)
{
	return weatherRepo.getTotalHoursForDescription(description);
}

void Controller::loadRepo(std::string filepath)
{
	weatherRepo.loadFromFile(filepath);
}

Controller::~Controller()
{
}
