#include "Map.h"
#include "MapIterator.h"

Map::Map()
{
}

TValue Map::add(TKey c, TValue v)
{
	TElem element(c, v);
	return this->slla.addElement(element);
}

TValue Map::search(TKey c) const
{
	TValue value = this->slla.searchElement(c);
	return value;
}

TValue Map::remove(TKey c)
{
	return this->slla.deleteElement(c);
}

int Map::size() const
{
	int size = this->slla.getSize();
	return size;
}

bool Map::isEmpty() const
{
	if (this->slla.getSize() == 0)
		return true;
	else
		return false;
}

MapIterator Map::iterator() const
{
	return MapIterator(*this);
}

