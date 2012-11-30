#include "worker.h"
#include "game.h"


Worker::Worker(Game *g)
{
    this->g = g;
    listing = new QList<int> ();
}

void Worker::setWorker(QList<int> deck, int nbCard, QList<int> play)
{
    this->deck = deck;
    this->nbCard = nbCard;
    this->play = play;

    cnt = 0;
    nBetter = 0;
}

void Worker::work()
{
    m_isInterrupted = false;
    qsrand(QDateTime::currentDateTime().toTime_t ());

    while (!m_isInterrupted)
    {
        for (int i = 7 - nbCard; i < 7; ++i)
        {
            play[i] = deck[qrand() % deck.length()];
            deck.removeOne(play[i]);
        }

        nComp = result(play, comp, 0);
        if (nComp % 1000 == 1)
            nComp += 13;
        comp = play;

        play[0] = deck[qrand() % deck.length()];
        deck.removeOne(play[0]);

        play[1] = deck[qrand() % deck.length()];
        deck.removeOne(play[1]);

        if (result(play, comp, nComp) != 0)
            nBetter++;

        deck.append(play[0]);
        deck.append(play[1]);

        for (int i = 7 - nbCard; i < 7; ++i)
        {
            deck.append(play[i]);
        }

        play = comp;

        cnt++;
    }
}

// result renvoie un int significatif de la combinaison de 7 cartes
// par exemple 9001 est une quinte flush à l'as, ou 3003 une double paire au 3.
int Worker::result(QList<int> list, QList<int> comp, int nComp)
{
    nbHearts = 0;
    nbSpades = 0;
    nbClubs = 0;
    nbDiamonds = 0;

    listing->clear();
    for (int i = 0; i < 14; ++i)
        listing->append(0);
    int res;
    for(QList<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if (*it / 100 == 3)
            nbHearts++;
        else if (*it / 100 == 2)
            nbDiamonds++;
        else if (*it / 100 == 1)
            nbClubs++;
        else if (*it / 100 == 4)
            nbSpades++;

        (*listing)[*it % 100] += 1;
    }

    if (nbHearts >= 5)
        colour = 300;
    else if (nbSpades >= 5)
        colour = 400;
    else if (nbDiamonds >= 5)
        colour = 200;
    else if (nbClubs >= 5)
        colour = 100;
    else
        colour = 0;

    straightBegin = consec();

    // Quinte flush
    if (((straightBegin != 0 && colour != 0) && ((res = StraightFlush(list, straightBegin, colour)) != 0)) || (nComp > 9000))
    {
        if (res > nComp || (res % 1000 == 1 && nComp % 1000 != 14))
            return res;
        else
            return 0;
    }
    // Carré
    if ((res = Poker()) > 0 || (nComp > 8000))
    {
        if (res > nComp || (res % 1000 == 1 && nComp % 1000 != 14))
            return res;
        else if (res == nComp || (res % 1000 == 1 && nComp % 1000 == 14))
        {
            // Gestion des kickers
            if (PokerKicker(list, comp, res) == 1)
                return res;
            else
                return 0;
        }
        else
            return 0;
    }
    // Full
    else if ((res = Full()) > 0 || (nComp > 7000))
    {
        if (res > nComp || (res % 1000 == 1 && nComp % 1000 != 14))
            return res;
        else if (res == nComp || (res % 1000 == 1 && nComp % 1000 == 14))
        {
            // Gestion des kickers
            if (FullKicker(comp, res) == 1)
                return res;
            else
                return 0;
        }
        else
            return 0;
    }
    // couleur
    else if (colour != 0 || (nComp > 6000))
    {
        if (list.contains(colour + 1) == true)
            res = 6001;
        else
        {
            for (int i = 2; i <= 13; ++i)
            {
                if (list.contains(colour + i) == true)
                    res = i + 6000;
            }
        }

        if (res > nComp || (res % 1000 == 1 && nComp % 1000 != 14))
            return res;
        else if (res == nComp || (res % 1000 == 1 && nComp % 1000 == 14))
        {
            // Gestion des kickers
            if (FlushKicker(list, colour, comp, res) == 1)
                return res;
            else
                return 0;
        }
        else
            return 0;
    }
    // suite
    else if ((res = straightBegin + 5000) != 5000 || (nComp > 5000))
    {
        if (res > nComp || (res == 5001 && res != nComp - 13))
            return res;
        else
            return 0;
    }
    // brelan
    else if ((res = Threeofakind()) > 0 || (nComp > 4000))
    {
        if (res > nComp|| (res % 1000 == 1 && nComp % 1000 != 14))
            return res;
        else if (res == nComp || (res % 1000 == 1 && nComp % 1000 == 14))
        {
            // Gestion des kickers
            if (ThreeofakindKicker(list, comp, res) == 1)
                return res;
            else
                return 0;
        }
        else
            return 0;
    }
    // double paire
    else if ((res = Twopairs()) > 0 || (nComp > 3000))
    {
        if (res > nComp|| (res % 1000 == 1 && nComp % 1000 != 14))
            return res;
        else if (res == nComp || (res % 1000 == 1 && nComp % 1000 == 14))
        {
            // Gestion des kickers
            if (TwopairsKicker(list, comp, res) == 1)
                return res;
            else
                return 0;
        }
        else
            return 0;
    }
    // paire
    else if ((res = Pair()) > 0 || (nComp > 2000))
    {
        if (res > nComp|| (res % 1000 == 1 && nComp % 1000 != 14))
            return res;
        else if (res == nComp || (res % 1000 == 1 && nComp % 1000 == 14))
        {
            // Gestion des kickers
            if (PairsKicker(list, comp, res) == 1)
                return res;
            else
                return 0;
        }
        else
            return 0;
    }
    // carte haute
    else
    {
        if (listing->value(1) > 0)
            res = 1001;
        else
        {
            for (int i = 13; (listing->value(i) == 0); --i)
                res = 1000 + i;
        }

        if (res > nComp || (res % 1000 == 1 && nComp % 1000 != 14))
            return res;
        else if (res == nComp || (res % 1000 == 1 && nComp % 1000 == 14))
        {
            // Gestion des kickers
            if (HighcardKicker(list, comp) == 1)
                return res;
            else
                return 0;
        }
        else
            return 0;
    }
}

