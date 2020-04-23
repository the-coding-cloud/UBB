#include "Map.h"
#include "MapIterator.h"

Map::Map(int capacity)
// theta(n) (where n is the capacity)
{
	this->elements = new TElem[capacity];
	this->next = new int[capacity];
	this->capacity = capacity;
	this->head = -1;
	this->firstEmpty = 0;
	this->length = 0;

	for (int index = 0; index < this->capacity - 1; index++)
		this->next[index] = index + 1;
	this->next[this->capacity - 1] = -1;
}

TValue Map::add(TKey c, TValue v)
// O(n) (where n is the size of the map)
{

	int index = this->head;
	while (this->elements[index].first != c && index != -1)
		index = this->next[index];

	if (index == -1)
	{
		if (this->firstEmpty == -1)
			resize();

		int nextFirstEmpty = this->next[this->firstEmpty];

		TElem element(c, v);

		this->elements[this->firstEmpty] = element;
		this->next[this->firstEmpty] = this->head;
		this->head = this->firstEmpty;
		this->firstEmpty = nextFirstEmpty;
		this->length++;

		return NULL_TVALUE;
	}

	else
	{
		TValue oldValue = this->elements[index].second;
		this->elements[index].second = v;
		return oldValue;
	}
}

TValue Map::search(TKey c) const
// O(n) (where n is the size of the map)
{
	int index = this->head;

	while (this->elements[index].first != c && index != -1)
		index = this->next[index];

	if (index == -1)
		return NULL_TVALUE;
	else
		return this->elements[index].second;
}

TValue Map::remove(TKey c)
// O(n) (where n is the size of the map)
{
	int index = this->head;
	int prev = -1;
	while (this->elements[index].first != c && index != -1)
	{
		prev = index;
		index = this->next[index];
	}
	if (index != -1)
	{
		TValue oldValue = this->elements[index].second;

		if (prev == -1)
		{
			int oldFirstEmpty = this->firstEmpty;
			this->firstEmpty = this->head;
			this->head = this->next[head];
			next[firstEmpty] = oldFirstEmpty;
		}

		else
		{
			int oldFirstEmpty = this->firstEmpty;
			this->next[prev] = this->next[index];
			this->firstEmpty = index;
			this->next[firstEmpty] = oldFirstEmpty;
		}

		this->length--;
		return oldValue;
	}

	else
	{
		return NULL_TVALUE;
	}
}

int Map::size() const
// theta(1)
{
	return this->length;
}

bool Map::isEmpty() const
// theta(1)
{
	return this->length == 0;
}

MapIterator Map::iterator() const
// theta(1)
{
	return MapIterator(*this);
}

Map::~Map()
// theta(1)
{
	delete[] this->elements;
	delete[] this->next;
}

void Map::resize()
// theta(n) (where n is the capacity of the map)
{
	TElem* newElements = new TElem[this->capacity*2];
	for (int index = 0; index < this->capacity; index++)
		newElements[index] = this->elements[index];

	int* newNext = new int[this->capacity*2];
	for (int index = 0; index < this->capacity; index++)
		newNext[index] = this->next[index];

	for (int index = this->capacity; index < this->capacity*2 - 1; index++)
		newNext[index] = index + 1;
	newNext[this->capacity*2 - 1] = -1;
	
	
	this->firstEmpty = this->capacity;
	this->capacity *= 2;

	delete[] this->elements;
	delete[] this->next;

	this->elements = newElements;
	this->next = newNext;
}
