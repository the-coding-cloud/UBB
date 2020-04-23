#include "SLL.h"

SLL::SLL()
{
	this->head = nullptr;
}

bool SLL::search(TElem elem) const
// O(n)
{
    Node *currentNode = this->head;
    while(currentNode != nullptr && currentNode->data != elem)
	{
        currentNode = currentNode->next;
    }

    return currentNode!=nullptr;
}

void SLL::addToBeginning(TComp data)
// theta(1)
{
    Node *node = new Node;
    node->data = data;
    node->next = this->head;
    this->head = node;
}

void SLL::addAfterNode(TComp data, Node* current)
// theta(1)
{
    Node* node = new Node;
    node->data = data;
    node->next = current->next;
    current->next = node;
}

bool SLL::deleteNode(TComp data)
// O(n)
{
    Node* currentNode = this->head;
    Node* previousNode = nullptr;

    while(currentNode != nullptr && currentNode->data != data)
	{
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
	
	if (currentNode != nullptr && previousNode == nullptr)
	{
		this->head = this->head->next;
		delete currentNode;
		return true;
	}

	else if (currentNode != nullptr)
	{
		previousNode->next = currentNode->next;
		delete currentNode;
		return true;
	}

	else
		return false;
}

void SLL::empty()
// complexity: theta(n) (where n is the size of the set)
{
	Node* currentNode = this->head;

	while (currentNode != nullptr)
	{
		Node* aux = currentNode->next;
		delete currentNode;
		currentNode = aux;
	}

	this->head = nullptr;
}

SLL::~SLL()
{
	Node* currentNode = this->head;

	while (currentNode != nullptr)
	{
		Node* aux = currentNode->next;
		delete currentNode;
		currentNode = aux;
	}
}


