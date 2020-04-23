#pragma once
#include "Domain.h"
#include "Repo.h"
#include "Controller.h"

class Tests {
public:
	void testDomain();
	void testRepo();
	void testController();
	void testValidator();
	void testIsolated();
};