#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    
    bool doLeft();
    bool doRigth();
    bool doUp();
    bool doDown();

    void createRandNumber();
    void doCheckGameOver();
    
    void addScore(int num);
    
private:
    int firstX,firstY,endX,endY;
    
    void createCardSprite(Size size);
    
    CardSprite *cardArr[4][4];
    
    int score;
    
    Label *labelScoreTitle;
    
    Label *labelScore;
};

#endif // __HELLOWORLD_SCENE_H__
