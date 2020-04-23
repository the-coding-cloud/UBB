#include "Weather.h"
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int Weather::getTime()
{
	return this->endHour - this->startHour;
}

int Weather::getPrecipitation()
{
	return this->precipitation;
}

std::string Weather::getDescription()
{
	return this->description;
}

std::string Weather::toString()
{
	std::string info = "";

	info += std::to_string(this->startHour);
	info += "; ";
	info += std::to_string(this->endHour);
	info += "; ";
	info += std::to_string(this->temperature);
	info += "; ";
	info += std::to_string(this->precipitation);
	info += "; ";
	info += this->description;

	return info;
}

Weather::Weather(int startHour, int endHour, int temperature, int precipitation, std::string description)
{
	this->startHour = startHour;
	this->endHour = endHour;
	this->temperature = temperature;
	this->precipitation = precipitation;
	this->description = description;
}

Weather::Weather()
{
}


Weather::~Weather()
{
}

std::vector<std::string> tokenize(std::string stringToBeRead, char delimiter)
{
	std::vector<std::string> result;
	std::string token;
	std::stringstream ss(stringToBeRead);

	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream & operator>>(std::ifstream & inputStream, Weather & weather)
{
	std::string line;
	getline(inputStream, line);

	std::vector<std::string> tokens = tokenize(line, ';');

	if (tokens.size() != 5)
		return inputStream;

	std::string::size_type sizeType;
	weather.startHour = std::stoi(tokens[0], &sizeType);
	weather.endHour = std::stoi(tokens[1], &sizeType);
	weather.temperature = std::stoi(tokens[2], &sizeType);
	weather.precipitation = std::stoi(tokens[3], &sizeType);
	weather.description = tokens[4];

	return inputStream;
}
