#ifndef MYSCROLL_H
#define MYSCROLL_H

#include <QWidget>

namespace Ui {
class MyScroll;
}

class MyScroll : public QWidget
{
    Q_OBJECT

public:
    explicit MyScroll(QWidget *parent = nullptr);
    ~MyScroll();

private:
    Ui::MyScroll *ui;
};

#endif // MYSCROLL_H
