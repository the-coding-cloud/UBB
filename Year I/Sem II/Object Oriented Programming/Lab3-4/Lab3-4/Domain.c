#include "Domain.h"

/*
	Create an offer with the given type, address, surface and price and return it
*/

Offer* createOffer(int offerID, char* type, char* destination, int price) 
{
	Offer* newOffer;

	newOffer = (Offer*)malloc(sizeof(Offer));

	newOffer->offerID = offerID;

	newOffer->type = (char*)malloc(sizeof(char) * (strlen(type) + 1));
	strcpy(newOffer->type, type);

	newOffer->destination = (char*)malloc(sizeof(char) * (strlen(destination) + 1));
	strcpy(newOffer->destination, destination);

	newOffer->price = price;

	return newOffer;
}

Offer* copyOffer(Offer* offer)
{
	Offer* newOffer;

	newOffer = (Offer*)malloc(sizeof(Offer));

	newOffer->offerID = offer->offerID;

	newOffer->type = (char*)malloc(sizeof(char) * (strlen(offer->type) + 1));
	strcpy(newOffer->type, offer->type);

	newOffer->destination = (char*)malloc(sizeof(char) * (strlen(offer->destination) + 1));
	strcpy(newOffer->destination, offer->destination);

	newOffer->price = offer->price;

	return newOffer;
}

void destroyOffer(Offer* offer) 
{
	free(offer->destination);
	free(offer->type);

	free(offer);
}

int equalOffers(Offer* firstOffer, Offer* secondOffer)
{
	return firstOffer->offerID == secondOffer->offerID;
}