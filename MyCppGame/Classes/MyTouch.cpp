//
//  MyTouch.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 15/4/20.
//
//

#include <MyTouch.h>

USING_NS_CC;


//是cocos渲染树的根节点，是一个独立游戏逻辑模块的封装
Scene* MyTouch::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MyTouch::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MyTouch::init()
{
    //游戏的touch事件
    
    
    return true;
}
