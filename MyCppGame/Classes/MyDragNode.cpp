//
//  MyDragNode.cpp
//  MyCppGame
//
//  拖动节点移动
//  Created by zhihuanglai on 15/4/21.
//
//

#include "MyDragNode.h"



USING_NS_CC;


//是cocos渲染树的根节点，是一个独立游戏逻辑模块的封装
Scene* MyDragNode::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MyDragNode::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MyDragNode::init()
{
    //游戏的touch事件
    Layer::init();
    
    auto sprite = Sprite::create("CloseNormal.png");
    addChild(sprite);
    sprite->setPosition(ccp(100,100));
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    _sprite = sprite;
    
    return true;
}

bool MyDragNode::onTouchBegan(Touch *touch, Event *unused_event)
{
    log("MyDragNode::onTouchBegan");
    Rect rect = _sprite->boundingBox();
    Point pt = touch->getLocation();
    return rect.containsPoint(pt);
}

void MyDragNode::onTouchMoved(Touch *touch, Event *unused_event)
{
    log("MyDragNode::onTouchMoved");
    Point delta = touch->getDelta();
    Point oldPos = _sprite->getPosition();
    Point newPos = oldPos + delta;
    _sprite->setPosition(newPos);
};

void MyDragNode::onTouchEnded(Touch *touch, Event *unused_event)
{
    log("MyDragNode::onTouchEnded");
};

void MyDragNode::onTouchCancelled(Touch *touch, Event *unused_event)
{
    log("MyDragNode::onTouchCancelled");
};


