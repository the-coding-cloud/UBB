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

    Node* search(TComp elem);

    void addBeginning(TComp data);

    void addAfter(TComp data, Node* current);

    Node* getNode(int position);

    Node* deleteNode(TComp data);

    void operator=(SLL& lst);
};
