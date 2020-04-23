#pragma once
#include <list>

using namespace std;

typedef int TElem;
typedef bool(*Relation) (TElem e1, TElem e2);

typedef struct {
	list<TElem>::iterator currentPosition;
	list<TElem>::iterator endOfList;
} myPair;

typedef myPair iteratorPair;

class Heap
{
private:
	Relation relation;
	iteratorPair* elements;
	int totalSize = 0;
	int numberOfLists = 0;
	int capacity = 100;

	void swap(int index1, int index2)
		// theta(1)
	{
		iteratorPair aux = this->elements[index1];
		this->elements[index1] = this->elements[index2];
		this->elements[index2] = aux;
	}

	void bubbleDown(int index)
		// O(log n) - n is the number of lists
	{
		int leftChild = index * 2;
		int rightChild = index * 2 + 1;
		int toChange = index;

		if (leftChild <= this->numberOfLists && this->relation(*(this->elements[leftChild].currentPosition), *(this->elements[toChange].currentPosition)))
			toChange = leftChild;
		
		if (rightChild <= this->numberOfLists && this->relation(*(this->elements[rightChild].currentPosition), *(this->elements[toChange].currentPosition)))
			toChange = rightChild;
		
		if (toChange != index)
		{
			this->swap(index, toChange);
			this->bubbleDown(toChange);
		}
	}

	void bubbleUp(int index)
		// O(log n) - n is the number of lists
	{
		if (index == 1)
			return;

		if (this->relation(*(this->elements[index].currentPosition), *(this->elements[index / 2].currentPosition)))
		{
			this->swap(index, index / 2);
			this->bubbleUp(index / 2);
		}
	}
	void resize()
		// theta(n) - n is the number of lists
	{
		iteratorPair* newElements = new iteratorPair[this->capacity * 2];
		for (int i = 0; i < this->capacity; i++)
			newElements[i] = this->elements[i];

		delete[] this->elements;

		this->elements = newElements;
		this->capacity *= 2;
	}

public:
	Heap()
	{

	}

	int length() 
		// theta(1)
	{
		return this->totalSize;
	}

	void insert(std::list<std::list<TElem>>::iterator element)
		// O(log n) - taking into consideration the bubble up
	{
		iteratorPair newElement;
		newElement.currentPosition = element->begin();
		newElement.endOfList = element->end();

		this->totalSize += element->size();
		this->numberOfLists++;

		if (this->capacity == this->numberOfLists)
			this->resize();

		this->elements[this->numberOfLists] = newElement;

		this->bubbleUp(this->numberOfLists);

	}

	TElem popRoot()
		// O(log n) - taking into consideration the bubble down
	{
		if (this->totalSize > 0)
		{

			iteratorPair aux = this->elements[1];
			this->elements[1].currentPosition++;

			if (this->elements[1].currentPosition == this->elements[1].endOfList)
			{
				this->elements[1] = this->elements[this->numberOfLists];
				this->numberOfLists--;
			}

			this->bubbleDown(1);
			this->totalSize--;

			return *aux.currentPosition;
		}
		return -1;
	}

	Heap(Relation rel)
	{
		this->relation = rel;
		this->elements = new iteratorPair[this->capacity];
	}

	~Heap()
	{
		delete[] this->elements;
	}
};

