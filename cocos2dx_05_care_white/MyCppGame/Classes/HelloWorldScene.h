#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int linesCount;
    bool showEnd;
    Label *timerLabel;
    Node *gameLayer;
    bool timerRunning;
    long startTime;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void createStartLine();
    
    void createEndLine();
    
    void addLine(int lineIndex);
    
    void startGame();
    
    void moveDown();
    
    void startTimer();
    void stopTimer();
    virtual void update(float dt);
};

#endif // __HELLOWORLD_SCENE_H__