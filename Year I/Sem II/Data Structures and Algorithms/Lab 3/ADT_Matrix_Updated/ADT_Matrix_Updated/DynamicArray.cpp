#include "DynamicArray.h"
#include <iostream>

using namespace std;

DynamicArray::DynamicArray(int capacity)
// constructor
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new TElem[capacity];
}

DynamicArray::DynamicArray(const DynamicArray& array)
// copy constructor
{
	this->size = array.size;
	this->capacity = array.capacity;
	this->elements = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = array.elements[i];
}

DynamicArray::~DynamicArray()
// destructor
{
	delete[] this->elements;
}

void DynamicArray::addElement(const TElem& e)
// theta(1)
{
	if (this->size == this->capacity)
		this->resize();

	this->elements[this->size] = e;
	this->size++;
}

void DynamicArray::insertElement(const TElem& e, int index)
// O(n)
{
	if (this->size == this->capacity)
		this->resize();

	size++;

	for (int i = size; i > index; i--)
		this->elements[i] = this->elements[i - 1];

	this->elements[index] = e;

}

void DynamicArray::deleteElement(int index)
// O(n)
{
	for (int i = index; i < size - 1; i++)
		this->elements[i] = this->elements[i + 1];

	size--;
}

void DynamicArray::resize(double factor)
// theta(n)
{
	this->capacity *= static_cast<int>(factor);

	TElem* newElements = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++)
		newElements[i] = this->elements[i];

	//delete[] this->elements;
	this->elements = newElements;
}

int DynamicArray::getSize() const
// theta(1)
{
	return this->size;
}

void DynamicArray::printArray() const
// theta(n)
{
	for (int index = 0; index < size; index++)
		cout << this->elements[index] << ' ';
	cout << '\n';
}