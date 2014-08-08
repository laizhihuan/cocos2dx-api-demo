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
    
    score = 0;
    
    Size visibelSize = Director::getInstance()->getVisibleSize();
    
    auto layerColorBG = LayerColor::create(Color4B(180,170,160,255));
    this->addChild(layerColorBG);
    
    labelScoreTitle = Label::createWithSystemFont("分数:", "HirakakuProN-W6", 60);
    labelScoreTitle->setPosition(Vec2(visibelSize.width/5,visibelSize.height - 130));
    addChild(labelScoreTitle);
    
    labelScore = Label::createWithSystemFont("0", "HirakakuProN-W6", 60);
    labelScore->setPosition(Vec2(visibelSize.width/2,visibelSize.height - 130));
    addChild(labelScore);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    createCardSprite(visibelSize);
    
    createRandNumber();
    createRandNumber();
    return true;
}

void HelloWorld::createCardSprite(cocos2d::Size size) {
    //UI中每个单元格的宽高
    int cardSize = (size.width-28)/4;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            CardSprite *card = CardSprite::createCardSprite(0, cardSize, cardSize, cardSize*i+20, cardSize*j+20+size.height/6);
            addChild(card);
            
            cardArr[i][j] = card;
        }
    }
}

void HelloWorld::createRandNumber() {
    int i = CCRANDOM_0_1()*4;
    int j = CCRANDOM_0_1()*4;
    if (cardArr[i][j]->getNumber() > 0) {
        createRandNumber();
    } else {
        cardArr[i][j]->setNumber(CCRANDOM_0_1()*10<1?4:2);
    }
}

void HelloWorld::doCheckGameOver() {
    bool isGameOver = true;
    
    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (cardArr[x][y]->getNumber() == 0 ||
                (x > 0 && (cardArr[x][y]->getNumber() == cardArr[x-1][y]->getNumber())) ||
                (x < 3 && (cardArr[x][y]->getNumber() == cardArr[x+1][y]->getNumber())) ||
                (y > 0 && (cardArr[x][y]->getNumber() == cardArr[x][y-1]->getNumber())) ||
                (y < 3 && (cardArr[x][y]->getNumber() == cardArr[x][y+1]->getNumber())) ) {
                isGameOver = false;
            }
        }
    }
    
    if (isGameOver) {
        MessageBox(__String::createWithFormat("你获得了这个分数：%d",score)->getCString(), "游戏结束");
        Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
    }
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {
    Point point = touch->getLocation();
    firstX = point.x;
    firstY = point.y;
    
    return true;
}

void HelloWorld::addScore(int num) {
    score += num;
    
    labelScore->setString(__String::createWithFormat("%d",score)->getCString());
    
    if(score>=0) {
        labelScore->setSystemFontSize(100);
    } else if(score >= 10) {
        labelScore->setSystemFontSize(80);
    } else if(score >= 100) {
        labelScore->setSystemFontSize(50);
    } else if(score >= 1000) {
        labelScore->setSystemFontSize(20);
    }
    
    
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event) {
    Point point = touch->getLocation();
    
    endX = firstX - point.x;
    endY = firstY - point.y;
    
    bool isMeger= false;
    
    if(abs(endX) > abs(endY)) {
        if((endX + 5) > 0) {
            isMeger = doLeft();
        } else {
            isMeger = doRigth();
        }
    } else {
        if((endY + 5) > 0) {
          isMeger = doDown();
        } else {
          isMeger = doUp();
        }
    }
    
    if(isMeger) {
        createRandNumber();
        doCheckGameOver();
    }
    
}

bool HelloWorld::doLeft() {
    log("doLeft");
    
    bool isDo = false;
    
    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            for (int l=x+1; l<4; l++) {
                if (cardArr[l][y]->getNumber() > 0) {
                    if (cardArr[x][y]->getNumber() <= 0) {
                        cardArr[x][y]->setNumber(cardArr[l][y]->getNumber());
                        cardArr[l][y]->setNumber(0);
                        
                        x--;
                        isDo = true;
                    } else if(cardArr[x][y]->getNumber() == cardArr[l][y]->getNumber()) {
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        cardArr[l][y]->setNumber(0);
                        
                        addScore(cardArr[x][y]->getNumber());
                        
                        isDo = true;
                    }
                    break;
                }
            }
        }
    }
    
    
    return isDo;
}

bool HelloWorld::doRigth() {
    log("doRigth");
    
    bool isDo = false;
    
    for (int y=0; y<4; y++) {
        for (int x=3; x>=0; x--) {
            for (int r=x-1; r>=0; r--) {
                if (cardArr[r][y]->getNumber() > 0) {
                    if (cardArr[x][y]->getNumber() <= 0) {
                        cardArr[x][y]->setNumber(cardArr[r][y]->getNumber());
                        cardArr[r][y]->setNumber(0);
                        
                        x++;
                        isDo = true;
                    } else if(cardArr[x][y]->getNumber() == cardArr[r][y]->getNumber()) {
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        cardArr[r][y]->setNumber(0);
                        
                        addScore(cardArr[x][y]->getNumber());
                        
                        isDo = true;
                    }
                    break;
                }
            }
        }
    }
    
    
    return isDo;

}

bool HelloWorld::doUp() {
    log("doUp");
    bool isDo = false;
    
    for (int x=0; x<4; x++) {
        for (int y=3; y>=0; y--) {
            for (int u=y-1; u>=0; u--) {
                if (cardArr[x][u]->getNumber() > 0) {
                    if (cardArr[x][y]->getNumber() <= 0) {
                        cardArr[x][y]->setNumber(cardArr[x][u]->getNumber());
                        cardArr[x][u]->setNumber(0);
                        
                        y++;
                        isDo = true;
                    } else if(cardArr[x][y]->getNumber() == cardArr[x][u]->getNumber()) {
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        cardArr[x][u]->setNumber(0);
                        
                        addScore(cardArr[x][y]->getNumber());
                        
                        isDo = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isDo;
}

bool HelloWorld::doDown() {
    log("doDown");
     bool isDo = false;
    
    for (int x=0; x<4; x++) {
        for (int y=0; y<4; y++) {
            for (int d=y+1; d<4; d++) {
                if (cardArr[x][d]->getNumber() > 0) {
                    if (cardArr[x][y]->getNumber() <= 0) {
                        cardArr[x][y]->setNumber(cardArr[x][d]->getNumber());
                        cardArr[x][d]->setNumber(0);
                        
                        y--;
                        isDo = true;
                    } else if(cardArr[x][y]->getNumber() == cardArr[x][d]->getNumber()) {
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        cardArr[x][d]->setNumber(0);
                        
                        addScore(cardArr[x][y]->getNumber());
                        
                        isDo = true;
                    }
                    break;
                }
            }
        }
    }
    
    
    return isDo;
}

