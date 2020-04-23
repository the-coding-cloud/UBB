#pragma once
#include <utility>
#define NULL_TVALUE -1
typedef int TKey;
typedef int TValue;
typedef std::pair <TKey, TValue> TElem;

class SLLA
{
	friend class MapIterator;
	friend class Map;

private:
	TElem* elements;
	int* next;
	int capacity;
	int head;
	int firstEmpty;
	int length;

public:
	SLLA(int capacity = 100);

	TValue addElement(TElem element);

	TValue deleteElement(TKey key);

	TValue searchElement(TKey key) const;

	int getSize() const;

	~SLLA();

private:

	void resize(double factor = 2);

};