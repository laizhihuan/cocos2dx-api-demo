//
//  MainScene.cpp
//  GeDou
//
//  Created by zhihuanglai on 15/6/16.
//
//

#include "MainScene.h"

bool MainScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto *node = CSLoader::createNode("main.csb");
    this->addChild(node);
    return true;
}

Scene* MainScene::createScene()
{
    Scene *scene = Scene::create();
    MainScene *layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}