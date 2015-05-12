//
//  MainScene.cpp
//  Chess
//
//  Created by zhihuanglai on 15/5/8.
//
//

#include "MainScene.h"
#include "Common.h"

bool MainScene::init()
{
    Layer::init();
    
    int driff = 100;
    
    // 创建红棋
    Sprite* sprite1 = Sprite::create("bkg2.png");
	addChild(sprite1);
	sprite1->setPosition(ccp(winSize.width/2 - driff, winSize.height / 2));
    
    // 创建黑棋
    Sprite* sprite2 = Sprite::create("bkg1.png");
    addChild(sprite2);
    sprite2->setPosition(ccp(winSize.width/2 + driff, winSize.height/2));
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    return true;
}

bool MainScene::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void MainScene::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}

void MainScene::onTouchEnded(Touch *touch, Event *unused_event)
{
    log("click on touch ended");
}

void MainScene::onTouchCancelled(Touch *touch, Event *unused_event)
{
    
}

void MainScene::update(float delta)
{
}

