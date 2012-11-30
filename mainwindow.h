#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void setResult(float res, int nbPlayers = 0);

public slots:
    void refresh();
    void setRes(float res);

signals:
    void Refresh();

public:
    Ui::MainWindow *ui;
    int mflop1;
    int mflop2;
    int mflop3;
    int mturn;
    int mriver;
    int mh1;
    int mh2;
    int mNbPlayers;
};

#endif // MAINWINDOW_H
