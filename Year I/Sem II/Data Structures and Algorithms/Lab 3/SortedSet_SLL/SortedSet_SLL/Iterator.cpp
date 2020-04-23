#include "Iterator.h"
#include "SortedSet.h"
#include <exception>
using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet & container) : container(container)
// theta(1)
{
    this->currentNode = container.linkedList.head;
}

void SortedSetIterator::first() 
// theta(1)
{
    this->currentNode = container.linkedList.head;
}

void SortedSetIterator::next()
// theta(1)
{
    if(!this->valid())
        throw std::exception();
    this->currentNode = this->currentNode->next;
}

bool SortedSetIterator::valid() const
// theta(1)
{
    return this->currentNode != nullptr;
}

TElem SortedSetIterator::getCurrent() const
// theta(1)
{
    if(!this->valid())
		throw std::exception();
	
	return this->currentNode->data;
    
}