// Teste la quinte flush
int Worker::StraightFlush(QList<int> list, int straightBegin, int colour)
{
    if (straightBegin == 1)
        straightBegin = 14;

    int res = colour + straightBegin;

    if (list.contains(res - 2) && list.contains(res - 3) && list.contains(res - 4))
    {
        if (list.contains(res - 1) && (list.contains(res) || (list.contains(res - 13) && straightBegin == 14)))
            if (straightBegin == 14)
                return 9001;
            else
                return straightBegin + 9000;

        if (straightBegin > 5 && list.contains(res - 1) && list.contains(res - 5))
            return (straightBegin - 1) + 9000;

        if (straightBegin > 6 && list.contains(res - 5) && list.contains(res - 6))
            return (straightBegin - 2) + 9000;
    }

    return 0;
}

// Cherche la présence d'une suite et renvoie sa hauteur le cas échéant
int Worker::consec()
{
    int tmpMax = 0;
    int max = 0;
    int tmpH = 1;
    int maxH = 1;

    for (int i = 1; i <= 14; ++i)
    {
        if (listing->value(i) >= 1)
        {
            tmpMax += 1;
            tmpH = i;
        }
        else
        {
            if (tmpMax >= max)
            {
                max = tmpMax;
                maxH = tmpH;
            }

            tmpMax = 0;
            tmpH = 1;
        }
    }

    if (max >= 4 && maxH == 13 && listing->value(1) != 0)
    {
        max += 1;
        maxH = 1;
    }

    if (max >= 5)
        return maxH;
    else
        return 0;
}

// Teste le carré
int Worker::Poker()
{
    for(int i = 1; i <= 13; ++i)
    {
        if (listing->value(i) == 4)
            return i + 8000;
    }

    return 0;
}

int Worker::PokerKicker(QList<int> list, QList<int> comp, int res)
{
    int hC1 = 0;
    int hC2 = 0;

    for (int i = 0; i < 7; ++i)
    {
        int h1 = list[i] % 100;
        int h2 = comp[i] % 100;

        if (h1 != res % 1000 && (h1 > hC1 || h1 == 1))
        {
            if (h1 == 1)
                hC1 = 14;
            else
                hC1 = h1;
        }
        if (h2 != res % 1000 && (h2 > hC2 || h2 == 1))
        {
            if (h2 == 1)
                hC2 = 14;
            else
                hC2 = h2;
        }
    }

    if (hC1 > hC2)
        return 1;
    else
        return 0;
}

