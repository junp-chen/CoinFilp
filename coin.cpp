#include "coin.h"
#include <QDebug>
Coin:: Coin(QString coin_pix)
{
    QPixmap pix_coin{coin_pix};
    this->setFixedSize(pix_coin.width(),pix_coin.height());
    this->setIcon(pix_coin);
    this->setIconSize(QSize(pix_coin.width(),pix_coin.height()));
    this->setStyleSheet("QPushButton{border:0px}");//设置图片风格
    timer1 = new QTimer(this);
    connect(timer1,&QTimer::timeout,this,[=](){
        static int animationed_num = 0;
        animationed_num++;
        QPixmap pix_coin;
        if(flag == 2)
        {
            if(dd_flag == 1)
            {
                pix_coin.load(QString(":/res/Coin000%1.png").arg(current++));
            }
            else if(dd_flag == 4)
            {
                 pix_coin.load(QString(":/res/Coin000%1.png").arg(current++));
            }
        }
        else if(flag == 4)
        {
            if(dd_flag == 3)
            {
                pix_coin.load(QString(":/res/Coin000%1.png").arg(current--));
            }

            else if(dd_flag == 2)
            {
                pix_coin.load(QString(":/res/Coin000%1.png").arg(current--));
            }
        }
        this->setIcon(pix_coin);
        setIconSize(QSize(pix_coin.width(),pix_coin.height()));
        this->setStyleSheet("QPushButton{border:0px}");//设置图片风格
        if(animationed_num == 2)
        {
            isanimation = false;
            animationed_num = 0;
        }
        if(current >8 || current < 1)
        {
            if(this->flag == 2 && dd_flag == 1)
                this->flag = 3;
            else if(this->flag == 2 && dd_flag == 4)
                this->flag = 3;
            else if(this->flag == 4 && dd_flag == 3)
                this->flag = 1;
            else if(this->flag == 4 && dd_flag == 2)
                this->flag = 1;
            timer1->stop();
            isanimation = false;
            animationed_num = 0;
        }
    });
}
void Coin::changeFlag()
{
    dd_flag = flag;
    if(flag == 1)
    {
       flag++;
       current = 1;
    }
    else if(flag == 3)
    {
       flag++;
       current = 8;
    }
    else if(flag == 2)
    {
        flag = 4;
        current -= 2;
        if(current <= 0)
            current = 1;
    }
    else if(flag == 4)
    {
        flag = 2;
        current += 2;
        if(current >= 9)
            current = 8;
    }
    timer1->start(20);
    isanimation = true;
}
void Coin::mousePressEvent(QMouseEvent *event)
{
    if(isanimation == true || game_win == true)
    {
        return;
    }
    else
        return QPushButton::mousePressEvent(event);
}
