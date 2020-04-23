#include "MapIterator.h"

MapIterator::MapIterator(const Map& c) : c(c) {
	this->map = c.slla;
	this->currentElement = c.slla.head;
}

void MapIterator::first()
{
	this->currentElement = this->map.head;
}

void MapIterator::next()
{
	if (!this->valid()) 
	{
		throw std::exception("Invalid iterator");
	}
	this->currentElement = this->map.next[this->currentElement];
}

bool MapIterator::valid() const
{
	return this->currentElement != -1;
}

TElem MapIterator::getCurrent() const
{
	if (!this->valid())
	{
		throw std::exception("Invalid iterator");
	}
	return this->map.elements[currentElement];
}
