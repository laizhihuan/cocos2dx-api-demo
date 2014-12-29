//
//  HiTouchSence.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 14-8-6.
//
//

#include "HiTouchSence.h"

USING_NS_CC;

Scene* HiTouchSence::createScene() {
    Scene * scene = Scene::create();
    
    HiTouchSence * layer = HiTouchSence::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool HiTouchSence::init() {
    Size size = Director::getInstance()->getVisibleSize();
    
    auto * label = Label::createWithSystemFont("on touch me", "宋体", 30);
    label->setPosition(Vec2(size.width/2,size.height/2));
    
    addChild(label);
    
    //添加监听器
    auto listener = EventListenerTouchOneByOne::create();
    
    //监听器的闭包函数
    listener->onTouchBegan = [label](Touch *t,Event *event) {
        //触摸目标判断
        if(label->getBoundingBox().containsPoint(t->getLocation())) {
            log("touch me");
        }
        return true;
    };
    
    //如果onTouchBegan return true,onTouchMoved才会执行
    listener->onTouchMoved = [](Touch *t,Event *e) {
        log("touch moved");
    };
    
    //注册label监听器
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

    
    return true;
}
