#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>
#include <myscroll.h>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("翻金币主场景");
    connect(ui->action_exit,&QAction::triggered,[=](){
        this->close();
    });
  QSound  *sound_main = new QSound(":/res/myDouDZ.wav",this);
  sound_main->setLoops(-1);
  sound_main->play();
  connect(this,&MainScene::closed_voice,[=](){
      sound_main->stop();
  });
  connect(this,&MainScene::open_voice,[=](){
      sound_main->play();
  });
//添加按钮音效
    QSound  *sound_button = new QSound(":/res/TapButtonSound.wav",this);
//添加主按钮
    MyPushButton *button1 = new MyPushButton{":/res/MenuSceneStartButton.png"};
    button1->setParent(this);
    button1->move((this->width()-button1->width())/2,height()*0.7);
//设置关卡选择场景
    choose_scene = new ChooseLevelScene;

    connect(button1,&QPushButton::clicked,this,
    [=](){
        button1->zoom1();
        button1->zoom2();
        sound_main->stop();
        sound_button->play();
        QTimer::singleShot(300,this,
        [=](){
            this->hide();
            choose_scene->setGeometry(this->geometry());
            choose_scene->show();
        });
    });

    connect(choose_scene,&ChooseLevelScene::chooselevelscene_back,this,[=](){
        this->setGeometry(choose_scene->geometry());
        choose_scene->hide();
        this->show();
        emit MainScene::open_voice();
    });
}

MainScene::~MainScene()
{
    delete ui;
}
void MainScene::paintEvent(QPaintEvent *event)
{

    QPainter painter{this};
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap{":/res/PlayLevelSceneBg.png"});

    QPixmap pix;
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())/2,30,pix);
}
