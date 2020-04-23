#include "SortedSet.h"
#include "SLL.h"

SortedSet::SortedSet(Relation r) 
{
    this->relation = r;
    this->length = 0;
	this->linkedList = SLL();
}

bool SortedSet::add(TComp e)
// O(n)
{
	if (this->linkedList.search(e))
		return false;

	Node* currentNode = this->linkedList.head;
	Node* previous = nullptr;

	while (currentNode != nullptr && relation(currentNode->data, e))
	{
		previous = currentNode;
		currentNode = currentNode->next;
	}

	if (previous == nullptr && currentNode == this->linkedList.head)
		this->linkedList.addToBeginning(e);

	else if (this->length != 0)
		this->linkedList.addAfterNode(e, previous);

	this->length++;
	return true;
}

bool SortedSet::remove(TComp e) 
// theta(1)
{
    if(this->linkedList.deleteNode(e))
	{
        this->length--;
        return true;
    }
    return false;
}

bool SortedSet::search(TElem elem) const
// theta(1)
{
	return this->linkedList.search(elem);
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
    return SortedSetIterator(*this);
}

void SortedSet::empty()
{
	this->linkedList.empty();
	this->length = 0;
}

