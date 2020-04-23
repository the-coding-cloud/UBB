#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;


int main() {

	// Run the set of tests from ShortTest.cpp
	testAll();
	cout << "All Short Tests Passed.\n";

	// Run the set of tests from ExtendedTest.cpp
	testAllExtended();
	cout << "All Extended Tests Passed.\n";

	system("pause");

	_CrtDumpMemoryLeaks();
	return 0;
}