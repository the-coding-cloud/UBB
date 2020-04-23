#pragma once
#include "SLL.h"

typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);

//unidirectional iterator for a container
class SortedSet;
class SLL;
class SortedSetIterator {

    friend class SLL;
    friend class SortedSet;

private:

	SortedSetIterator(const SortedSet & container);

    //after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty
	
	const SortedSet& container;

    /* representation specific for the iterator*/

	struct Node* currentNode;

public:
	
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

