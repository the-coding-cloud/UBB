#include "SortedMap.h"
#include "SMIterator.h"

void SortedMap::resize()
// theta(n) - n is the new capacity - we have to pass through the whole new array once in order to initialize it
{
	int newMaxSize = this->primeGreaterThan(this->maxSize * 2);
	int oldMaxSize = this->maxSize;
	TElem* newElements = new TElem[newMaxSize];

	this->maxSize = newMaxSize;

	for (int i = 0; i < newMaxSize; i++)
		newElements[i] = this->empty;

	for (int index = 0; index < oldMaxSize; index++)
	{
		TElem e = this->elements[index];
		for (int i = 0; i < newMaxSize; i++)
			if (newElements[hashFunction(hashCode(e.first), i)] == this->empty)
			{
				newElements[hashFunction(hashCode(e.first), i)] = e;
				break;
			}
	}

	delete [] this->elements;

	this->elements = newElements;
}

int SortedMap::hashCode(TKey key) const
// theta(1)
{
	if (key < 0)
		return -key;
	else
		return key;
}

int SortedMap::hashFunction(int key, int i) const
// theta(1)
{
	return (key % maxSize + i * (1 + key % (maxSize - 1))) % maxSize;
}

int SortedMap::primeGreaterThan(int number) const
// O(sqrt(2 * m) * m) - m is the old capacity
// The for loop goes up until 2*m because Bertrand's postulate states that if n > 1 is an integer,
// then there always exists at least one prime number p with n < p < 2n (Thank you Wikipedia)
{
	bool isPrime;

	for (int i = number + 1; i < 2 * number; i++)
	{
		isPrime = true;
		for (int div = 2; div * div <= i; div++)
			if (i % div == 0)
			{
				isPrime = false;
				break;
			}
		
		if (isPrime == true)
			return i;
	}
}

SortedMap::SortedMap(Relation r)
// theta(m)
{
	this->maxSize = 3;
	this->elements = new TElem[this->maxSize];
	this->r = r;
	this->numberOfElements = 0;
	this->empty = std::make_pair(-99999, -99999);
	this->deleted = std::make_pair(-99998, -99998);

	for (int i = 0; i < this->maxSize; i++)
		this->elements[i] = this->empty;
}

TValue SortedMap::add(TKey c, TValue v)
// BC=AC=theta(1), WC=theta(m) => overall - O(m)
{
	if (numberOfElements == maxSize)
		this->resize();

	for (int i = 0; i < maxSize; i++)
		if (this->elements[hashFunction(hashCode(c), i)] != this->empty && this->elements[hashFunction(hashCode(c), i)] != this->deleted)
		{
			if (this->elements[hashFunction(hashCode(c), i)].first == c)
			{
				TValue oldValue = this->elements[hashFunction(hashCode(c), i)].second;
				this->elements[hashFunction(hashCode(c), i)].second = v;

				return oldValue;
			}
		}
		else
		{
			this->elements[hashFunction(hashCode(c), i)].first = c;
			this->elements[hashFunction(hashCode(c), i)].second = v;
			this->numberOfElements++;
			return NULL_TVALUE;
		}
}

TValue SortedMap::search(TKey c) const
// BC=AC=theta(1), WC=theta(m) => overall - O(m)
{
	for (int i = 0; i < maxSize; i++)
		if (this->elements[hashFunction(hashCode(c), i)] != this->empty)
		{
			if (this->elements[hashFunction(hashCode(c), i)].first == c)
			{
				return this->elements[hashFunction(hashCode(c), i)].second;
			}
		}
		else
		{
			return NULL_TVALUE;
		}

	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey c)
// BC=AC=theta(1), WC=theta(m) => overall - O(m)
{
	for (int i = 0; i < maxSize; i++)
		if (this->elements[hashFunction(hashCode(c), i)] != this->empty)
		{
			if (this->elements[hashFunction(hashCode(c), i)].first == c)
			{
				TValue oldValue = this->elements[hashFunction(hashCode(c), i)].second;
				this->elements[hashFunction(hashCode(c), i)] = this->deleted;
				this->numberOfElements--;
				return oldValue;
			}
		}
		else
		{
			return NULL_TVALUE;
		}

	return NULL_TVALUE;
}

int SortedMap::size() const
// theta(1)
{
	return numberOfElements;
}

bool SortedMap::isEmpty() const
// theta(1)
{
	return numberOfElements == 0;
}

SMIterator SortedMap::iterator() const
// theta(1)
{
	return SMIterator(*this);
}



int SortedMap::addIfNotPresent(SortedMap & sm)
{
	/*
	SMIterator SMit = sm.iterator();
	int addedPairs = 0;

	while (SMit.valid())
	{
		TElem e = SMit.getCurrent();
		if (this->search(e.first) == NULL_TVALUE)
		{
			this->add(e.first, e.second);
			addedPairs++;
		}
		SMit.next();
	}
	*/

	// O(m1*m2) - where m1 is the capacity of the SortedMap and m2 is the capacity of the given SortedMap,
	// also taking into consideration the complexities of search and add

	// Otherwise it would be theta(m), where m is the size of the given SortedMap

	int addedPairs = 0;
	for (int i = 0; i < sm.maxSize; i++)
	{
		if (sm.elements[i] != this->empty && sm.elements[i] != this->deleted)
		{
			if (this->search(sm.elements[i].first) == NULL_TVALUE)
				// new search function that returns empty pos
			{
				this->add(sm.elements[i].first, sm.elements[i].second);
				addedPairs++;
			}
		}
	}

	return addedPairs;
}

SortedMap::~SortedMap()
// theta(1)
{
	delete [] this->elements;
}
