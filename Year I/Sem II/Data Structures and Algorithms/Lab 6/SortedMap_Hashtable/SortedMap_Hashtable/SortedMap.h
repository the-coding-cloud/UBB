#pragma once
#include <utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;

#define NULL_TVALUE -1

typedef bool(*Relation)(TKey, TKey);

class SMIterator;

class SortedMap {
	friend class SMIterator;
private:
	TElem* elements;
	Relation r;
	int numberOfElements;
	int maxSize;
	TElem empty;
	TElem deleted;

	void resize();
	int hashCode(TKey key) const;
	int hashFunction(int key, int i) const;
	int primeGreaterThan(int number) const;
	//representation of SortedMap

public:
    // implicit constructor
    SortedMap(Relation r);

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TELEM otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed or null: NULL_TELEM otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//return the iterator for the map
	//the iterator will return the keys following the order given by the relation
    SMIterator iterator() const;

	//adds all pairs from the given SortedMap, whose key is not in the SortedMap already
	//returns the number of added pairs
	int addIfNotPresent(SortedMap& sm);

    // destructor
	~SortedMap();

};

