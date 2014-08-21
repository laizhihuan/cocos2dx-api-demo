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
    
    srand(time(NULL));
    
    gameLayer = Node::create();
    addChild(gameLayer);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    timerLabel = Label::create();
    timerLabel->setTextColor(Color4B::BLUE);
    timerLabel->setSystemFontSize(48);
    timerLabel->setPosition(visibleSize.width/2,visibleSize.height - 100);
    timerLabel->setString("0.000000");
    addChild(timerLabel);
    
    startGame();
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [this](Touch *t,Event *event) {
        log("onTouch");
        
        auto bs = Block::getBlocks();
        Block *b;
        
        for (auto it = bs->begin(); it!=bs->end(); it++) {
            b = *it;
            
            //只有当前块行数是1的时候才进行交互
            if (b->getLineIndex() == 1 && b->getBoundingBox().containsPoint(t->getLocation())) {
                
                if (b->getColor() == Color3B::BLACK) {
                    //点击黑块，将原色块进行修改，并将画面向下移动
                    b->setColor(Color3B::GRAY);
                    this->moveDown();
                    
                    if (!timerRunning) {
                        this->startTimer();
                    }
                } else if(b->getColor()== Color3B::GREEN) {
                    
                    this->moveDown();
                    
                    this->stopTimer();
                } else {
                    //点击白块游戏结束
                    MessageBox("GameOver", "fail");
                }
                
                break;
            }
        }
        
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

//所有的卡片都向下移动
void HelloWorld::moveDown() {
    log("moveDown");
    
    if (linesCount<10) {
        addLine(4);
    } else if(!showEnd)  {
        createEndLine();
        showEnd = true;
    }
    
    auto bs = Block::getBlocks();
    
    for (auto it=bs->begin(); it!=bs->end(); it++) {
        (*it)->moveDown();
    }
}

void HelloWorld::startGame() {
    showEnd = false;
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
    
    linesCount++;
    
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

void HelloWorld::update(float dt) {
    long offset = clock() - startTime;
    
    timerLabel->setString(StringUtils::format("%g",((double)offset)/1000000));
}

void HelloWorld::startTimer() {
    if (!timerRunning) {
        scheduleUpdate();
        startTime = clock();
        
        timerRunning = true;
    }
}

void HelloWorld::stopTimer() {
    if (timerRunning) {
        unscheduleUpdate();
        timerRunning = false;
    }
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
