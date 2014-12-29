#include "HelloWorldScene.h"

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//    
//	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));
//
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//    
//    auto label = LabelTTF::create("Hello World", "Arial", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    buildUI();
    addListener();
    return true;
}

void HelloWorld::buildUI() {
    aTF = TextFieldTTF::textFieldWithPlaceHolder("Value", "Courier", 16);
    aTF->setPosition(100,300);
    addChild(aTF);
    
    addLabel = Label::create();
    addLabel->setString("+");
    addLabel->setPosition(aTF->getPositionX()+50,aTF->getPositionY());
    addChild(addLabel);
    
    bTF = TextFieldTTF::textFieldWithPlaceHolder("Value", "Courier", 16);
    bTF->setPosition(addLabel->getPositionX()+50, addLabel->getPositionY());
    addChild(bTF);
    
    auto equalLable = Label::create();
    equalLable->setString("=");
    equalLable->setPosition(bTF->getPositionX()+50,bTF->getPositionY());
    addChild(equalLable);
    
    resultLabel = Label::create();
    resultLabel->setPosition(resultLabel->getPositionX()+50, resultLabel->getPositionY());
    addChild(resultLabel);
    
    addBtn = Label::create();
    addBtn->setString("Add");
    addBtn->setSystemFontSize(16);
    addChild(addBtn);
    addBtn->setPosition(aTF->getPositionX(),aTF->getPositionY() - 50);
}

void HelloWorld::addListener() {
    auto director = Director::getInstance();
    
    auto handler = [=] (Touch * t, Event * e) {
        auto taget = e->getCurrentTarget();
        
        if(taget->getBoundingBox().containsPoint(t->getLocation())) {
            if(taget == aTF) {
                aTF->attachWithIME();
            } else if (taget == bTF) {
                bTF->attachWithIME();
            } else if (taget == addBtn) {
                log("click");
            }
        }
        log("click-------");
        
        return false;
    };
    
    auto addListenerToTarget = [director,handler](Node* target) {
        auto l = EventListenerTouchOneByOne::create();
        l->onTouchBegan = handler;
        director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(l, target);
    };
    
    addListenerToTarget(addBtn);
    addListenerToTarget(aTF);
    addListenerToTarget(bTF);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
