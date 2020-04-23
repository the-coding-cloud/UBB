#include "SortedBag.h"
#include "Iterator.h"

void SortedBag::resize()
// theta(n) - where n is the new capacity
{

	// Basically we copy the old information in the arrays, then initialize the remaining part

	TElem* newInfo = new TComp[this->capacity * 2];
	for (int index = 0; index < this->capacity; index++)
		newInfo[index] = this->info[index];

	int* newLeftChild = new int[this->capacity * 2];
	int* newParents = new int[this->capacity * 2];
	int* newRightChild = new int[this->capacity * 2];
	for (int index = 0; index < this->capacity; index++)

	{
		newLeftChild[index] = this->leftChild[index];
		newRightChild[index] = this->rightChild[index];
		newParents[index] = this->parents[index];
	}

	for (int index = this->capacity; index < this->capacity * 2 - 1; index++)
	{
		newLeftChild[index] = index + 1;
		newRightChild[index] = -1;
	}
	newRightChild[this->capacity*2 - 1] = -1;
	newLeftChild[this->capacity*2 - 1] = -1;
	
	this->firstEmpty = this->capacity;
	this->capacity *= 2;

	delete[] this->info;
	delete[] this->leftChild;
	delete[] this->rightChild;
	delete[] this->parents;

	this->info = newInfo;
	this->leftChild = newLeftChild;
	this->rightChild = newRightChild;
	this->parents = newParents;
}

SortedBag::SortedBag(Relation r)
// theta(n) - where n is the capacity
{
	this->r = r;
	this->capacity = 10;
	this->info = new TComp[capacity];
	this->leftChild = new int[capacity];
	this->rightChild = new int[capacity];
	this->parents = new int[capacity];
	this->numberOfElements = 0;
	this->firstEmpty = 0;
	this->root = -1;

	for (int index = 0; index < this->capacity - 1; index++)
	{
		this->parents[index] = -1; 
		this->rightChild[index] = -1;
		this->leftChild[index] = index + 1;
	}

	this->rightChild[this->capacity - 1] = -1;
	this->leftChild[this->capacity - 1] = -1;
	this->parents[this->capacity - 1] = -1;
}

void SortedBag::add(TComp e)
// O(n) - where n is the height of the tree in our case
{
	// Do resize if necessary
	if (this->firstEmpty==-1)
		resize();

	// We store the new firstEmpty position in this variable
	// Do not forget to update the new value at the end!
	int nextFirstEmpty = this->leftChild[firstEmpty];

	// We initialize the new "node" on the firstEmpty position
	this->info[firstEmpty] = e;
	this->leftChild[firstEmpty] = -1;
	this->rightChild[firstEmpty] = -1;

	// We are now searching for the place where the new node should be inserted 
	int currentPosition = root;
	int parent = -1; 

	// We stop when we reach a leaf; the parent represents the leaf we stop at
	while (currentPosition != -1)
	{
		parent = currentPosition;

		if (r(e, info[currentPosition]))
			currentPosition = leftChild[currentPosition];
		else
			currentPosition = rightChild[currentPosition];
	}


	// We check if the BST is empty - if so, the element to be added becomes the root of our BST
	if (root == -1)
		root = firstEmpty;

	// Here we decide if the new element is a left child or a right child
	else if (r(e, info[parent]))
		leftChild[parent] = firstEmpty;
	else
		rightChild[parent] = firstEmpty;

	this->parents[this->firstEmpty] = parent; // The parent of the root is going to be -1, all good

	// We update the firstEmpty value now
	firstEmpty = nextFirstEmpty;

	// Don't forget to increase the count!
	numberOfElements++;

}

void SortedBag::deleteNode(int currentPosition)
// theta(1)
{
	//	- we change the firstEmpty to the position of the current node
	//	- we change the linked list of empty positions and on the position of this node we add its new next empty which is the current firstEmpty
	//	- we change the child of its parent to -1
	//  - we change the parent of the current node to -1

	this->leftChild[currentPosition] = firstEmpty;
	this->firstEmpty = currentPosition;
	this->parents[currentPosition] = -1;
	this->rightChild[currentPosition] = -1;
}

