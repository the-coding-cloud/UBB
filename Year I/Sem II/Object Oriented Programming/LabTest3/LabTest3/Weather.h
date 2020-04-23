#pragma once
#include <iostream>

class Weather
{

private:
	int startHour, endHour;
	int temperature;
	int precipitation;
	std::string description;

public:

	int getTime();
	int getPrecipitation();
	std::string getDescription();
	std::string toString();
	Weather(int startHour, int endHour, int temperature, int precipitation, std::string description);
	Weather();
	~Weather();

	friend std::istream & operator>>(std::ifstream & inputStream, Weather & weather);
};

