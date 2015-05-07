//
//  MyActions.h
//  MyCppGame
//
//  Created by zhihuanglai on 15/5/7.
//
//

#ifndef __MyCppGame__MyActions__
#define __MyCppGame__MyActions__

#include "MyCommonLayer.h"

class ActionsDisplay : public MyCommonLayer
{
public:
    static Scene* scene(const char* actionName)
    {
        Scene* scene = Scene::create();
        ActionsDisplay* layer = ActionsDisplay::create(actionName);
        scene->addChild(scene);
        return scene;
    }
    
    static ActionsDisplay* create(const char* actionName)
    {
        ActionsDisplay* display = new ActionsDisplay();
        display->init(actionName);
        display->autorelease();
        return display;
    }
    
    bool init(const char* actionName)
    {
        MyCommonLayer::init();
        
        Action* action = NULL;
        
        CCSprite* sprite = CCSprite::create("CloseNormal.png");
		addChild(sprite);
		sprite->setPosition(ccp(240, 160));
        
        if(actionName == "CCMoveBy")
        {
            action = MoveBy::create(4,ccp(100,100));
        }
        
        if(action)
        {
            sprite->runAction(action);
        }
        return true;
    }
};

class MyActions : public MyCommonLayer
{
public:
	static CCScene* scene();
	CREATE_FUNC(MyActions);
	bool init();
    
	void menuCallback(CCObject* sender);
    
	bool onTouchBegan(CCTouch* t, CCEvent* e)
	{
		return true;
	}
    
	void onTouchMoved(CCTouch* t, CCEvent*e)
	{
		setPositionY(getPositionY() + t->getDelta().y);
	}
};


#endif /* defined(__MyCppGame__MyActions__) */
