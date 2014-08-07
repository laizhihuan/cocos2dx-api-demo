#include "HelloWorldScene.h"

#include "CardSprite.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibelSize = Director::getInstance()->getVisibleSize();
    
    auto layerColorBG = LayerColor::create(Color4B(180,170,160,255));
    this->addChild(layerColorBG);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    createCardSprite(visibelSize);
    return true;
}

void HelloWorld::createCardSprite(cocos2d::Size size) {
    //UI中每个单元格的宽高
    int cardSize = (size.width-28)/4;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            CardSprite *card = CardSprite::createCardSprite(2, cardSize, cardSize, cardSize*i+20, cardSize*j+20+size.height/6);
            addChild(card);
        }
    }
    
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {
    Point point = touch->getLocation();
    firstX = point.x;
    firstY = point.y;
    
    return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event) {
    Point point = touch->getLocation();
    
    endX = firstX - point.x;
    endY = firstY - point.y;
    
    if(abs(endX) > abs(endY)) {
        if((endX + 5) > 0) {
            doLeft();
        } else {
            doRigth();
        }
    } else {
        if((endY + 5) > 0) {
          doDown();
        } else {
          doUp();
        }
    }
    
}

bool HelloWorld::doLeft() {
    log("doLeft");
    return true;
}

bool HelloWorld::doRigth() {
    log("doRigth");
    return true;
}

bool HelloWorld::doUp() {
    log("doUp");
    return true;
}

bool HelloWorld::doDown() {
    log("doDown");
    return true;
}

