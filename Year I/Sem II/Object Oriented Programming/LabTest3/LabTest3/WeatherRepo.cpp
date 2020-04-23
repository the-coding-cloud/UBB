#include "WeatherRepo.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


void WeatherRepo::addWeather(Weather & weather)
{
	this->weatherList.push_back(weather);
}

std::vector<Weather> WeatherRepo::getAllWeather()
{
	return this->weatherList;
}

int WeatherRepo::getTotalHoursForDescription(std::string description)
// Function that computes the total number of hours predicted for a certain kind of weather during the day
// Input: std::string description - represents the type of weather
// Output: int time - integer that represents the number of hours
{
	int time = 0;
	for (auto weather : this->weatherList)
		if (weather.getDescription() == description)
			time += weather.getTime();

	return time;

}

void WeatherRepo::loadFromFile(std::string filepath)
{
	ifstream file(filepath);
	if (!file.is_open()) return;


	Weather weatherForecast = Weather();

	while (file >> weatherForecast)
		addWeather(weatherForecast);

	file.close();

}

std::vector<Weather> WeatherRepo::filterByPrecipitation(int precipitation)
{
	std::vector<Weather> filteredList;

	for (auto weather : this->weatherList)
		if (weather.getPrecipitation() <= precipitation)
			filteredList.push_back(weather);

	return filteredList;
}

WeatherRepo::WeatherRepo()
{
}


WeatherRepo::~WeatherRepo()
{
}

void Tests::testGetTotalHours()
{
	Weather weather1{ 1, 2, 3, 4, "sunny" };
	repo.addWeather(weather1);

	assert(repo.getTotalHoursForDescription("sunny") == 1);

	Weather weather2{ 1, 3, 3, 4, "sunny" };
	repo.addWeather(weather2);

	assert(repo.getTotalHoursForDescription("sunny") == 3);

	Weather weather3{ 1, 3, 3, 4, "meh" };
	repo.addWeather(weather3);

	assert(repo.getTotalHoursForDescription("sunny") == 3);
	
}
