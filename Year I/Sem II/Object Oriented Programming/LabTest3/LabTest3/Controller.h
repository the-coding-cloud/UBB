#pragma once
#include "WeatherRepo.h"
#include "Weather.h"

class Controller
{
private:
	WeatherRepo weatherRepo;

public:
	std::vector<Weather> getAllWeather();
	std::vector<Weather> getFilteredWeather(int precipitation);
	int getTotalTimeForType(std::string description);
	void loadRepo(std::string filepath);

	Controller();
	~Controller();
};

