#pragma once
#include "Repository.h"
#include "Domain.h"

typedef struct {
	OfferRepo **operationList;
	int listLength;
	int listCapacity;
}UndoRedoList;

UndoRedoList* createUndoRedoList();

void addOperation(UndoRedoList* undoRedoList, OfferRepo* offerRepo);

void destroyOperationList(UndoRedoList* undoRedoList);

UndoRedoList* emptyOperationList(UndoRedoList* operationList);