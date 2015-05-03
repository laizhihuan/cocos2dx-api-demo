//
//  MyMenu.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 15/5/3.
//
//

#include "MyMenu.h"

USING_NS_CC;

//创建一个菜单数组
static const char* _tn[] = {
    "HelloWorldScene.h",
    "SceneSecond.h",
    "MyTouch.h",
    "MyDragNode.h"
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
    
    for (int i=0; i<sizeof(_tn)/sizeof(*_tn); ++i) {
        auto* item = MenuItemFont::create(_tn[i]);
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
}

