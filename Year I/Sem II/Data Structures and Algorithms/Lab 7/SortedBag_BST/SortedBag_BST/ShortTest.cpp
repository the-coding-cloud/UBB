#include "ShortTest.h"
#include "SortedBag.h"
#include "Iterator.h"
#include <assert.h>
#include <iostream>

using namespace std;


bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);
	

	assert(sb.size() == 6);

	assert(sb.nrOccurrences(5) == 2);
	
	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);
	
	SortedBagIterator it = sb.iterator();
	cout << it.getCurrent();
	assert(it.valid() == true);
	it.first();
	it.first();
	while (it.valid()) {
		cout << it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

	sb.addOccurences(5, 7);

	assert(sb.nrOccurrences(7) == 5);


}