void SortedBag::removeNoDescendant(int currentPosition)
// theta(1)
{
		if (currentPosition == this->root)
		{
			this->root = -1;
		}

		else
		{
			// We decide whether the node to delete was a left child or right child
			if (r(this->info[currentPosition], this->info[this->parents[currentPosition]]))
				this->leftChild[parents[currentPosition]] = -1;
			else
				this->rightChild[parents[currentPosition]] = -1;

		}
		
		this->deleteNode(currentPosition);

}

void SortedBag::removeLeftDescendant(int currentPosition)
// theta(1)
{

	if (currentPosition==this->root)
	{
		this->root = leftChild[currentPosition];
	}

	else
	{
		parents[leftChild[currentPosition]] = parents[currentPosition];

		if (r(this->info[currentPosition], this->info[parents[currentPosition]]))
			this->leftChild[parents[currentPosition]] = leftChild[currentPosition];
		else
			this->rightChild[parents[currentPosition]] = leftChild[currentPosition];
	}
	this->deleteNode(currentPosition);
}

void SortedBag::removeRight(int currentPosition)
// theta(1)
{

	if (currentPosition == this->root)
	{
		this->root = rightChild[currentPosition];
	}

	else
	{
		parents[rightChild[currentPosition]] = parents[currentPosition];

		if (r(this->info[currentPosition], this->info[parents[currentPosition]]))
			this->leftChild[parents[currentPosition]] = rightChild[currentPosition];
		else
			this->rightChild[parents[currentPosition]] = rightChild[currentPosition];
	}

	this->deleteNode(currentPosition);
}

void SortedBag::removeBothDescendants(int currentPosition)
{
	// Find the maximum of left tree
	int currentMaxNode = this->leftChild[currentPosition];
	int previousMaxNode = currentPosition;

	while (this->rightChild[currentMaxNode] != -1)
	{
		previousMaxNode = currentMaxNode;
		currentMaxNode = this->rightChild[currentMaxNode];
	}

	// Change the info in the node to be deleted
	this->info[currentPosition] = this->info[currentMaxNode];

	// Delete the maximum node
	if (this->leftChild[currentMaxNode] == -1)
	{
		this->removeNoDescendant(currentMaxNode);
	}
	else
	{
		this->removeLeftDescendant(currentMaxNode);
	}

}

void SortedBag::addOccurences(int nr, TComp elem)
// O(n + nr) - n is the height of the tree
{
	if (nr < 0)
		throw std::exception("Invalid number of occurences (cannot be negative)");

	else if (nr >= 1)
	{
		// Do resize if necessary
		if (this->firstEmpty == -1)
			resize();

		// We store the new firstEmpty position in this variable
		// Do not forget to update the new value at the end!
		int nextFirstEmpty = this->leftChild[firstEmpty];

		// We initialize the new "node" on the firstEmpty position
		this->info[firstEmpty] = elem;
		this->leftChild[firstEmpty] = -1;
		this->rightChild[firstEmpty] = -1;

		// We are now searching for the place where the new node should be inserted 
		int currentPosition = root;
		int parent = -1;

		// We stop when we reach a leaf; the parent represents the leaf we stop at
		while (currentPosition != -1)
		{
			parent = currentPosition;

			if (r(elem, info[currentPosition]))
				currentPosition = leftChild[currentPosition];
			else
				currentPosition = rightChild[currentPosition];
		}

		// We check if the BST is empty - if so, the element to be added becomes the root of our BST
		if (root == -1)
			root = firstEmpty;

		// Here we decide if the new element is a left child or a right child
		else if (r(elem, info[parent]))
			leftChild[parent] = firstEmpty;
		else
			rightChild[parent] = firstEmpty;

		this->parents[this->firstEmpty] = parent; // The parent of the root is going to be -1, all good

		parent = firstEmpty;

		// We update the firstEmpty value now
		firstEmpty = nextFirstEmpty;

		// Don't forget to increase the count!
		numberOfElements++;

		nr -= 1;
		while (nr)
		{
			if (this->firstEmpty == -1)
				resize();

			nextFirstEmpty = this->leftChild[firstEmpty];

			this->info[firstEmpty] = elem;
			this->leftChild[firstEmpty] = -1;
			this->rightChild[firstEmpty] = -1;

			if (r(elem, info[parent]))
				leftChild[parent] = firstEmpty;
			else
				rightChild[parent] = firstEmpty;

			this->parents[this->firstEmpty] = parent; 

			parent = firstEmpty;
			firstEmpty = nextFirstEmpty;
			numberOfElements++;

			nr -= 1;
		}

	}

	else return;
}

