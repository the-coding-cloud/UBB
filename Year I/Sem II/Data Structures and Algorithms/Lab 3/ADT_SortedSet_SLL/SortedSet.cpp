#include "SortedSet.h"

SortedSet::SortedSet(Relation r) {
    this->sortRelation = r;
    this->capacity = 3;
    this->length = 0;
    this->linkedList = new SLL[capacity];
}

SortedSet::SortedSet()
{
}

bool SortedSet::add(TComp e) 
// O(n)
{
    if(this->linkedList->search(e) != nullptr)
        return false;

    if(this->length == this->capacity)
        this->resize();

    Node* currentNode = this->linkedList->head;
    Node* previous = nullptr;

    while(currentNode != nullptr && sortRelation(currentNode->data, e))
	{
        previous = currentNode;
        currentNode = currentNode->next;
    }

    if(previous == nullptr && currentNode == this->linkedList->head)
        this->linkedList->addBeginning(e);

    else if(this->length != 0)
        this->linkedList->addAfter(e,previous);

    this->length++;
    return true;
}

void SortedSet::resize(int factor)
// theta(n)
{
    this->capacity *= factor;
    auto *auxArray = new SLL[this->capacity];

    for (int i=0; i<this->length; i++)
	{
        auxArray[i] = this->linkedList[i];
    }

    delete[] this->linkedList;
    this->linkedList = auxArray;
}

bool SortedSet::remove(TComp e) 
// theta(1)
{
    if(this->linkedList->deleteNode(e) != nullptr)
	{
        this->length--;
        return true;
    }
    return false;
}

bool SortedSet::search(TElem elem) const
// theta(1)
{
    return this->linkedList->search(elem) != nullptr;
}

int SortedSet::size() const 
// theta(1)
{
    return this->length;
}

bool SortedSet::isEmpty() const
// theta(1)
{
    return this->length == 0;
}

SortedSetIterator SortedSet::iterator() const 
// theta(1)
{
	SortedSetIterator it(*this);
    return it;
}

SortedSet::~SortedSet() 
// theta(1)
{
    delete[] this->linkedList;
}
