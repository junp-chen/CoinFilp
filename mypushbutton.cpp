#include "mypushbutton.h"
#include <QDebug>
MyPushButton:: MyPushButton(QString pic1,QString pic2):pic_filename1(pic1),pic_filename12(pic2)
{
    QPixmap pix;
    bool set = pix.load(pic1);
    if(set == 0)
    {
        qDebug() << "load fail";
    }

    setFixedSize(pix.width(),pix.height());//设置按钮大小

    setIcon(QIcon(pic1));//设置按钮图片

    setIconSize(QSize(pix.width(),pix.height()));//设置按钮图片大小

    setStyleSheet("QPushButton{border:0px;}");

}
void MyPushButton::zoom1()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::zoom2()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(this->x(),this->y()+20,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::mousePressEvent(QMouseEvent *event)
{
    if(this->pic_filename12 != "")
    {
        QPixmap pix;
        bool set = pix.load(pic_filename12);
        if(set == 0)
        {
            qDebug() << "error:load pic_filename12 fail";
        }

        setFixedSize(pix.width(),pix.height());//设置按钮大小

        setIcon(pix);//设置按钮图片

        setIconSize(QSize(pix.width(),pix.height()));//设置按钮图片大小

        setStyleSheet("QPushButton{border:0px;}");
    }
    return QPushButton::mousePressEvent(event);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(this->pic_filename12 != "")
    {
        QPixmap pix;
        bool set = pix.load(pic_filename1);
        if(set == 0)
        {
            qDebug() << "error:load pic_filename12 fail";
        }

        setFixedSize(pix.width(),pix.height());//设置按钮大小

        setIcon(pix);//设置按钮图片

        setIconSize(QSize(pix.width(),pix.height()));//设置按钮图片大小

        setStyleSheet("QPushButton{border:0px;}");
    }
    return QPushButton::mouseReleaseEvent(event);
}
