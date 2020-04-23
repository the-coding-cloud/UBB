#include "MapIterator.h"

MapIterator::MapIterator(const Map& c) : c(c) 
// theta(1) 
{
	this->currentElement = c.head;
}

void MapIterator::first()
{
	this->currentElement = c.head;
}

void MapIterator::next()
// theta(1)
{
	if (!this->valid())
	{
		throw std::exception("Invalid iterator");
	}
	this->currentElement = this->c.next[this->currentElement];
}

bool MapIterator::valid() const
// theta(1)
{
	return this->currentElement != -1;
}

TElem MapIterator::getCurrent() const
// theta(1)
{
	if (!this->valid())
	{
		throw std::exception("Invalid iterator");
	}

	return this->c.elements[currentElement];
}

void MapIterator::jumpForward(int k)
// O(n) (where n is actually k, the input)
{
	for (int index = 0; index < k; index++)
		this->next();

	if (!this->valid())
	{
		throw std::exception("Invalid iterator");
	}
}
