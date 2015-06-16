//
//  MainScene.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 15/6/16.
//
//

#include "MainScene.h"

Scene* MainScene::createScene()
{
    Scene *scene = Scene::create();
    MainScene *layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
//    uiLayer* uiLayer = uiLayer::create();
    //Layer* layer = Layer::create();
    auto mainLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("main.ExportJson");
    //layer->addChild(mainLayout);
    this->addChild(mainLayout);
    
    return true;
}

