#pragma once
#include "Repository.h"

int addNewOffer(Offer* offer, OfferRepo* offerRepo);
int updateExistingOffer(Offer* offer, OfferRepo* offerRepo);
int deleteExistingOffer(int offerID, OfferRepo* offerRepo);