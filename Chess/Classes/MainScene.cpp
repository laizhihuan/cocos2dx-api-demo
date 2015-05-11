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
    
    Sprite* sprite1 = Sprite::create("bkg2.png");
	addChild(sprite1);
	sprite1->setPosition(ccp(winSize.width/2 - driff, winSize.height / 2));
    
    Sprite* sprite2 = Sprite::create("bkg1.png");
    addChild(sprite2);
    sprite2->setPosition(ccp(winSize.width/2 + driff, winSize.height/2));
    
    return true;
    
}