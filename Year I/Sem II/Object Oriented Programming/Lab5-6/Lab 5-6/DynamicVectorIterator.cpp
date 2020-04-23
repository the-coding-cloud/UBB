#include "DynamicVectorIterator.h"


DynamicVectorIterator::DynamicVectorIterator(DynamicVector<Movie> vector)
{
	this->elements = vector.elements;
	this->current = 0;
	this->size = vector.size;
}

void DynamicVectorIterator::next()
{
	this->current++;
	if (this->current >= this->size)
		this->current = 0;
}


 Movie DynamicVectorIterator::getCurrent()
{
	if (this->size > 0)
		return this->elements[this->current];

	else
	{
		Movie element;
		return element;
	}
}

bool DynamicVectorIterator::valid()
{
	return this->current < this->size && this->current >= 0;
}
