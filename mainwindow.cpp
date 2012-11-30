#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "game.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->refresh, SIGNAL(clicked()), this, SLOT(refresh()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    Game* game = new Game(this);

    mflop1 = ui->flop1->text().toInt();
    mflop2 = ui->flop2->text().toInt();
    mflop3 = ui->flop3->text().toInt();
    mturn = ui->turn->text().toInt();
    mriver = ui->river->text().toInt();
    mh1 = ui->h1->text().toInt();
    mh2 = ui->h2->text().toInt();
    mNbPlayers = ui->nbPlayers->text().toInt();

    game->refresh();
    delete game;
}

static int comb(int a, int b)
{
    if (a > b)
        return 0;

    if (a == 0)
        return 1;

    int res = 1;

    for (int i = 1; i <= a; ++i)
        res = res * ((b - i + 1) / i);

    return res;
}

void MainWindow::setRes(float res)
{
    setResult(res, mNbPlayers);
}

void MainWindow::setResult(float res, int nbPlayers)
{
    QString tmp;

    res = 1 - res;

    for (int m = 1; m < nbPlayers; ++m)
        res *= res;

    ui->victory->setText("Victory : " + tmp.number(res * 100) + "\%");
}
