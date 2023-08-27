#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <chooselevelscene.h>
#include <myscroll.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void paintEvent(QPaintEvent *event);
private:
    Ui::MainScene *ui;
    ChooseLevelScene *choose_scene = nullptr;
signals:
    void closed_voice();
    void open_voice();
};
#endif // MAINSCENE_H
