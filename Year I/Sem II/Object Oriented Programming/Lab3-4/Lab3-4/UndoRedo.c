#include "UndoRedo.h"

UndoRedoList * createUndoRedoList()
{
	UndoRedoList* undoRedoList;
	undoRedoList = (UndoRedoList*)malloc(sizeof(UndoRedoList));
	undoRedoList->listLength = 0;
	undoRedoList->listCapacity = 50;
	undoRedoList->operationList = (OfferRepo**)malloc(undoRedoList->listCapacity * sizeof(Offer*));

	return undoRedoList;
}

void addOperation(UndoRedoList * undoRedoList, OfferRepo * offerRepo)
{
	if (undoRedoList->listLength == undoRedoList->listCapacity)
	{
		undoRedoList->listCapacity = offerRepo->listCapacity * 1.5;
		undoRedoList->operationList = (OfferRepo**)realloc(undoRedoList->operationList, undoRedoList->listCapacity * sizeof(OfferRepo*));
		undoRedoList->operationList[undoRedoList->listLength] = copyRepo(offerRepo);
		undoRedoList->listLength += 1;
	}

	else
	{
		undoRedoList->operationList[undoRedoList->listLength] = copyRepo(offerRepo);
		undoRedoList->listLength += 1;
	}
}

void destroyOperationList(UndoRedoList * undoRedoList)
{
	for (int index = 0; index < undoRedoList->listLength; index++)
	{
		deallocateRepo(undoRedoList->operationList[index]);
	}
	free(undoRedoList->operationList);
	free(undoRedoList);
}

UndoRedoList* emptyOperationList(UndoRedoList * operationList)
{
	destroyOperationList(operationList);

	UndoRedoList* emptyList;
	emptyList = createUndoRedoList();

	return emptyList;
}

