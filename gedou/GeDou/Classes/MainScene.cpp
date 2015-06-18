//
//  MainScene.cpp
//  GeDou
//
//  Created by zhihuanglai on 15/6/16.
//
//

#include "MainScene.h"
#include "GameScene.h"

bool MainScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto *node = CSLoader::createNode("main.csb");
    this->addChild(node);
    
    Button *startBtn = static_cast<Button*>(node->getChildByName("start_game"));
    startBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::touchEvent, this));
    
    return true;
}

Scene* MainScene::createScene()
{
    Scene *scene = Scene::create();
    MainScene *layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

void MainScene::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            log("Button down");
            break;
        case Widget::TouchEventType::MOVED:
            log("Button moved");
            break;
        case Widget::TouchEventType::ENDED:
            log("Button ended");
            Director::getInstance()->replaceScene(GameScene::createScene());
            break;
        case Widget::TouchEventType::CANCELED:
            log("Button canceled");
            break;
        default:
            break;
    }
}