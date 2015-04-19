//
//  SceneSecond.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 15/4/17.
//
//

#include <SceneSecond.h>
USING_NS_CC;


//是cocos渲染树的根节点，是一个独立游戏逻辑模块的封装
Scene* SceneSecond::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneSecond::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneSecond::init()
{
    // add "HelloWorld" splash screen"，游戏的元素依靠精灵来
    auto sprite = Sprite::create("HelloWorld.png");
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite);
    
    return true;
}
