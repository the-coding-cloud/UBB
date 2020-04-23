#include "Iterator.h"
#include <exception>
using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet & container)
// theta(1)
{
    this->head = container.linkedList->head;
    this->currentNode = container.linkedList->head;
}

SortedSetIterator::SortedSetIterator()
{
}

void SortedSetIterator::first() 
// theta(1)
{
    this->currentNode = this->head;
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

void SortedSetIterator::previous()
{
	if (this->currentNode == nullptr)
		throw std::exception();

	if (this->currentNode == this->head)
		throw std::exception();
	else
	{
		Node *ourNodeAndSaviour = this->currentNode;
		this->currentNode = this->head;

		while (this->currentNode->next != ourNodeAndSaviour)
			this->currentNode = this->currentNode->next;
	}
}

TElem SortedSetIterator::getCurrent() const
// theta(1)
{
    if(this->valid())
        return this->currentNode->data;
    throw std::exception();
}
