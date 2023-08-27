#include "playscene.h"
#include <QPropertyAnimation>
#include <QSound>
PlayScene::PlayScene(int _level):level(_level)
{
    //添加音效资源
    QSound *sound_back = new QSound(":/res/BackButtonSound.wav",this);
    QSound *sound_coin = new QSound(":/res/ConFlipSound.wav",this);
    QSound *sound_gameover = new QSound(":/res/LevelWinSound.wav",this);

    setWindowTitle(QString("关卡%1").arg(level));
    setFixedSize(320,588);
    QPixmap pix1 = QPixmap(":/res/Coin0001.png");
    setWindowIcon(QIcon(pix1));

    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);
    QMenu *menu = menubar->addMenu("开始");
    QAction *action_exit = menu->addAction("退出");
    connect(action_exit,&QAction::triggered,this,[=]
    {
        this->close();
    });
    //关卡返回按钮的实现
    MyPushButton *button_back = new MyPushButton{":/res/BackButton.png",":/res/BackButtonSelected.png"};
    button_back->setParent(this);//挂对象树
    button_back->move(this->width()-button_back->width(),this->height()-button_back->height());
    //信号连接
    connect(button_back,&QPushButton::clicked,this,[=]()
    {
        sound_back->play();
        QTimer::singleShot(400,this,[=](){
                emit delete_play();
        });
    });

    //关卡标签实现
    QLabel *lable_level = new QLabel{this};
    lable_level->setText(QString("Level:%1").arg(level));
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    lable_level->setFont(font);
    lable_level->setGeometry(30,height()-50,120,50);

    //载入关卡胜利标签
    QLabel *lable_win = new QLabel(this);
    QPixmap pix_win{":/res/LevelCompletedDialogBg"};
    lable_win->setPixmap(pix_win);
    lable_win->setFixedSize(pix_win.width(),pix_win.height());
    lable_win->move(this->width()/2-pix_win.width()/2,-pix_win.height());
    //载入关卡数据

    dataConfig _data;
    for(int i = 0;i < 4;i++)
    {
        for(int j =0;j < 4;j++)
        {
            data[i][j] = _data.mData[level][i][j];
        }
    }
    //关卡金币背景的图片加载
    QPixmap pix_coin;
    pix_coin.load(":/res/BoardNode");
    QString str;
    for(int i = 0;i < 16;i++)
    {
         //关卡金币背景的创建
         QLabel *coin_scene = new QLabel{this};
         coin_scene->setPixmap(pix_coin);
         coin_scene->setFixedSize(pix_coin.width(),pix_coin.height());
         coin_scene->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
         coin_scene->move(57+i%4*50,200+i/4*50);

         //创建金币
        if(data[i%4][i/4] == 1)
            str = ":/res/Coin0001.png";
        else
            str = ":/res/Coin0008.png";

         Coin *coin = new Coin{str};
         coins[i%4][i/4] = coin;
         coin->setParent(this);//设置对象树
         coin->move(59+i%4*50,203+i/4*50);
         coin->pos_x = i%4;
         coin->pos_y = i/4;
         coin->flag = data[i%4][i/4]>0?1:3;//更新二维数组中的数据

         connect(coin,&QPushButton::clicked,this,[=](){
             sound_coin->play();//设置点击音效
             //先更新游戏数据
            this->data[i%4][i/4] = !data[i%4][i/4];
             if(coin->pos_x-1 >= 0)//更新数据是注意判断边界，否则会导致游戏异常退出
             {
                 this->data[coin->pos_x-1][coin->pos_y] = !data[coin->pos_x-1][coin->pos_y];
             }
             if(coin->pos_x+1 <= 3)
             {
                 this->data[coin->pos_x+1][coin->pos_y] = !data[coin->pos_x+1][coin->pos_y];
             }
             if(coin->pos_y-1 >= 0)
             {
                 this->data[coin->pos_x][coin->pos_y-1] = !data[coin->pos_x][coin->pos_y-1];
             }
             if(coin->pos_y+1 <= 3)
             {
                 this->data[coin->pos_x][coin->pos_y+1] = !data[coin->pos_x][coin->pos_y+1];
             }
             //判断游戏是否胜利
            game_win = true;
            for(int i = 0;i < 4;i++)
            {
                for(int j =0;j < 4;j++)
                {
                    if(data[i][j] == 0)
                    {
                        game_win = false;
                        break;
                    }
                }
            }
            //游戏胜利
            if(game_win == true)
            {
                for(int i = 0;i < 4;i++)
                {
                    for(int j =0;j < 4;j++)
                    {
                       coins[i][j]->game_win = true;
                    }
                }
              qDebug() << "游戏胜利";
              //移动胜利图片
              QPropertyAnimation *animation_win = new QPropertyAnimation{lable_win,"geometry"};
              animation_win->setDuration(1000);
              animation_win->setStartValue(QVariant(QRect(lable_win->x(),lable_win->y(),lable_win->width(),lable_win->height())));
              animation_win->setEndValue(QVariant(QRect(lable_win->x(),lable_win->y()+160,lable_win->width(),lable_win->height())));
              animation_win->setEasingCurve(QEasingCurve::OutElastic);
              animation_win->start();

              sound_gameover->play();
            }
           //最后再进行特效显示，防止在金币翻转特效延时时数据更新不及时，若鼠标点击过快，会导致数据更新不及时错过游戏结束的判断
            coin->changeFlag();
            QTimer::singleShot(300,this,[=](){
                if(coin->pos_x-1 >= 0)//同理金币特显也要注意判断边界，否则会导致游戏异常退出
                {
                    coins[coin->pos_x-1][coin->pos_y]->changeFlag();
                }
                if(coin->pos_x+1 <= 3)
                {
                    coins[coin->pos_x+1][coin->pos_y]->changeFlag();
                }
                if(coin->pos_y-1 >= 0)
                {
                    coins[coin->pos_x][coin->pos_y-1]->changeFlag();
                }
                if(coin->pos_y+1 <= 3)
                {
                    coins[coin->pos_x][coin->pos_y+1]->changeFlag();
                }
            });
         });
    }
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    QPixmap pix(":/res/PlayLevelSceneBg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
