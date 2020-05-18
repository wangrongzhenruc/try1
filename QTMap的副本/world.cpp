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
    //mpFile�����ļ�·��
    //TODO ���������Ӧ�ø�Ϊ�ӵ�ͼ�ļ�װ��
    /*e.g.�ļ���ʽ
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

    //���δ浽_objs������
    this->_objs.push_back(p1);
    this->_objs.push_back(p2);
    this->_objs.push_back(p3);

    //��������
    QMediaPlayer * player = new QMediaPlayer;//QMediaPlayer��һ�����Ŷ�ý��������
    player->setMedia(QUrl("qrc:/sounds/hdl.mp3"));
    player->setVolume(30);
    player->play();
    /* ʾ��
    player = new QMediaPlayer;
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
    player->setVolume(50);
    player->play();
     */
}


void World::show(QPainter * painter){
    int n = this->_objs.size();
    //��ʾobj
    for (int i=0;i<n;i++){
        this->_objs[i]->show(painter);
    }
    //��ʾ���
    this->_player->show(painter);
}

//δ���
void World::eraseObj(int x, int y){
    vector<RPGObj*>::iterator it; //������
    it = _objs.begin();
    while(it!=_objs.end()){
        int flag1 = ((*it)->getObjType()!="stone"); //����ʯͷ
        int flag2 = ((*it)->getPosX() == x) && ((*it)->getPosY()==y);//λ���ص�

        if (flag1 && flag2){
            cout<<(*it)->getObjType()<<endl;
            (*it)->onErase();
            delete (*it);
            it = this->_objs.erase(it);
            /* �ڽ��е���Ԫ��ɾ���󣬴���ĵ�����ָ�򲻱䣬��Ȼָ��ɾ��Ԫ�ص�λ�ã�����ɾ��Ԫ��֮�������Ԫ�ض���ǰ�ƶ�һλ��
             * Ҳ���Ǹõ�����ʵ������ָ����ԭ����ɾ��Ԫ�ص���һ��Ԫ�ء�*/
            break;
         }
        else{
            it++;
        }
    }

}

void World::handlePlayerMove(int direction, int steps){
    //������һ�����꣬�������Ա�������obj
    //�Ҿ��������㷨�����⣬���������steps��ʵһֱ����1���Բ��ᷴӳ�����⣬��steps����1���ܾ���������
    int x =  this->_player->getNextX(direction);
    int y = this->_player->getNextY(direction);
    this->eraseObj(x,y);
    //�ƶ����
    this->_player->move(direction, steps);
}

