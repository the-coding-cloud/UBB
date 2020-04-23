#pragma once
#include <iostream>

class Building
{
protected:
	std::string address;
	int constructionYear;

public:
	virtual bool toRestore() = 0;
	virtual bool canBeDemolished() = 0 ;
	virtual std::string toString();
};

class Block : public Building
{
private:
	int totalApt;
	int occupiedApt;

public:
	Block(std::string address, int constructionYear, int totalApt, int occupiedApt);
	bool toRestore();
	bool canBeDemolished();
	std::string toString() override;
};

class House : public Building
{
private:
	std::string type;
	bool isHistorical;

public:
	House(std::string address, int constructionYear, std::string type, bool isHistorical);
	bool toRestore();
	bool canBeDemolished();
	std::string toString() override;
};