#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <mypushbutton.h>
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
private:

signals:
    void chooselevelscene_back();
};

#endif // CHOOSELEVELSCENE_H
