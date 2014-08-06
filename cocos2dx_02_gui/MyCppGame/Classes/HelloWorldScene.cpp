#include "HelloWorldScene.h"
#include "HiImageSence.h"
#include "HiTouchSence.h"
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
    
    log("hello world log...");
    

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //--------------却换场景------------------------
    Label *label = Label::create();
    label->setString("show the image sence");
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - 20));
    addChild(label);
    
    //添加监听器
    auto listener = EventListenerTouchOneByOne::create();
    
    //监听器的闭包函数
    listener->onTouchBegan = [label](Touch *t,Event *event) {
        if(label->getBoundingBox().containsPoint(t->getLocation())) {
            log("click show the image sence");
            //普通的切换场景的效果
            //Director::getInstance()->replaceScene(HiImageSence::createSence());
            
            //添加动画效果
            Director::getInstance()->replaceScene(TransitionJumpZoom::create(3, HiImageSence::createSence()));
        }
        return false;
    };
    
    //注册监听器
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);
    
    //--------------------用户交互事件-----------------------------------------
    auto *touchLabel = Label::create();
    touchLabel->setString("show the touch sence");
    touchLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height - 40));
    addChild(touchLabel);
    
    auto touchListener = EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = [touchLabel](Touch *t,Event *event) {
        if(touchLabel->getBoundingBox().containsPoint(t->getLocation())) {
            log("click show the touch sence");
            
            Director::getInstance()->replaceScene(HiTouchSence::createScene());
            //普通的切换场景的效果
            //Director::getInstance()->replaceScene(HiImageSence::createSence());
            
            //添加动画效果
            //Director::getInstance()->replaceScene(TransitionJumpZoom::create(3, HiImageSence::createSence()));
        }
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, touchLabel);
    
    
    return true;
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
