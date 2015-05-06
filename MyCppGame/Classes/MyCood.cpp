//
//  MyCood.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 15/4/23.
//
//

#include "MyCood.h"

USING_NS_CC;


//是cocos渲染树的根节点，是一个独立游戏逻辑模块的封装
Scene* MyCood::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MyCood::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MyCood::init()
{
    //游戏的touch事件
     MyCommonLayer::init();
    
    
    return true;
}