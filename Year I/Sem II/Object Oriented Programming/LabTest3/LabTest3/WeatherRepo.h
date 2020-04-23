#pragma once
#include <Weather.h>
#include <vector>
#include <assert.h>

class WeatherRepo
{
private:
	std::vector<Weather> weatherList;

public:

	void addWeather(Weather & weather);
	std::vector<Weather> getAllWeather();
	int getTotalHoursForDescription(std::string description);
	void loadFromFile(std::string filepath);
	std::vector<Weather> filterByPrecipitation(int precipitation);

	WeatherRepo();
	~WeatherRepo();
};

class Tests
{
private:
	WeatherRepo repo;

public:
	void testGetTotalHours();
};