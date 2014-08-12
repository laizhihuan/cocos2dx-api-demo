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
    
    startGame();
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [this](Touch *t,Event *event) {
        log("onTouch");
        
        auto bs = Block::getBlocks();
        Block *b;
        
        for (auto it = bs->begin(); it!=bs->end(); it++) {
            b = *it;
            
            if (b->getLineIndex() == 1 && b->getBoundingBox().containsPoint(t->getLocation())) {
                
                if (b->getColor() == Color3B::BLACK) {
                    b->setColor(Color3B::GRAY);
                    this->moveDown();
                } else {
                    MessageBox("GameOver", "fail");
                }
                
            }
            
        }
        
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void HelloWorld::moveDown() {
    log("moveDown");
    
    addLine(4);
    
    auto bs = Block::getBlocks();
    for (auto it=bs->begin(); it!=bs->end(); it++) {
        (*it)->moveDown();
    }
}

void HelloWorld::startGame() {
    createStartLine();
    
    addLine(1);
    addLine(2);
    addLine(3);
}

void HelloWorld::addLine(int lineIndex) {
    
    Block *b;
    int blockIndex = rand()%4;
    
    for (int i=0; i<4; i++) {
        
        b = Block::createWithArgs(blockIndex == i ? Color3B::BLACK : Color3B::WHITE,
                       Size((visibleSize.width/4)-1,(visibleSize.height/4)-1),
                       "",20,Color4B::BLACK);
        
        b->setPosition(Vec2(i*visibleSize.width/4, lineIndex*visibleSize.height/4));
        
        b->setLineIndex(lineIndex);
        
        addChild(b);
    }
    
}

void HelloWorld::createStartLine() {
    auto b = Block::createWithArgs(Color3B::YELLOW,
                                   Size(visibleSize.width,visibleSize.height/4), "", 20, Color4B::BLACK);
    b->setLineIndex(0);
    addChild(b);
}

void HelloWorld::createEndLine() {
    auto b = Block::createWithArgs(Color3B::GREEN, visibleSize, "Game over", 36, Color4B::BLACK);
    b->setLineIndex(4);
    addChild(b);
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
