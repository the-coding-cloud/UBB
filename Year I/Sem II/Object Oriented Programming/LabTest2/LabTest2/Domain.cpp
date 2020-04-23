#include "Domain.h"
#include <string>

std::string Building::toString()
{
	std::string info;
	info = "";
	info += this->address;
	info += "; ";
	info += std::to_string(this->constructionYear);
	return info;
}

Block::Block(std::string address, int constructionYear, int totalApt, int occupiedApt)
{
	this->address = address;
	this->constructionYear = constructionYear;
	this->totalApt = totalApt;
	this->occupiedApt = occupiedApt;
}

bool Block::toRestore()
{
	if (2019 - this->constructionYear > 40 && occupiedApt / totalApt * 100 > 80)
		return true;
	else
		return false;
}

bool Block::canBeDemolished()
{
	if (occupiedApt / totalApt * 100 < 5)
		return true;
	else
		return false;
}

std::string Block::toString()
{
	std::string info;
	info = "";
	info += this->address;
	info += "; ";
	info += std::to_string(this->constructionYear);
	info += "; ";
	info += std::to_string(this->totalApt);
	info += "; ";
	info += std::to_string(this->occupiedApt);
	return info;
}

House::House(std::string address, int constructionYear, std::string type, bool isHistorical)
{
	this->address = address;
	this->constructionYear = constructionYear;
	this->type = type;
	this->isHistorical = isHistorical;
}

bool House::toRestore()
{
	if (2019 - this->constructionYear > 100)
		return true;
	else
		return false;
}

bool House::canBeDemolished()
{
	return !this->isHistorical;
}

std::string House::toString()
{
	std::string info;
	info = "";
	info += this->address;
	info += "; ";
	info += std::to_string(this->constructionYear);
	info += "; ";
	info += this->type;
	info += "; ";
	if (this->isHistorical)
		info += "is historical";
	else
		info += "not historical";

	return info;
}
