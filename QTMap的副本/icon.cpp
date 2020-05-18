#include "icon.h"
#include<iostream>
int ICON::GRID_SIZE = 32;

//创建一个pair数组存所有图标的信息，用来初始化map，map相当于一个图标素材库
pair<string,ICON> pairArray[] =
    //pair是将2个数据组合成一组数据，当需要这样的需求时就可以使用pair
{
    make_pair("player",ICON("player",1,13, 1, 2)),//直接调用make_pair生成pair对象
    make_pair("stone",ICON("stone",4,9, 1, 1)),
    make_pair("fruit",ICON("fruit",3,6, 1, 1))
};

map<string,ICON> ICON::GAME_ICON_SET(pairArray,pairArray+sizeof(pairArray)/sizeof(pairArray[0]));
/* map是一个关联容器，它提供key-value对应
 * key称为关键字，每个关键字只能在map中出现一次，value称为该关键字的值*/
//这行代码，是把ICON::GAME_ICON_SET这个map用列表初始化，
//括号内的(pairArray,pairArray+sizeof(pairArray)/sizeof(pairArray[0]))就是列表
//pairArray：数组开始地址； pairArray+sizeof(pairArray)/sizeof(pairArray[0])：数组结束地址


ICON::ICON(string name, int x, int y, int w, int h){
    this->typeName = name;
    this->srcX = x; //图标在素材图中的位置
    this->srcY = y;
    this->width = w; //图标尺寸
    this->height = h;
}

ICON ICON::findICON(string type){
    map<string,ICON>::iterator kv;
    /*迭代器(iterator)是一中检查容器内元素并遍历元素的数据类型，每种容器类型都定义了自己的iterator类型，
    如：vector<int>::iterator iter;这条语句定义了一个名为iter的变量*/
    kv = ICON::GAME_ICON_SET.find(type);
    /* 用find函数来定位数据出现位置，它返回一个迭代器（kv），当数据出现时，
     * 它返回数据所在位置的迭代器，如果map中没有要查找的数据，它返回的迭代器等于end函数返回的迭代器。
     * 查找map中是否包含某个关键字条目用find()方法，传入的参数是要查找的key */
    if (kv==ICON::GAME_ICON_SET.end()){
       cout<<"Error: cannot find ICON"<<endl;
       return ICON();
    }
    else{
        return kv->second;
        //map中key-value就是first-secon
        //在这里first就是type， second就是icon类的对象（type相当于一个标签，贴在icon对象上）
    }
}
