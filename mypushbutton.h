#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <QEvent>
class MyPushButton : public QPushButton
{
    Q_OBJECT
private:
    QString pic_filename1;
    QString pic_filename12;//按下按钮后切换的场景
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString pic1,QString pic2 = "");
    void zoom1();//0:down 1:up
    void zoom2();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:

};

#endif // MYPUSHBUTTON_H
