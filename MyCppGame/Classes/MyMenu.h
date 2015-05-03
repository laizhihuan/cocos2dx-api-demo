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
    
    void menuCallback(CCObject* sender);
};

#endif