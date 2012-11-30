#include "pocketcards.h"

PocketCards::PocketCards(Card *firstCard, Card *secondCard)
{
    firstC = firstCard;
    secondC = secondCard;
}

PocketCards::~PocketCards()
{
    delete firstC;
    delete secondC;
}


