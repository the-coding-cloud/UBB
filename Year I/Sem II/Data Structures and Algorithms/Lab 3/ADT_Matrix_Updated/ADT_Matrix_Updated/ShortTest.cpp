#include <assert.h>
#include "Matrix.h"
#include <iostream>

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	m.printMatrix();
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	m.printMatrix();
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	m.printMatrix();
	assert(m.element(1, 2) == 0);
	cout << "Bun\n";
}