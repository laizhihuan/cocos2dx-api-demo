//
//  MainScene.cpp
//  Chess
//
//  Created by zhihuanglai on 15/5/8.
//
//

#include "MainScene.h"
#include "Common.h"
#include "SceneGame.h"

bool MainScene::init()
{
    Layer::init();
    
    int driff = 100;
    
    // 创建红棋
    Sprite* sprite1 = Sprite::create("bkg2.png");
	addChild(sprite1);
	sprite1->setPosition(Vec2(winSize.width/2 - driff, winSize.height / 2));
    
    // 创建黑棋
    Sprite* sprite2 = Sprite::create("bkg1.png");
    addChild(sprite2);
    sprite2->setPosition(Vec2(winSize.width/2 + driff, winSize.height/2));
    
    // 添加触摸，使用单点触控功能
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    _red   = sprite1;
    _black = sprite2;
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
    
    Point touchPoint = touch->getLocation();
    
    if(_red->boundingBox().containsPoint(touchPoint))
    {
        //选中红棋
        _selected = true;
    } else if(_black->boundingBox().containsPoint(touchPoint))
    {
        //选中黑棋
        _selected = false;
    } else {
        //什么都没有选中
        return;
    }
    
    // 点中棋子的效果处理
    int dt = 2;
    
    MoveTo* moveBlack = MoveTo::create(dt, Vec2(winSize.width/2, winSize.height/2));
    MoveTo* moveRed   = MoveTo::create(dt, Vec2(winSize.width/2, winSize.height/2));
    
    _red->runAction(moveRed);
    _black->runAction(moveBlack);
    
    //启动帧循环定时器，进行碰撞检测
    scheduleUpdate();
}

void MainScene::onTouchCancelled(Touch *touch, Event *unused_event)
{
    
}

void MainScene::update(float delta)
{
    //当俩个棋子碰撞时，启动游戏
    if (_black->getPositionX() - _red->getPositionX() <= _red->getContentSize().width) {
        log("start game");
        Director::getInstance()->replaceScene(SceneGame::createScene(_selected));
    }
}

