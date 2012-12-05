#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class Game;

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(Game *g);
    void setWorker(QList<int> deck, int nbCard, QList<int> play, int nbPlayer);

    int result(QList<int> list, QList<int> comp, int res);

    int StraightFlush(QList<int> list, int straightBegin, int colour);
    int Poker();
    int Full();
    int Threeofakind();
    int Twopairs();
    int Pair();

    int PokerKicker(QList<int> list, QList<int> comp, int res);
    int FullKicker(QList<int> comp, int res);
    int ThreeofakindKicker(QList<int> list, QList<int> comp, int res);
    int FlushKicker(QList<int> list, int colour, QList<int> comp, int res);
    int TwopairsKicker(QList<int> list, QList<int> comp, int res);
    int PairsKicker(QList<int> list, QList<int> comp, int res);
    int HighcardKicker(QList<int> list, QList<int> comp);

    int consec();

public slots:
    void work();

public:
    QList<int> deck;
    QList<int> play;
    QList<int> comp;

    int nbPlayer;
    int nComp;
    int nBetter;
    int n;
    int nbCard;
    int cnt;
    Game *g;
    QString name;
    Manager *manager;

    QList<int>      *listing;

    int             nbHearts;
    int             nbSpades;
    int             nbClubs;
    int             nbDiamonds;
    int             colour;
    int             straightBegin;

    bool            m_isInterrupted;
};

#endif // MYTHREAD_H
