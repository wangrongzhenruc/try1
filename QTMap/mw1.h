#ifndef MW1_H
#define MW1_H

#include <QMainWindow> //#
#include <QImage> //#
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include "rpgobj.h"
#include "world.h"

namespace Ui {
class MW1;
}

class MW1 : public QMainWindow
     //QWidget 是所有用户界面元素的基类
     //QMainWindow、QWidget、QDialog 三个类就是用来创建窗口的，可以直接使用也可以继承后再使用
     //inline void show() { setVisible(true); }
{
    Q_OBJECT

public:
    explicit MW1(QWidget *parent = 0);
    /*explicit用于修饰只有一个参数的类构造函数, 它的作用是表明该构造函数是显示的, 而非隐式的, （如，不允许隐式类型转换）
     * 跟它相对应的另一个关键字是implicit, 意思是隐藏的,类构造函数默认情况下即声明为implicit(隐式).*/
    ~MW1();
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *);

protected slots:
    void randomMove();

private:
    Ui::MW1 *ui;//？为什么在类中定义了一个本类指针类的成员？
    World _game;
    QTimer *timer;
    /*QTimer类提供了重复和单次触发信号的定时器，为定时器提供了一个高级别的编程接口。
     * 使用：首先，创建一个QTimer，连接timeout()信号到适当的槽函数，并调用start()，然后在恒定的时间间隔会发射timeout()信号。
     * 注意：当QTimer的父对象被销毁时，它也会被自动销毁。*/
};

#endif // MW1_H
