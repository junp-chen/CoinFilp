#include "chooselevelscene.h"
#include <QIcon>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <playscene.h>
#include <QSound>
#include <QScrollArea>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon{":/res/Coin0001.png"});
    this->setWindowTitle("翻转金币场景");
    QMenuBar *menubar = new QMenuBar(this);
    this->setMenuBar(menubar);
    QMenu *menu1 = menubar->addMenu("开始");
    QAction * action1 = menu1->addAction("退出");
    connect(action1,&QAction::triggered,this,[=](){
        this->close();
    });


    //加载关卡音效
    QSound *sound_choose = new QSound{":/res/TapButtonSound.wav",this};
    QSound *sound_back = new QSound{":/res/BackButtonSound.wav",this};

    //创建返回按钮
    MyPushButton *pushbutton_back = new MyPushButton{":/res/BackButton",":/res/BackButtonSelected"};
    pushbutton_back->setParent(this);
    pushbutton_back->move(this->width()-pushbutton_back->width(),this->height()-pushbutton_back->height());

    connect(pushbutton_back,&QPushButton::clicked,this,[=](){
        sound_back->play();
        QTimer::singleShot(400,this,[=](){
             emit chooselevelscene_back();
        });
    });
//创建关卡按钮
    for(int i = 0;i < 20;i++)
    {
        MyPushButton *levelBton = new MyPushButton{":/res/LevelIcon"};
        levelBton->setParent(this);
        levelBton->move(25+i%4*70,130+i/4*70);
        connect(levelBton,&QPushButton::clicked,this,[=]()
        {
            sound_choose->play();
           // qDebug() << QString("进入第%1关").arg(i+1);
            PlayScene *play_scene = new PlayScene{i+1};
            play_scene->setGeometry(this->geometry());
            this->hide();
            play_scene->show();

            connect(play_scene,&PlayScene::delete_play,this,[=]()
            {
                this->setGeometry(play_scene->geometry());
                delete play_scene;
              //  play_scene = NULL;
                this->show();
            });
        });

        QLabel *lable = new QLabel;
        lable->setParent(this);
        lable->move(25+i%4*70,130+i/4*70);
        lable->setFixedSize(levelBton->width(),levelBton->height());
        lable->setText(QString::number(i+1));
        lable->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        lable->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}
void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap{":/res/OtherSceneBg.png"});

    QPixmap pix;
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())/2,30,pix);
}
