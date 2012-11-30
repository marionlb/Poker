#include "card.h"

Card::Card()
{
    h = UNKNOWNH;
    c = UNKNOWNC;
}

Card::Card(eC couleur, eH hauteur)
{
    h = hauteur;
    c = couleur;
}

Card::Card(int i)
{
    if (i / 100 >= 4)
        c = SPADES;
    else if (i / 100 >= 3)
        c = HEARTS;
    else if (i / 100 >= 2)
        c = DIAMONDS;
    else
        c = CLUBS;

    if (i % 100 == 1)
        h = ACE;
    if (i % 100 == 2)
        h = TWO;
    if (i % 100 == 3)
        h = THREE;
    if (i % 100 == 4)
        h = FOUR;
    if (i % 100 == 5)
        h = FIVE;
    if (i % 100 == 6)
        h = SIX;
    if (i % 100 == 7)
        h = SEVEN;
    if (i % 100 == 8)
        h = HEIGHT;
    if (i % 100 == 9)
        h = NINE;
    if (i % 100 == 10)
        h = TEN;
    if (i % 100 == 11)
        h = JACK;
    if (i % 100 == 12)
        h = QUEEN;
    if (i % 100 == 13)
        h = KING;

    nb = i;
}

Card::~Card()
{
}
