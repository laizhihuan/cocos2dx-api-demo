//
//  HiImageSence.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 14-8-5.
//
//

#include "HiImageSence.h"

Scene* HiImageSence::createSence() {
    Scene* scene = Scene::create();
    
    HiImageSence * layer = HiImageSence::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool HiImageSence::init() {
    Size size = Director::getInstance()->getVisibleSize();
    Sprite *s = Sprite::create("HelloWorld.png");
    s->setPosition(Vec2(size.width/2, size.height/2));
    addChild(s);
    
    return true;
}