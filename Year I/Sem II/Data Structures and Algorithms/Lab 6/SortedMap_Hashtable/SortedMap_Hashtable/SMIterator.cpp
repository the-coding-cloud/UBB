#include "SMIterator.h"

SMIterator::SMIterator(const SortedMap & sm) : sm(sm)
// O(n^2) - because of the bubble sort, but luckily it is an operation done only once
{
	this->arraySize = sm.size();
	this->elements = new TElem[this->arraySize];
	this->currentElement = 0;

	int index = 0;
	for (int i = 0; i < sm.maxSize; i++)
		if (sm.elements[i] != sm.empty && sm.elements[i] != sm.deleted)
		{
			this->elements[index] = sm.elements[i];
			index++;
		}

	bool unsorted;
	TElem aux;
	do 
	{
		unsorted = false;
		for (int i = 0; i < this->arraySize - 1; i++)
			if (sm.r(this->elements[i].first, this->elements[i+1].first) == false) 
			{
				aux = this->elements[i];
				this->elements[i] = this->elements[i + 1];
				this->elements[i + 1] = aux;
				unsorted = true;
			}

	} while (unsorted);
}

void SMIterator::first()
// theta(1)
{
	this->currentElement = 0;
}

void SMIterator::next()
// theta(1)
{
	if (!this->valid())
		throw std::exception("invalid iterator");

	this->currentElement++;

}

bool SMIterator::valid() const
// theta(1)
{
	return this->currentElement < this->arraySize;
}

TElem SMIterator::getCurrent() const
// theta(1)
{
	if (!this->valid())
		throw std::exception("invalid iterator");

	return this->elements[this->currentElement];
}
