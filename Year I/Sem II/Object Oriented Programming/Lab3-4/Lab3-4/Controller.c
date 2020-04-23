#include "Controller.h"

int addNewOffer(Offer * offer, OfferRepo * offerRepo)
{
	return addOffer(offer, offerRepo);
}

int updateExistingOffer(Offer * offer, OfferRepo * offerRepo)
{
	return updateOffer(offer, offerRepo);
}

int deleteExistingOffer(int offerID, OfferRepo * offerRepo)
{
	return deleteOffer(offerID, offerRepo);
}
