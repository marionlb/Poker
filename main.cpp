#include <QApplication>
#include <QPushButton>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow *mWindow = new MainWindow();
    mWindow->show();

    return app.exec();
}
