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

int determineCarte(int valeur, int couleur){
    int newValeur;
    if(valeur == 0)
        return 0;

    newValeur = ((couleur+1)*100)+valeur;

    return newValeur;
}

void MainWindow::refresh()
{
    Game* game = new Game(this);

    mflop1 = determineCarte(ui->flop1_val->currentIndex(), ui->flop1_col->currentIndex());
    mflop2 = determineCarte(ui->flop2_val->currentIndex(), ui->flop2_col->currentIndex());
    mflop3 = determineCarte(ui->flop3_val->currentIndex(), ui->flop3_col->currentIndex());
    mturn = determineCarte(ui->turn_val->currentIndex(), ui->turn_col->currentIndex());
    mriver = determineCarte(ui->river_val->currentIndex(), ui->river_col->currentIndex());
    mh1 = determineCarte(ui->h1_val->currentIndex(), ui->h1_col->currentIndex());
    mh2 = determineCarte(ui->h2_val->currentIndex(), ui->h2_col->currentIndex());
    mNbPlayers = ui->nbPlayers->text().toInt();

    game->refresh();

    delete game;
}

void MainWindow::setRes(float res)
{
    setResult(res, mNbPlayers);
}

void MainWindow::setResult(float res, int nbPlayers)
{
    QString tmp;

    res = 1 - res;


    ui->victoire->setText("Victory : " + tmp.number(res * 100) + "\%");
    QFont f("Arial", 24);
    ui->victoire->setFont( f);
    ui->victoire->setAlignment(Qt::AlignCenter);
}
