#ifndef COIN_H
#define COIN_H

#include <QPushButton>
#include <QTimer>
#include <QEvent>
class Coin : public QPushButton
{
    Q_OBJECT
public:
   // explicit Coin(QWidget *parent = nullptr);
    Coin(QString coin_pix);
    int flag;//四个状态，1：金币状态2、金币->银币3、银币状态4、银币->金币
    int dd_flag;//记录前一次的状态
    int pos_x;
    int pos_y;
    QTimer *timer1;
    int min = 1;//翻转特性起始图片标记
    int max = 8;//
    int current = -1;
    bool isanimation = false;
    bool game_win = false;//游戏胜利则鼠标点击无效,初始默认失败，可以点击

    void changeFlag();
    void mousePressEvent(QMouseEvent *event);
signals:

};

#endif // COIN_H
