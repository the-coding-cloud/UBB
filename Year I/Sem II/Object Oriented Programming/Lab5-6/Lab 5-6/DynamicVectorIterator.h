#pragma once
#include "DynamicVector.h"
#include "Domain.h"

template <typename ElementType>
class DynamicVector;

class DynamicVectorIterator
{
private:
	Movie* elements;
	int current;
	int size;

public:

	DynamicVectorIterator(DynamicVector<Movie> vector);

	DynamicVectorIterator() {}

	void next();

	bool valid();

	Movie getCurrent();
};
