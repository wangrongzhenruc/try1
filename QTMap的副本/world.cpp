#include "world.h"
#include "icon.h"
#include "rpgobj.h"
#include <QMediaPlayer>
#include<iostream>
using namespace std;

World::~World(){
    delete this->_player;//
}

void World::initWorld(string mapFile){
    //mpFile就是文件路径
    //TODO 下面的内容应该改为从地图文件装载
    /*e.g.文件格式
       player 5 5
       stone 3 3
       fruit 7 8
     */
    //player 5 5
    this->_player->initObj("player");
    this->_player->setPosX(10);
    this->_player->setPosY(10);

    RPGObj *p1 = new RPGObj;
    p1->initObj("stone");
    p1->setPosX(4);
    p1->setPosY(3);

    RPGObj *p2 = new RPGObj;
    p2->initObj("stone");
    p2->setPosX(6);
    p2->setPosY(5);

    RPGObj *p3 = new Fruit;
    p3->initObj("fruit");
    p3->setPosX(6);
    p3->setPosY(8);

    //依次存到_objs向量中
    this->_objs.push_back(p1);
    this->_objs.push_back(p2);
    this->_objs.push_back(p3);

    //背景音乐
    QMediaPlayer * player = new QMediaPlayer;//QMediaPlayer是一个播放多媒体流的类
    player->setMedia(QUrl("qrc:/sounds/hdl.mp3"));
    player->setVolume(30);
    player->play();
    /* 示例
    player = new QMediaPlayer;
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
    player->setVolume(50);
    player->play();
     */
}


void World::show(QPainter * painter){
    int n = this->_objs.size();
    //显示obj
    for (int i=0;i<n;i++){
        this->_objs[i]->show(painter);
    }
    //显示玩家
    this->_player->show(painter);
}

//未解决
void World::eraseObj(int x, int y){
    vector<RPGObj*>::iterator it; //迭代器
    it = _objs.begin();
    while(it!=_objs.end()){
        int flag1 = ((*it)->getObjType()!="stone"); //不是石头
        int flag2 = ((*it)->getPosX() == x) && ((*it)->getPosY()==y);//位置重叠

        if (flag1 && flag2){
            cout<<(*it)->getObjType()<<endl;
            (*it)->onErase();
            delete (*it);
            it = this->_objs.erase(it);
            /* 在进行单个元素删除后，传入的迭代器指向不变，仍然指向被删除元素的位置，而被删除元素之后的所有元素都向前移动一位，
             * 也就是该迭代器实际上是指向了原来被删除元素的下一个元素。*/
            break;
         }
        else{
            it++;
        }
    }

}

void World::handlePlayerMove(int direction, int steps){
    //计算下一格坐标，擦掉可以被擦掉的obj
    //我觉得这里算法有问题，这个程序里steps其实一直都是1所以不会反映出问题，若steps大于1可能就有问题了
    int x =  this->_player->getNextX(direction);
    int y = this->_player->getNextY(direction);
    this->eraseObj(x,y);
    //移动玩家
    this->_player->move(direction, steps);
}

