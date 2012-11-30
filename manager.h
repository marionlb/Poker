#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>

class Game;

class Manager : public QObject
{
    Q_OBJECT
public:
    Manager(Game *g);

    void Manage();

    Game *g;
};

#endif // MANAGER_H
