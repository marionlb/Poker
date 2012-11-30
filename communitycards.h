#ifndef COMMUNITYCARDS_H
#define COMMUNITYCARDS_H

#include "card.h"

class CommunityCards
{
public:
    CommunityCards();
    ~CommunityCards();

    void flop(Card *c1, Card *c2, Card *c3);
    void turn(Card *c4);
    void river(Card *c5);

public:
    Card *firstC;
    Card *secondC;
    Card *thirdC;
    Card *fourthC;
    Card *fifthC;
};

#endif // COMMUNITYCARDS_H
