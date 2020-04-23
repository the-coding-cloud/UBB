#pragma once
#include <iostream>

typedef int TElem;

class DynamicArray
{
public:

	TElem* elements;
	int size;
	int capacity;

	DynamicArray(int capacity = 100);

	DynamicArray(const DynamicArray& array);

	~DynamicArray();

	void addElement(const TElem& e);

	void insertElement(const TElem& e, int index);

	void deleteElement(int index);

	void printArray() const;

	int getSize() const;

private:
	// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
	void resize(double factor = 2);
};

