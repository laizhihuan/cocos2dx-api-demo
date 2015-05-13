//
//  SceneGame.cpp
//  Chess
//
//  Created by zhihuanglai on 15/5/12.
//
//
#include "SceneGame.h"

Scene* SceneGame::createScene(bool isRed)
{
    Scene* scene = Scene::create();
    SceneGame* layer = SceneGame::create(isRed);
    scene->addChild(layer);
    return scene;
}

SceneGame* SceneGame::create(bool isRed)
{
    SceneGame* pRet = new SceneGame();
    if(pRet)
    {
        if (pRet->init(isRed)) {
            pRet->autorelease();
        } else {
            pRet->release();
        }
    }
    else
    {
        return NULL;
    }
    
    return pRet;
}

bool SceneGame::init(bool red)
{
    if (!Layer::init()) {
        return false;
    }
    
    //画棋盘
    Sprite* plate = CCSprite::create("background.png");
    this->addChild(plate);
    plate->setAnchorPoint(Vec2::ZERO);
    plate->setPosition(_plateOffset);
    plate->setScale((winSize.height -_plateOffset.y *2) / plate->getContentSize().height);
    
    //摆棋子
    for (int i=0; i<32; i++) {
        _stone[i] = Stone::create(i);
        addChild(_stone[i]);
    }
    
    return true;
}