bool SortedBag::remove(TComp e)
// O(n) - where n is the height
{
	int currentPosition = this->root;
	bool found = false;

	while (currentPosition != -1)
	{
		// The element is found and now we perform additional checks to determine the case we are in
		if (e == info[currentPosition])
		{
			if (leftChild[currentPosition] == -1 && rightChild[currentPosition] == -1)
				this->removeNoDescendant(currentPosition);

			else if (leftChild[currentPosition] == -1)
				// This is the case where our node has a RIGHT descendant
			{
				this->removeRight(currentPosition);
			}

			else if (rightChild[currentPosition] == -1)
				// This is the case where our node has a LEFT descendant
			{
				this->removeLeftDescendant(currentPosition);	
			}

			else
				// This is the case where our node has TWO descendants; good luck
			{
				this->removeBothDescendants(currentPosition);
			}

			this->numberOfElements -= 1;

			return true;
	
		}

		else
		{
			if (r(e, info[currentPosition]))
				currentPosition = leftChild[currentPosition];
			else
				currentPosition = rightChild[currentPosition];
		}
	}

	return false;
}

bool SortedBag::search(TComp e) const
// O(n) - where n is the height
{
	// We start from the root
	// The case where the BST is empty is also covered
	int currentPosition = root;

	// The while loop stops when we reach a leaf or find the element
	while (currentPosition != -1)
	{
		// We return true if we find the element
		if (info[currentPosition] == e)
			return true;

		// Here we determine which child will become the current position
		else if (r(e, info[currentPosition]))
			currentPosition = leftChild[currentPosition];
		else
			currentPosition = rightChild[currentPosition];
	}
	
	// If we reach this line, clearly we didn't find the element
	return false;
}

int SortedBag::nrOccurrences(TComp e) const
// O(n) - where n is the height
{
	// We start from the root
	// The case where the BST is empty is also covered
	int currentPosition = root;
	int count = 0;

	// The while loop stops when we reach a leaf or find the element
	while (currentPosition != -1)
	{
		// We return true if we find the element
		if (info[currentPosition] == e)
		{
			count++;
			if (r(e, info[currentPosition]))
				currentPosition = leftChild[currentPosition];
			else
				currentPosition = rightChild[currentPosition];
		}


		// Here we determine which child will become the current position
		else if (r(e, info[currentPosition]))
			currentPosition = leftChild[currentPosition];
		else
			currentPosition = rightChild[currentPosition];
	}

	return count;
}

int SortedBag::size() const
// theta(1)
{
	return this->numberOfElements;
}

SortedBagIterator SortedBag::iterator() const
// theta(1)
{
	return SortedBagIterator(*this);
}

bool SortedBag::isEmpty() const
// theta(1)
{
	return this->numberOfElements == 0;
}

SortedBag::~SortedBag()
{
	
	delete[] info;
	delete[] leftChild;
	delete[] rightChild;
	delete[] parents;
}
