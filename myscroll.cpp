#include "myscroll.h"
#include "ui_myscroll.h"

MyScroll::MyScroll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyScroll)
{
    ui->setupUi(this);
}

MyScroll::~MyScroll()
{
    delete ui;
}
