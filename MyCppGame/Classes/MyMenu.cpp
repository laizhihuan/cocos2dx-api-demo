//
//  MyMenu.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 15/5/3.
//
//

#include "MyMenu.h"
#include "HelloWorldScene.h"
#include "SceneSecond.h"
#include "MyTouch.h"
#include "MyDragNode.h"
#include "ErasableLayer.h"

USING_NS_CC;

/**
 *  创建一个菜单数组
 */
static const char* _menuArr[] = {
    "HelloWorldScene.h",
    "SceneSecond.h",
    "MyTouch.h",
    "MyDragNode.h",
    "ErasableLayer.h"
};

//是cocos渲染树的根节点，是一个独立游戏逻辑模块的封装
Scene* MyMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MyMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MyMenu::init()
{
    //游戏的touch事件
    Layer::init();
    
    //根据数组动态的创建menu
    auto* myMenu = Menu::create();
    
    for (int i=0; i<sizeof(_menuArr)/sizeof(*_menuArr); ++i) {
        auto* item = MenuItemFont::create(_menuArr[i]);
        myMenu->addChild(item);
        item->setTarget(this, menu_selector(MyMenu::menuCallback));
        item->setTag(1000+i);
    }
    
    addChild(myMenu);
    
    myMenu->alignItemsVertically();
    
    return true;
}

void MyMenu::menuCallback(CCObject* sender) {
    log("click menucallback....");
    
    Node* node = (Node*)sender;
    int tag = node->getTag()-1000;
    
    Scene* playScene = NULL;
    switch (tag) {
        case 0:
            playScene = HelloWorld::createScene();
            break;
        case 1:
            playScene = SceneSecond::createScene();
            break;
        case 2:
            playScene = MyTouch::createScene();
            break;
        case 3:
            playScene = MyDragNode::createScene();
            break;
        case 4:
            playScene = SceneSecond::createScene();
            if (playScene) {
                //遮照层
                auto maskLayer = LayerColor::create(Color4B(0,0,255,200));
                maskLayer->setContentSize(playScene->getContentSize());
                
                //创建可擦除的layer
                auto layer= ErasableLayer::create(maskLayer, "eraser.png");
                auto visibleSize = playScene->getContentSize();
                layer->setPosition(Vec2(visibleSize.width/4,visibleSize.height/4));
                playScene->addChild(layer);
            }
            break;
        default:
            break;
    }
    
    if (playScene) {
        Director::sharedDirector()->replaceScene(playScene);
    }
}

