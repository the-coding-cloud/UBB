#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;


int main() {

	testAll();
	cout << "Inhale exhale\n";

	testAllExtended();

	system("pause");

	return 0;
}