// Teste le full
int Worker::Full()
{
    for(int i = 13; i >= 1; --i)
    {
        if (listing->value(i) == 3)
        {
            for(int j = 1; j <= 13; ++j)
            {
                if (j != i && listing->value(j) >= 2)
                {
                    if (j == 1 && listing->value(j) == 3)
                        return 7001;
                    else
                        return i + 7000;
                }
            }
        }
    }

    return 0;
}

int Worker::FullKicker(QList<int> comp, int res)
{
    if (res % 1000 != 1)
    {
        int nb = 0;
        for (int j = 0; j < 7; ++j)
        {
            if (comp[j] % 100 == 1)
                nb++;
        }
        if (nb >= 2)
            return 0;
        if (listing->value(1) >= 2)
        {
            return 1;
        }
    }

    for (int i = 13; i >= 2; --i)
    {
        if (res % 1000 != i)
        {
            int nb = 0;
            for (int j = 0; j < 7; ++j)
            {
                if (comp[j] % 100 == i)
                    nb++;
            }
            if (nb >= 2)
                return 0;
            if (listing->value(i) >= 2)
            {
                return 1;
            }
        }

    }
}

// Teste la Flush
int Worker::FlushKicker(QList<int> list, int colour, QList<int> comp, int res)
{
    int hC1 = 0;
    int hC2 = 0;
    int n = 0;
    for (int j = 0; j < 7; ++j)
    {
        int h1 = list[j] % 100;
        int h2 = comp[j] % 100;

        if (h1 % 100 == 1 && h1 / 100 == colour)
            hC1 = 1;
        if (h2 % 100 == 1 && h2 / 100 == colour)
            hC2 = 1;
    }

    if (hC1 > hC2)
        return 1;
    if (hC2 > hC1)
        return 0;
    if (hC1 == 1)
        n++;

    hC1 = 0;
    hC2 = 0;

    for (int i = 13; i >= 2 || n == 5; --i)
    {
        for (int j = 0; j < 7; ++j)
        {
            int h1 = list[j] % 100;
            int h2 = comp[j] % 100;

            if (h1 % 100 == 1 && h1 / 100 == colour)
                hC1 = 1;
            if (h2 % 100 == i && h2 / 100 == colour)
                hC2 = 1;
        }

        if (hC1 > hC2)
            return 1;
        if (hC2 > hC1)
            return 0;
        if (hC1 == 1)
            n++;

        hC1 = 0;
        hC2 = 0;
    }

    return 0;
}

// Teste le brelan
int Worker::Threeofakind()
{
    for(int i = 1; i <= 13; ++i)
    {
        if (listing->value(i) == 3)
            return i + 4000;
    }

    return 0;
}

int Worker::ThreeofakindKicker(QList<int> list, QList<int> comp, int res)
{
    int hC1 = 0;
    int hC2 = 0;
    int n = 3;

    if (1 != res % 1000)
    {
        for (int j = 0; j < 7; ++j)
        {
            int h1 = list[j] % 100;
            int h2 = comp[j] % 100;

            if (h1 % 100 == 1)
                hC1 = 1;
            if (h2 % 100 == 1)
                hC2 = 1;
        }

        if (hC1 > hC2)
            return 1;
        if (hC2 > hC1)
            return 0;
        if (hC1 == 1)
            n++;

        hC1 = 0;
        hC2 = 0;
    }

    for (int i = 13; i >= 2 || n == 5; --i)
    {
        if (i != res % 1000)
        {
            for (int j = 0; j < 7; ++j)
            {
                int h1 = list[j] % 100;
                int h2 = comp[j] % 100;

                if (h1 % 100 == i)
                    hC1 = 1;
                if (h2 % 100 == i)
                    hC2 = 1;
            }

            if (hC1 > hC2)
                return 1;
            if (hC2 > hC1)
                return 0;
            if (hC1 == 1)
                n++;

            hC1 = 0;
            hC2 = 0;
        }
    }

    return 0;
}

