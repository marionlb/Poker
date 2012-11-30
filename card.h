#ifndef CARD_H
#define CARD_H

#include <QObject>

enum eH
{
    ACE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    HEIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    UNKNOWNH = 0
};

enum eC
{
    CLUBS = 1,
    DIAMONDS = 2,
    HEARTS = 3,
    SPADES = 4,
    UNKNOWNC = 0
};

class Card
{

public:
    Card();
    Card(int i);
    Card(eC couleur, eH hauteur);
    ~Card();

public:
    eH h;
    eC c;
    int nb;
};

#endif // CARD_H
