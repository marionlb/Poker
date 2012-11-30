/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Nov 30 17:12:55 2012
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *flop1;
    QLineEdit *h2;
    QLineEdit *flop3;
    QLineEdit *turn;
    QLineEdit *flop2;
    QLineEdit *h1;
    QLineEdit *river;
    QPushButton *refresh;
    QLineEdit *nbPlayers;
    QPushButton *victory;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(727, 203);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        flop1 = new QLineEdit(centralwidget);
        flop1->setObjectName(QString::fromUtf8("flop1"));
        flop1->setGeometry(QRect(120, 10, 113, 20));
        h2 = new QLineEdit(centralwidget);
        h2->setObjectName(QString::fromUtf8("h2"));
        h2->setGeometry(QRect(260, 40, 113, 20));
        flop3 = new QLineEdit(centralwidget);
        flop3->setObjectName(QString::fromUtf8("flop3"));
        flop3->setGeometry(QRect(120, 70, 113, 20));
        turn = new QLineEdit(centralwidget);
        turn->setObjectName(QString::fromUtf8("turn"));
        turn->setGeometry(QRect(120, 100, 113, 20));
        flop2 = new QLineEdit(centralwidget);
        flop2->setObjectName(QString::fromUtf8("flop2"));
        flop2->setGeometry(QRect(120, 40, 113, 20));
        h1 = new QLineEdit(centralwidget);
        h1->setObjectName(QString::fromUtf8("h1"));
        h1->setGeometry(QRect(260, 10, 113, 20));
        river = new QLineEdit(centralwidget);
        river->setObjectName(QString::fromUtf8("river"));
        river->setGeometry(QRect(120, 130, 113, 20));
        refresh = new QPushButton(centralwidget);
        refresh->setObjectName(QString::fromUtf8("refresh"));
        refresh->setGeometry(QRect(20, 30, 75, 23));
        nbPlayers = new QLineEdit(centralwidget);
        nbPlayers->setObjectName(QString::fromUtf8("nbPlayers"));
        nbPlayers->setGeometry(QRect(530, 20, 113, 20));
        victory = new QPushButton(centralwidget);
        victory->setObjectName(QString::fromUtf8("victory"));
        victory->setGeometry(QRect(280, 80, 371, 61));
        QFont font;
        font.setPointSize(20);
        victory->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 727, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(flop1, flop2);
        QWidget::setTabOrder(flop2, flop3);
        QWidget::setTabOrder(flop3, turn);
        QWidget::setTabOrder(turn, river);
        QWidget::setTabOrder(river, h1);
        QWidget::setTabOrder(h1, h2);
        QWidget::setTabOrder(h2, refresh);
        QWidget::setTabOrder(refresh, nbPlayers);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        flop1->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        h2->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        flop3->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        turn->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        flop2->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        h1->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        river->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        refresh->setText(QApplication::translate("MainWindow", "Refresh", 0, QApplication::UnicodeUTF8));
        nbPlayers->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        victory->setText(QApplication::translate("MainWindow", "Victory probability : 0%", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
