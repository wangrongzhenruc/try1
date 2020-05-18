#include "mw1.h"
#include "ui_mw1.h"
#include "icon.h"
#include <QTime>
#include<QTimer>
#include <map>
#include <iostream>

using namespace std;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);
    /*
     * ui->setupUi(this)是由.ui文件生成的类的构造函数，这个函数的作用是对界面进行初始化，
     * 它按照我们在Qt设计器里设计的样子把窗体画出来，把我们在Qt设计器里面定义的信号和槽建立起来。
     */

    //init game world
    _game.initWorld("mapFile");//TODO 应该是输入有效的地图文件路径mapFile

    timer = new QTimer(this);
    //创建一个QTimer，连接timeout()信号到适当的槽函数，并调用start()，然后在恒定的时间间隔会发射timeout()信号。
    connect(timer,SIGNAL(timeout()),this,SLOT(randomMove()));
        //randomMove()为自定义槽函数
    timer->start(50);
    timer->setInterval(500);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//设置随机种子
    //？为什么要设置随机？
}

/*关于信号和槽：
 * 当某个事件发生之后，比如，按钮检测到自己被点击了一下，它就会发出一个信号（signal）。
 * 这种发出是没有目的的，类似广播。如果有对象对这个信号感兴趣，它就会使用连接（connect）函数，
 * 将想要处理的信号和自己的一个函数（称为槽（slot））绑定来处理这个信号。
 * 也就是说，当信号发出时，被连接的槽函数会自动被回调。
 */

MW1::~MW1()
{
    delete ui;
}

void MW1::paintEvent(QPaintEvent *e){
    QPainter *pa;//QPainter可以在QPaintDevice类上绘制各种图形，只能在类对象的paintEvent()函数中绘制图形
    pa = new QPainter();
    pa->begin(this);//将MW1作为画布
    this->_game.show(pa);//显示游戏世界所有玩家和obj
    pa->end();
    delete pa;
}

/*关于paintEvent
 * paintEvent(QPaintEvent*)函数是QWidget类中的虚函数，用于ui的绘制，
 * 会在多种情况下被其他函数自动调用，比如update()时。
 * 运行时机：
 * 一个重绘事件用来重绘一个部件的全部或者部分区域，下面几个原因的任意一个都会发生重绘事件：
 * （1）repaint()函数或者update()函数被调用；（2）被隐藏的部件现在被重新显示；（3）其他一些原因。
 */

void MW1::keyPressEvent(QKeyEvent *e)
{
    //direction = 1,2,3,4 for 上下左右
    if(e->key() == Qt::Key_A)
    {
        this->_game.handlePlayerMove(3,1);
    }
    else if(e->key() == Qt::Key_D)
    {
        this->_game.handlePlayerMove(4,1);
    }
    else if(e->key() == Qt::Key_W)
    {
        this->_game.handlePlayerMove(1,1);
    }
    else if(e->key() == Qt::Key_S)
    {
         this->_game.handlePlayerMove(2,1);
    }
    this->repaint();
}

void MW1::randomMove(){

    int d = 1 + rand()%4;//生成随机运动的方向
    this->_game.handlePlayerMove(d,1);
    this->repaint();
}
