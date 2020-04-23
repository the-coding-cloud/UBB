#include "Tests.h"
#include <assert.h>

void testDomain()
{
	Offer* offer1 = createOffer(1, "Type1", "Destination1", 200);
	assert(offer1->offerID == 1);
	assert(strcmp(offer1->type, "Type1") == 0);
	assert(strcmp(offer1->destination, "Destination1") == 0);
	assert(offer1->price == 200);

	Offer* offer2 = createOffer(1, "Type2", "Destination2", 300);
	assert(equalOffers(offer1, offer2) == 1);

	destroyOffer(offer1);
	destroyOffer(offer2);
}

void testRepo()
{
	OfferRepo* offerRepo = createRepo();
	Offer* offer1 = createOffer(1, "Type1", "Destination1", 200);
	Offer* offer2 = createOffer(1, "Type2", "Destination2", 300);
	Offer* offer3 = createOffer(3, "Type3", "Destination3", 400);

	assert(addOffer(offer1, offerRepo) == 1);
	assert(addOffer(offer2, offerRepo) == 0);
	assert(addOffer(offer3, offerRepo) == 1);

	assert(offerRepo->offerList[0]->offerID == 1);
	assert(strcmp(offerRepo->offerList[0]->type, "Type1") == 0);
	assert(strcmp(offerRepo->offerList[0]->destination, "Destination1") == 0);
	assert(offerRepo->offerList[0]->price == 200);

	offer1->price = 300;
	assert(updateOffer(offer1, offerRepo) == 1);

	Offer* offerToDelete;
	offerToDelete = createOffer(3, "", "", 0);
	assert(deleteOffer(offerToDelete, offerRepo) == 1);
	
	destroyOffer(offerToDelete);
	destroyOffer(offer2);
	destroyOffer(offer3);
	deallocateRepo(offerRepo);

}

void testUndoRedo()
{
	OfferRepo* offerRepo = createRepo();
	Offer* offer1 = createOffer(1, "Type1", "Destination1", 200);

	UndoRedoList* undoRedoList;
	assert(undoRedoList->listLength == 1);
	assert(undoRedoList->operationList[0]->listLength == 1);
	assert(undoRedoList->operationList[0]->offerList[0]->price == 200);
	assert(strcmp(undoRedoList->operationList[0]->offerList[0]->type, "Type1") == 0);
	assert(strcmp(undoRedoList->operationList[0]->offerList[0]->destination, "Destination1") == 0);

	destroyOperationList(undoRedoList);

}

void runTests()
{
	testDomain();
	testRepo();
	testUndoRedo();
}