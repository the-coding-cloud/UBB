#pragma once
#include "Controller.h"
#include <iostream>
#include <string>

class UI
{
private:
	Controller controller;

public:
	UI();

	void UIAdd();
	void UIShowAll();
	void UIPair();
	void run();
};