#include "manager.h"

#include "game.h"


Manager::Manager(Game *g)
{
    this->g = g;
}

void Manager::Manage()
{
    qDebug() << "TET";
    g->n++;
    if (g->n == 2)
        g->upProgress();
}
