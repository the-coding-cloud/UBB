#include "SLL.h"

SLL::SLL()
{
	this->head = nullptr;
}

Node* SLL::search(TComp elem)
// O(n)
{
    Node *current = this->head;
    while(current != nullptr && current->data != elem)
	{
        current = current->next;
    }
    return current;
}

void SLL::addBeginning(TComp data)
// theta(1)
{
    Node *node = new Node;
    node->data = data;
    node->next = this->head;

    this->head = node;
}

void SLL::addAfter(TComp data, Node *current)
// theta(1)
{
    Node *node = new Node;
    node->data = data;
    node->next = current->next;

    current->next = node;
}

Node* SLL::getNode(int position) 
// theta(n) (or O(n) - not exactly sure how to consider all the stuff)
{
    if(this->head == nullptr || position < 0)
        return nullptr;

    if(position == 0)
        return this->head;

    Node* currentNode = this->head;
    int currentPos = 0;

    while(currentPos < position && currentNode != nullptr)
	{
        currentNode = currentNode->next;
        currentPos++;
    }

    return currentNode;
}

Node* SLL::deleteNode(TComp data)
// O(n)
{
    Node* currentNode = this->head;
    Node* previous = nullptr;
    while(currentNode != nullptr && currentNode->data != data)
	{
        previous = currentNode;
        currentNode = currentNode->next;
    }

    if(currentNode != nullptr && previous == nullptr)
        this->head = this->head->next;

    else if (currentNode != nullptr)
	{
        previous->next = currentNode->next;
        currentNode->next = nullptr;
    }
    return currentNode;
}

void SLL::operator=(SLL &list)
// theta(1)
{
    this->head = list.head;
}



