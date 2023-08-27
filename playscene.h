#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QString>
#include <mypushbutton.h>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <coin.h>
#include "dataconfig.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int _level);
    void paintEvent(QPaintEvent *event);
private:
    int level = 0;
    int data[4][4];
    Coin *coins[4][4];
    bool game_win = true;
signals:
     void delete_play();
};

#endif // PLAYSCENE_H
