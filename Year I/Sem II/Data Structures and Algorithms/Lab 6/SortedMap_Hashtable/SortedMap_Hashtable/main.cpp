#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;


int main() {

	testAll();
	cout << "Short tests passed\n";

	testAllExtended();
	cout << "Extended tests passed\n";

	testNewOp();
	cout << "*aplauze*\n";
	//system("pause");

	return 0;
}