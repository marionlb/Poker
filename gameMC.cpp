#include "game.h"
#include "worker.h"

// Constructeur par défaut
Game::Game()
{
}

// Constructeur via une interface
Game::Game(MainWindow *mmWindow)
{
    mWindow = mmWindow;


    nbThreads = QThread::idealThreadCount();

    workers = new Worker*[nbThreads];
    threads = new QThread*[nbThreads];
    for(int k=0; k<nbThreads; k++) {
        workers[k]=new Worker(this);
        threads[k]=new QThread();
        workers[k]->moveToThread(threads[k]);
        connect(this, SIGNAL(doWork()), workers[k], SLOT(work()));
    }


    /*
    worker1 = new Worker(this);
    worker2 = new Worker(this);

    th1 = new QThread();
    th2 = new QThread();

    worker1->moveToThread(th1);
    worker2->moveToThread(th2);

    connect(this, SIGNAL(doWork()), worker1, SLOT(work()));
    connect(this, SIGNAL(doWork()), worker2, SLOT(work()));
    */

    connect(mWindow, SIGNAL(Refresh()), this, SLOT(refresh()));
}

// Destructeur
Game::~Game()
{
}

// Renvoie true si la carte c appartient à la liste de cartes list
static bool cont(QList<Card> *list, Card c)
{
    for (int i = 0; i < list->size(); ++i)
    {
        if (list->value(i).nb == c.nb || (c.nb % 10 == 14 && c.nb - list->value(i).nb == 13))
            return true;
    }

    return false;
}

// Teste un jeu donné via l'interface
void Game::refresh()
{
    QList<int> deck;
    deck.clear();
    for (int i = 1; i < 5; ++i)
        for (int j = 1; j < 14; ++j)
            deck.append(i * 100 + j);

    QList<int> play;
    play.clear();

    play.append(mWindow->mh1);
    play.append(mWindow->mh2);
    play.append(mWindow->mflop1);
    play.append(mWindow->mflop2);
    play.append(mWindow->mflop3);
    play.append(mWindow->mturn);
    play.append(mWindow->mriver);

    int unknown = 0;
    for (int i = 0; i < 7; ++i)
    {
        if (play[i] == 0)
        {
            unknown++;
        }
    }

    foreach(int i, play)
    {
        deck.removeOne(i);
    }

    recursAll(deck, unknown, play);
}

float Game::recursAll(QList<int> deck, int nbCard, QList<int> play)
{
    debDate = QDateTime::currentDateTime();

    for(int k=0; k<nbThreads; k++) {
        threads[k]->start();
        workers[k]->setWorker(deck, nbCard, play);
    }
    //th1->start();
    //th2->start();

    //worker1->setWorker(deck, nbCard, play);
    //worker2->setWorker(deck, nbCard, play);

    emit doWork();

    int count = 0;
    float tmpRes = 0;
    float oldRes = 0;
    while(count < 50)
    {

        //th1->wait(100);
        threads[0]->wait(100);
        count++;
        cnt=0;
        nbBetter=0;
        for(int k=0; k<nbThreads; k++) {
            cnt+=workers[k]->cnt;
            nbBetter+=workers[k]->nBetter;
        }
        //cnt = worker1->cnt + worker2->cnt;
        //nbBetter = worker1->nBetter + worker2->nBetter;
        tmpRes = (float) nbBetter / cnt;
        if (cnt > 100000 && !(tmpRes - oldRes > 0.00001 || tmpRes - oldRes < -0.00001))
            break;
        oldRes = tmpRes;
    }

    for(int k=0; k<nbThreads; k++) {
        workers[k]->m_isInterrupted=true;
        threads[k]->terminate();
    }
    //worker1->m_isInterrupted = true;
    //worker2->m_isInterrupted = true;

    //th1->terminate();
    //th2->terminate();

    upProgress();
}


// Ajoute deux tableaux.
QList< QList<int> > Game::add(QList< QList<int> > l1, QList< QList<int> > l2)
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 13; ++j)
            l1[i][j] = l1[i][j] + l2[i][j];
    }

    return l1;
}

void Game::upProgress()
{
    cnt=0;
    nbBetter=0;
    for(int k=0; k<nbThreads; k++) {
        cnt+=workers[k]->cnt;
        nbBetter+=workers[k]->nBetter;
    }
    //cnt = worker1->cnt + worker2->cnt;
    //nbBetter = worker1->nBetter + worker2->nBetter;
    qDebug() << "\n nb de games:" << cnt << " games/s: " << (float) cnt / ((float) QDateTime::currentDateTime().msecsTo(debDate) / (-1000)) << " Result: " << (1 - (float) nbBetter / cnt) * 100;
    mWindow->setRes((float) nbBetter / cnt);
}
