#pragma once
#include "SLL.h"
#include "SortedSet.h"

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
    //after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty
	struct Node *head;
	struct Node *currentNode;
    /* representation specific for the iterator*/

public:
	SortedSetIterator(const SortedSet & container);
	SortedSetIterator();
    //sets the iterator to the first element of the container
    void first();

    //moves the iterator to the next element
    //throws exception if the iterator is not valid
    void next();

    //checks if the iterator is valid
    bool valid() const;

	void previous();

    //returns the value of the current element from the iterator
    // throws exception if the iterator is not valid
    TElem getCurrent() const;

};

