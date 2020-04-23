#include "Iterator.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag & c) : sb(c), stack{ std::stack<int>{} }
{
	first();
}

void SortedBagIterator::first()
// theta(n) - where n is the length from the root to the leftmost node (I guess)
{
	this->currentNode = sb.root;

	stack = std::stack<int>{};

	// We go to the leftmost node and push on the stack all the nodes on the way
	while (currentNode != -1)
	{
		stack.push(currentNode);
		currentNode = sb.leftChild[currentNode];
	}

	if (!stack.empty())
	{
		currentNode = stack.top();
	}

	else
		currentNode = -1;
}

void SortedBagIterator::next()
{
	if (!valid())
		throw std::exception("Invalid iterator");

	
	int node = stack.top();
	stack.pop();


	if (sb.rightChild[node] != -1)
	{
		node = sb.rightChild[node];
		while (node != -1) 
		{
			stack.push(node);
			node = sb.leftChild[node];
		}
	}

	if (!stack.empty())
		currentNode = stack.top();

	else
		currentNode = -1;
}

bool SortedBagIterator::valid() const
// theta(1)
{
	return currentNode != -1;
}

TElem SortedBagIterator::getCurrent() const
// theta(1)
{
	if (!valid())
		throw std::exception("Invalid iterator");

	return sb.info[currentNode];
}
