#pragma once
#include "Map.h"
#include "SLLA.h"
#include <stdexcept>

//unidirectional iterator for a container

class MapIterator {

	friend class Map;

private:

	

	//contains a reference of the container it iterates over

	const Map& c;



	/* representation specific for the iterator*/

	SLLA map;
	int currentElement;

public:

	MapIterator(const Map& c);

	//sets the iterator to the first element of the container

	void first();



	//moves the iterator to the next element

	//throws exception if the iterator is not valid

	void next();



	//checks if the iterator is valid

	bool valid() const;



	//returns the value of the current element from the iterator

	// throws exception if the iterator is not valid

	TElem getCurrent() const;



};
