#pragma once
#include "Controller.h"
#include "Domain.h"

class UI
{
private:
	Controller controller;

public:
	void UIAdd();
	void UIShowAll();
	void UIFilter();
	void UIWriteToFile();
	void run();
};