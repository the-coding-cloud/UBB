#include "P1.h"
#include "Heap.h"

list<TElem> mergeLists(list<list<TElem>> inputLists, Relation rel)
	// O(N*log n) - N = number of elements, n = number of lists
{
	Heap heap(rel);
	list<TElem> sortedList;
	for (auto it = inputLists.begin(); it != inputLists.end(); it++)
	{
		if (it->size() > 0)
		{
			heap.insert(it);
		}
	}

	while (heap.length())
	{
		TElem root = heap.popRoot();
		sortedList.push_back(root);
	}

	return sortedList;
}
