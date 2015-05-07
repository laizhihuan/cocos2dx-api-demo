//
//  MyMenu.h
//  MyCppGame
//
//  Created by zhihuanglai on 15/5/3.
//
//

#ifndef __MYMenu_
#define __MYMenu_

#include "cocos2d.h"

USING_NS_CC;

class MyMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MyMenu);
    
    Menu* _menu;
    
    void menuCallback(CCObject* sender);
    
    bool onTouchBegan(CCTouch*, CCEvent*){ return true; }
    
	void onTouchMoved(CCTouch* t, CCEvent*)
	{
		/*
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCRect rcWin = CCRect(0, 0, winSize.width, winSize.height);
        
		Node* first = (Node*)_menu->getChildren()->objectAtIndex(0);
		Node* last = (Node*)_menu->getChildren()->lastObject();
		CCPoint ptFirstInNode = first->getPosition();
		CCPoint ptFirstInWorld = _menu->convertToWorldSpace(ptFirstInNode);
		
		if (rcWin.containsPoint(ptFirstInWorld) && t->getDelta().y < 0)
			return;
        
		CCPoint ptLastInNode = last->getPosition();
		CCPoint ptLastInWorld = _menu->convertToWorldSpace(ptLastInNode);
		if (rcWin.containsPoint(ptLastInWorld) && t->getDelta().y > 0)
			return;
        */
		setPositionY(this->getPositionY() + t->getDelta().y);
	}
};

#endif