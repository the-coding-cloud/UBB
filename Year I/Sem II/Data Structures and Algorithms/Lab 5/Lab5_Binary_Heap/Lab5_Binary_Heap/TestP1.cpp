#include "TestP1.h"
#include "P1.h"
#include <vector>
#include <algorithm>
#include <assert.h>
#include <iostream>

using namespace std;

bool lessThanRelation(TElem e1, TElem e2) {
	return e1 <= e2;
}

bool greaterThanRelation(TElem e1, TElem e2) {
	return e1 >= e2;
}

bool lessThanLastDigit(TElem e1, TElem e2) {
	return e1 % 10 <= e2 % 10;
}

bool lessThanRelationS(TElem e1, TElem e2) {
	return e1 < e2;
}

bool greaterThanRelationS(TElem e1, TElem e2) {
	return e1 > e2;
}

bool lessThanLastDigitS(TElem e1, TElem e2) {
	return e1 % 10 < e2 % 10;
}

void testRelShort(Relation rel, Relation relS) {
	list<list<TElem >> input;
	for (int i = 0; i < 5; i++) {
		list<TElem> l1;
		for (int j = 0; j < 20; j++) {
			l1.push_back(rand() % 100);
		}		
		l1.sort(relS);
		input.push_back(l1);
	}
	list<TElem> empty;
	input.push_back(empty);

	list<TElem> res = mergeLists(input, rel);
	assert(res.size() == 100);
	auto i = res.begin();
	TElem e1 = *(res.begin());
	i++;
	for (; i != res.end(); i++) {
		assert(rel(e1, *i));
		e1 = *i;
	}
}

void testRelLong(Relation rel, Relation relS) {
	list<list<TElem>> input;
	for (int i = 0; i < 50; i++) {
		list<TElem> l1;
		for (int j = 0; j < 2000; j++) {
			l1.push_back(rand() % 10000);
		}
		l1.sort(relS);
		input.push_back(l1);
	}
	list<TElem> empty;
	input.push_back(empty);

	list<TElem> res = mergeLists(input, rel);
	assert(res.size() == 100000);
	auto i = res.begin();
	TElem e1 = *(res.begin());
	i++;
	for (; i != res.end(); i++) {
		assert(rel(e1, *i));
		e1 = *i;
	}
}

void testP1() {

	testRelShort(lessThanRelation, lessThanRelationS);
	cout << "Short test, rel 1" << endl;
	testRelShort(greaterThanRelation, greaterThanRelationS);
	cout << "Short test, rel 2" << endl;
	testRelShort(lessThanLastDigit, lessThanLastDigitS);
	cout << "Short test, rel 3" << endl;
	testRelLong(lessThanRelation, lessThanRelationS);
	cout << "Long test, rel 1" << endl;
	testRelLong(greaterThanRelation, greaterThanRelationS);
	cout << "Long test, rel 2" << endl;
	testRelLong(lessThanLastDigit, lessThanLastDigitS);
	cout << "Long test, rel 3" << endl;

}