#pragma once
#include <list>

using namespace std;

typedef int TElem;
typedef bool(*Relation) (TElem e1, TElem e2);


//merges k sorted lists into one single list.
//the input lists are sorted considering the relation and the results should be sorted in the same way.

list<TElem> mergeLists(list<list<TElem>> inputLists, Relation rel); 
