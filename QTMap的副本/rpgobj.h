#ifndef RPGOBJ_H
#define RPGOBJ_H
#include <QMediaPlayer>
#include <QImage>
#include <QPainter>
#include <string>
#include <icon.h>
#include <map>
using namespace std;
class RPGObj
{//游戏世界中所有对象
public:
    RPGObj(){}

    void initObj(string type);
    void show(QPainter * painter);

    //设置对象在游戏世界中的位置坐标
    void setPosX(int x){this->_pos_x=x;}
    void setPosY(int y){this->_pos_y=y;}

    //获取对象在游戏世界中的位置坐标
    int getPosX() const{return this->_pos_x;}
    int getPosY() const{return this->_pos_y;}
    //获取对象图标宽、高
    int getHeight() const{return this->_icon.getHeight();}
    int getWidth() const{return this->_icon.getWidth();}

    //对象是否可以被遮挡
    bool canCover() const{return this->_coverable;}
    //是否可以被吃掉
    bool canEat() const{return this->_eatable;}

    int getNextX(int direction);
    int getNextY(int direction);

    virtual void onErase();//吃东西音效

    string getObjType() const{return this->_icon.getTypeName();}//返回类名

protected:
    //所有坐标，单位均为游戏中的格
    QImage _pic;
    int _pos_x, _pos_y;//该物体在游戏中当前位置（左上角坐标）
    ICON _icon;//可以从ICON中获取对象的素材，尺寸等信息
    bool _coverable;
    bool _eatable;
};

#endif // RPGOBJ_H
