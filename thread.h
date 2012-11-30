#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include "game.h"

class Thread : public QThread
{
public:
    Thread();
    void run();
};

#endif // THREAD_H
