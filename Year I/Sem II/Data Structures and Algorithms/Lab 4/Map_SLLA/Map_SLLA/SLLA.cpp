#include "SLLA.h"
#include <iostream>
using namespace std;

SLLA::SLLA(int capacity)
// constructor
{
	this->elements = new TElem[capacity];
	this->next = new int[capacity];
	this->capacity = capacity;
	this->head = -1;
	this->firstEmpty = 0;
	this->length = 0;

	for (int index = 0; index < this->capacity - 1; index++)
		this->next[index] = index + 1;
	this->next[this->capacity - 1] = -1;
}

TValue SLLA::addElement(TElem element)
// adds to beginning
{
	int index = this->head;
	while (this->elements[index].first != element.first && index != -1)
		index = this->next[index];

	if (index == -1)
	{
		if (this->length == this->capacity)
			resize();

		int nextFirstEmpty = this->next[this->firstEmpty];

		this->elements[this->firstEmpty] = element;
		this->next[this->firstEmpty] = this->head;
		this->head = this->firstEmpty;
		this->firstEmpty = nextFirstEmpty;
		this->length++;

		return NULL_TVALUE;
	}

	else
	{
		TValue oldValue = this->elements[index].second;
		this->elements[index].second = element.second;
		return oldValue;
	}
}

TValue SLLA::deleteElement(TKey key)
{
	int index = this->head;
	int prev = -1;
	while (this->elements[index].first != key && index != -1)
	{
		prev = index;
		index = this->next[index];
	}
	if (index != -1)
	{
		TValue oldValue = this->elements[index].second;
		
		if (prev == -1)
		{
			int oldFirstEmpty = this->firstEmpty;
			this->firstEmpty = this->head;
			this->head = this->next[head];
			next[firstEmpty] = oldFirstEmpty;
		}

		else
		{
			int oldFirstEmpty = this->firstEmpty;
			this->next[prev] = this->next[index];
			this->firstEmpty = index;
			this->next[firstEmpty] = oldFirstEmpty;
		}

		this->length--;
		return oldValue;
	}

	else
	{
		return NULL_TVALUE;
	}
}

TValue SLLA::searchElement(TKey key) const
{
	int index = this->head;

	while (this->elements[index].first != key && index != -1)
		index = this->next[index];

	if (index == -1)
		return NULL_TVALUE;
	else
		return this->elements[index].second;
}

int SLLA::getSize() const
// returns size of SLLA
{
	return this->length;
}

SLLA::~SLLA()
{
	//delete[] this->elements;
	//delete[] this->next;
}

void SLLA::resize(double factor)
{
	this->capacity *= static_cast<int>(factor);

	TElem* newElements = new TElem[this->capacity];
	for (int index = 0; index < this->length; index++)
		newElements[index] = this->elements[index];

	int* newNext= new int[this->capacity];
	for (int index = 0; index < this->length; index++)
		newNext[index] = this->next[index];

	for (int index = this->length; index < this->capacity - 1; index++)
		newNext[index] = index + 1;
	newNext[this->capacity] = -1;

	this->firstEmpty = this->length;

	delete[] this->elements;
	delete[] this->next;

	this->elements = newElements;
	this->next = newNext;
}