#pragma once

typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
const int NULL_TCOMP = -99999999;

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;
private:
	/*representation of SortedBag*/
	Relation r;
	TComp* info;
	int* leftChild;
	int* rightChild;
	int* parents;
	int firstEmpty;
	int root;
	int capacity;
	int numberOfElements;

	void resize();

public:

	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	void removeNoDescendant(int currentPosition);

	void removeLeftDescendant(int currentPosition);

	void removeRight(int currentPosition);

	void deleteNode(int currentNode);

	void removeBothDescendants(int currentPosition);

	//adds nr occurences of elem into the Sorted Bag
	// throws an exception if nr is negative
	void addOccurences(int nr, TComp elem);

	//removes one occurrence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();

};