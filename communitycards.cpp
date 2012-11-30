#include "communitycards.h"

CommunityCards::CommunityCards()
{
    firstC = 0;
    secondC = 0;
    thirdC = 0;
    fourthC = 0;
    fifthC = 0;
}

CommunityCards::~CommunityCards()
{
    delete firstC;
    delete secondC;
    delete thirdC;
    delete fourthC;
    delete fifthC;
}

void CommunityCards::flop(Card *c1, Card *c2, Card *c3)
{
    firstC = c1;
    secondC = c2;
    thirdC = c3;
}

void CommunityCards::turn(Card *c4)
{
    fourthC = c4;
}

void CommunityCards::river(Card *c5)
{
    fifthC = c5;
}
