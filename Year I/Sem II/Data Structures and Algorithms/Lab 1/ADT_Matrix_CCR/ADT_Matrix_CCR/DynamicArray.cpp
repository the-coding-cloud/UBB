#include "DynamicArray.h"
#include <iostream>

using namespace std;

DynamicArray::DynamicArray(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new TElem[capacity];
}

DynamicArray::DynamicArray(const DynamicArray& array)
{
	this->size = array.size;
	this->capacity = array.capacity;
	this->elements = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = array.elements[i];
}

DynamicArray::~DynamicArray()
{
	delete[] this->elements;
}

void DynamicArray::addElement(const TElem& e)
{
	if (this->size == this->capacity)
		this->resize();

	this->elements[this->size] = e;
	this->size++;
}

void DynamicArray::insertElement(const TElem& e, int index)
{
	if (this->size == this->capacity)
		this->resize();

	size++;

	for (int i = size; i > index; i--)
		this->elements[i] = this->elements[i - 1];

	this->elements[index] = e;

}

void DynamicArray::deleteElement(int index)
{
	for (int i = index; i < size - 1; i++)
		this->elements[i] = this->elements[i + 1];

	size--;
}

void DynamicArray::resize(double factor)
{
	this->capacity *= static_cast<int>(factor);

	TElem* newElements = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++)
		newElements[i] = this->elements[i];

	delete[] this->elements;
	this->elements = newElements;
}

TElem DynamicArray::getElement(int index) const
{
	return this->elements[index];
}

TElem* DynamicArray::getAllElements() const
{
	return this->elements;
}

int DynamicArray::getSize() const
{
	return this->size;
}

void DynamicArray::printArray() const
{
	for (int index = 0; index < size; index++)
		cout << this->elements[index] << ' ';
	cout << '\n';
}