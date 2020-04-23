#pragma once
#include "Iterator.h"

typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);

typedef struct Node
{
    TComp data;
    Node* next;
} Node;

class SLL{

	friend class SortedSetIterator;
	friend class SortedSet;

private:

    Node *head;

public:
    SLL();

    bool search(TElem elem) const;

    void addToBeginning(TComp data);

    void addAfterNode(TComp data, Node* current);

    bool deleteNode(TComp data);

	void empty();

	~SLL();
};
