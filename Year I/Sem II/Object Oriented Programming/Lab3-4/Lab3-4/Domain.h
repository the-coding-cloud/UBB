#pragma once
#include <string.h>
#include <stdlib.h>

typedef struct{
	int offerID;
	char *type;
	char *destination;
	int price;
}Offer;


Offer* createOffer(int offerID, char* type, char* destination, int price);
Offer* copyOffer(Offer* offer);
void destroyOffer(Offer* offer);
int equalOffers(Offer* firstOffer, Offer* secondOffer);