// Teste la double paire
int Worker::Twopairs()
{
    for(int i = 13; i >= 1; --i)
    {
        if (listing->value(i) == 2)
        {
            for(int j = 1; j <= 13; ++j)
            {
                if (j != i && listing->value(j) == 2)
                {
                    if (j == 1)
                        return j + 3000;
                    else
                        return i + 3000;
                }
            }
        }
    }

    return 0;
}

int Worker::TwopairsKicker(QList<int> list, QList<int> comp, int res)
{
    for (int i = 13; i >= 1; --i)
    {
        if (res % 1000 != i)
        {
            int nb = 0;
            for (int j = 0; j < 7; ++j)
            {
                if (comp[j] % 100 == i)
                    nb++;
            }

            if (nb == 2 && listing->value(i) == 2)
            {
                int hC1 = 0;
                int hC2 = 0;

                for (int k = 0; k < 7; ++k)
                {
                    int h1 = list[k] % 100;
                    int h2 = comp[k] % 100;

                    if (h1 != i && h1 != res % 1000 && (h1 > hC1 || h1 == 1))
                    {
                        if (h1 == 1)
                            hC1 = 14;
                        else
                            hC1 = h1;
                    }
                    if (h2 != i && h2 != res % 1000 && (h2 > hC2 || h2 == 1))
                    {
                        if (h2 == 1)
                            hC2 = 14;
                        else
                            hC2 = h2;
                    }
                }

                if (hC1 > hC2)
                    return 1;
                else
                    return 0;
            }
            else if (nb == 2)
                return 0;

            if (listing->value(i) >= 2)
            {
                return 1;
            }
        }
    }
}

// Teste la paire
int Worker::Pair()
{
    for(int i = 13; i >= 1; --i)
    {
        if (listing->value(i) == 2)
        {
            return i + 2000;
        }
    }

    return 0;
}

int Worker::PairsKicker(QList<int> list, QList<int> comp, int res)
{
    int hC1 = 0;
    int hC2 = 0;
    int n = 2;

    if (1 != res % 1000)
    {
        for (int j = 0; j < 7; ++j)
        {
            int h1 = list[j] % 100;
            int h2 = comp[j] % 100;

            if (h1 == 1)
                hC1 = 1;
            if (h2 == 1)
                hC2 = 1;
        }

        if (hC1 > hC2)
            return 1;
        if (hC2 > hC1)
            return 0;
        if (hC1 == 1)
            n++;

        hC1 = 0;
        hC2 = 0;
    }

    for (int i = 13; i >= 2 || n == 5; --i)
    {
        if (i != res % 1000)
        {
            for (int j = 0; j < 7; ++j)
            {
                int h1 = list[j] % 100;
                int h2 = comp[j] % 100;

                if (h1 == i)
                    hC1 = 1;
                if (h2 == i)
                    hC2 = 1;
            }

            if (hC1 > hC2)
                return 1;
            if (hC2 > hC1)
                return 0;
            if (hC1 == 1)
                n++;

            hC1 = 0;
            hC2 = 0;
        }
    }

    return 0;
}

// HighCard
int Worker::HighcardKicker(QList<int> list, QList<int> comp)
{
    int hC1 = 0;
    int hC2 = 0;
    int n = 0;

    for (int j = 0; j < 7; ++j)
    {
        int h1 = list[j] % 100;
        int h2 = comp[j] % 100;

        if (h1 % 100 == 1)
            hC1 = 1;
        if (h2 % 100 == 1)
            hC2 = 1;
    }

    if (hC1 > hC2)
        return 1;
    if (hC2 > hC1)
        return 0;
    if (hC1 == 1)
        n++;

    hC1 = 0;
    hC2 = 0;

    for (int i = 13; i >= 2 || n == 5; --i)
    {
        for (int j = 0; j < 7; ++j)
        {
            int h1 = list[j] % 100;
            int h2 = comp[j] % 100;

            if (h1 % 100 == i)
            {
                hC1 = 1;
            }
            if (h2 % 100 == i)
                hC2 = 1;
        }

        if (hC1 > hC2)
            return 1;
        if (hC2 > hC1)
            return 0;
        if (hC1 == 1)
            n++;

        hC1 = 0;
        hC2 = 0;
    }

    return 0;
}
