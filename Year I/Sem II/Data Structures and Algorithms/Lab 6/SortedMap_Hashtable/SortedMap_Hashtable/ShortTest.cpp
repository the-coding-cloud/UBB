#include <assert.h>
#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMap sm(relatie1);
	assert(sm.size() == 0);
	assert(sm.isEmpty());
    sm.add(1,2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1)!=NULL_TVALUE);
    TValue v =sm.add(1,3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	assert(e.second != NULL_TVALUE);
    	it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());
}

void testNewOp()
{
	SortedMap sm1 = SortedMap(relatie1);
	SortedMap sm2 = SortedMap(relatie1);

	sm1.add(1, 1);
	sm1.add(2, 2);
	sm1.add(3, 3);
	sm2.add(1, 2);
	sm2.add(2, 3);
	sm2.add(3, 4);
	
	assert(sm1.addIfNotPresent(sm2) == 0);
	assert(sm1.size() == 3);

	sm2.add(4, 5);
	sm2.add(5, 6);
	assert(sm1.addIfNotPresent(sm2) == 2);
	assert(sm1.size() == 5);
	int v1 = sm1.search(4);
	int v2 = sm1.search(5);
	assert(v1 == 5);
	assert(v2 == 6);
}

