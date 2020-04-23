#pragma once
#include "Domain.h"

typedef struct {
	Offer **offerList;
	int listLength;
	int listCapacity;

}OfferRepo;

OfferRepo* createRepo();

OfferRepo* copyRepo();

int existingOffer(Offer* offer, OfferRepo* offerRepo);

int existingID(int offerID, OfferRepo * offerRepo);

int addOffer(Offer* offer, OfferRepo* offerRepo);

int updateOffer(Offer* offer, OfferRepo* offerRepo);

int deleteOffer(int offerID, OfferRepo* offerRepo);

void sortTypeAscending(OfferRepo* offerRepo);

void sortTypeDescending(OfferRepo* offerRepo);

void deallocateRepo(OfferRepo *offerRepo);

