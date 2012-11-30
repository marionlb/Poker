#ifndef POCKETCARDS_H
#define POCKETCARDS_H

#include <QList>

#include "card.h"
#include "communitycards.h"

enum eResult
{
    STRAIGHTFLUSH,
    POKER,
    FULL,
    FLUSH,
    STRAIGHT,
    THREEOFAKIND,
    TWOPAIRS,
    PAIR,
    HIGHCARD
};

class PocketCards
{
public:
    PocketCards(Card *firstCard, Card *secondCard);
    ~PocketCards();

public:
    Card *firstC;
    Card *secondC;
};

#endif // POCKETCARDS_H
