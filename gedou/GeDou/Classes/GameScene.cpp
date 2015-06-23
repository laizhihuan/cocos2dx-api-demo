//
//  GameScene.cpp
//  GeDou
//
//  Created by zhihuanglai on 15/6/18.
//
//

#include "GameScene.h"

Scene* GameScene::createScene()
{
    Scene *scene = Scene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //添加游戏背景
    Sprite *pSprite = Sprite::create("background_1.jpg");
    pSprite->setPosition(Vec2(visibleSize.width/2+origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite,0);
    
    //添加英雄精灵
    hero = Hero::create();
    hero->initHeroSprite("zhaoyun.png");
    hero->setPosition(Vec2(300, 300));
    this->addChild(hero,1);
    
    //添加摇杆
    rocker = HRocker::createHRocker("Direction_bt.png", "Direction_bc.png", Vec2(110,60));
    this->addChild(rocker,2);
    rocker->startRocker(true);
    
    //启动update事件
    this->scheduleUpdate();
    
    return true;
}

void GameScene::update(float delta)
{
    switch (rocker->rockerDirection) {
        case 1:
            //hero->setAnimation(<#const char *namePlist#>, <#const char *namePng#>, <#const char *nameEach#>, <#const unsigned int num#>,)
            break;
            
        default:
            break;
    }
}