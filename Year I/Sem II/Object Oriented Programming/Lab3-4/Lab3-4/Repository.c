#include "Repository.h"
#include <stdlib.h>

OfferRepo* createRepo()
{
	OfferRepo* offerRepo = (OfferRepo*)malloc(sizeof(OfferRepo));
	offerRepo->listLength = 0;
	offerRepo->listCapacity = 100;
	offerRepo->offerList = (Offer**)malloc(offerRepo->listCapacity * sizeof(Offer*));

	return offerRepo;
}

OfferRepo* copyRepo(OfferRepo* offerRepo)
{
	OfferRepo* newOfferRepo;
	newOfferRepo = createRepo();

	for (int index = 0; index < offerRepo->listLength; index++)
	{
		Offer* offerToAdd = copyOffer(offerRepo->offerList[index]);
		addOffer(offerToAdd, newOfferRepo);
	}

	return newOfferRepo;
}

int existingOffer(Offer * offer, OfferRepo * offerRepo)
{
	for (int index = 0; index < offerRepo->listLength; index++) 
	{
		if (equalOffers(offer, offerRepo->offerList[index]))
			return index;
	}
	return -1;
}

int existingID(int offerID, OfferRepo * offerRepo)
{
	for (int index = 0; index < offerRepo->listLength; index++)
	{
		if (offerID == offerRepo->offerList[index]->offerID)
			return index;
	}
	return -1;
}

int addOffer(Offer * offer, OfferRepo * offerRepo)
{
	if (existingOffer(offer, offerRepo) != -1)
		return 0;
	else
	{
		if (offerRepo->listLength == offerRepo->listCapacity)
		{
			offerRepo->listCapacity = offerRepo->listCapacity * 1.5;
			offerRepo->offerList = (Offer**)realloc(offerRepo->offerList, offerRepo->listCapacity * sizeof(Offer*));
			offerRepo->offerList[offerRepo->listLength] = offer;
			offerRepo->listLength += 1;
			return 1;
		}
		
		else
		{
			offerRepo->offerList[offerRepo->listLength] = offer;
			offerRepo->listLength += 1;
			return 1;
		}
	}
}

int updateOffer(Offer * offer, OfferRepo * offerRepo)
{
	int offerIndex = existingOffer(offer, offerRepo);
	if (offerIndex == -1)
		return 0;
	else {
		offerRepo->offerList[offerIndex]->offerID = offer->offerID;
		offerRepo->offerList[offerIndex]->type = offer->type;
		offerRepo->offerList[offerIndex]->destination = offer->destination;
		offerRepo->offerList[offerIndex]->price = offer->price;
		return 1;
	}
}

int deleteOffer(int offerID, OfferRepo * offerRepo)
{
	int offerIndex = existingID(offerID, offerRepo);
	if (offerIndex == -1)
		return 0;
	else
	{
		for (int index = offerIndex; index < offerRepo->listLength - 1; index++)
			offerRepo->offerList[index] = offerRepo->offerList[index + 1];
		offerRepo->listLength -= 1;

		return 1;
	}
}

void sortTypeAscending(OfferRepo* offerRepo)
{
	int i, j;
	Offer* auxOffer;
	auxOffer = createOffer(0, "", "", 0);

	for (i = 0; i < offerRepo->listLength - 1; ++i)
		for (j = i + 1; j < offerRepo->listLength; ++j)
			if (strcmp(offerRepo->offerList[i]->type, offerRepo->offerList[j]->type) > 0)
					{
						auxOffer->offerID = offerRepo->offerList[i]->offerID;
						auxOffer->price = offerRepo->offerList[i]->price;
						strcpy(auxOffer->type, offerRepo->offerList[i]->type);
						strcpy(auxOffer->destination, offerRepo->offerList[i]->destination);
						
						offerRepo->offerList[i]->offerID = offerRepo->offerList[j]->offerID;
						offerRepo->offerList[i]->price = offerRepo->offerList[j]->price;
						strcpy(offerRepo->offerList[i]->type, offerRepo->offerList[j]->type);
						strcpy(offerRepo->offerList[i]->destination, offerRepo->offerList[j]->destination);
						
						offerRepo->offerList[j]->offerID = auxOffer->offerID;
						offerRepo->offerList[j]->price = auxOffer->price;
						strcpy(offerRepo->offerList[j]->type, auxOffer->type);
						strcpy(offerRepo->offerList[j]->destination, auxOffer->destination);
					}

}

void sortTypeDescending(OfferRepo * offerRepo)
{
	int i, j;
	Offer* auxOffer;
	auxOffer = createOffer(0, "", "", 0);

	for (i = 0; i < offerRepo->listLength - 1; ++i)
		for (j = i + 1; j < offerRepo->listLength; ++j)
			if (strcmp(offerRepo->offerList[i]->type, offerRepo->offerList[j]->type) < 0)
			{
				auxOffer->offerID = offerRepo->offerList[i]->offerID;
				auxOffer->price = offerRepo->offerList[i]->price;
				strcpy(auxOffer->type, offerRepo->offerList[i]->type);
				strcpy(auxOffer->destination, offerRepo->offerList[i]->destination);

				offerRepo->offerList[i]->offerID = offerRepo->offerList[j]->offerID;
				offerRepo->offerList[i]->price = offerRepo->offerList[j]->price;
				strcpy(offerRepo->offerList[i]->type, offerRepo->offerList[j]->type);
				strcpy(offerRepo->offerList[i]->destination, offerRepo->offerList[j]->destination);

				offerRepo->offerList[j]->offerID = auxOffer->offerID;
				offerRepo->offerList[j]->price = auxOffer->price;
				strcpy(offerRepo->offerList[j]->type, auxOffer->type);
				strcpy(offerRepo->offerList[j]->destination, auxOffer->destination);
			}

}

void deallocateRepo(OfferRepo * offerRepo)
{
	for (int index = 0; index < offerRepo->listLength; index++) 
	{
		destroyOffer(offerRepo->offerList[index]);
	}
	free(offerRepo->offerList);
	free(offerRepo);
}