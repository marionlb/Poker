#ifndef GAME_H
#define GAME_H

#include <QPushButton>
#include <QObject>
#include <QMap>
#include <QDebug>
#include <QTime>

#include "card.h"
#include "pocketcards.h"
#include "communitycards.h"
#include "mainwindow.h"
#include "worker.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    Game();
    Game(MainWindow *mmWindow);
    Game(QPushButton *button);
    ~Game();

    float recursAll(QList<int> deck, int nbCard, QList<int> play);
    QList< QList<int> > add(QList< QList<int> > l1, QList< QList<int> > l2);

public slots:
    void refresh();
    void upProgress();

public:
    QPushButton*    mButton;
    MainWindow*     mWindow;
    int             nbBetter;
    int             cnt;
    Worker**         workers;
    QThread**        threads;
    // Worker*         worker1;
    // Worker*         worker2;
    Manager*        manager;
    QDateTime       debDate;
    //QThread*        th1;
    //QThread*        th2;
    //QThread*        thManager;
    //int             n;
    int             nbThreads;

signals:
    void doWork();
    void stopWork();
};

#endif // GAME_H
