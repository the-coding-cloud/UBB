#pragma once
#include "Domain.h"
#include "Repo.h"
#include "Controller.h"
#include "Validator.h"

class Tests {
public:
	void testDomain();
	void testRepo();
	void testController();
	void testValidator();
	void testIsolated();
};