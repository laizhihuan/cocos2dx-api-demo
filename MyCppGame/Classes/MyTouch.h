//
//  MyTouch.h
//  MyCppGame
//
//  Created by zhihuanglai on 15/4/20.
//
//

#ifndef __MYTOUCH_H__
#define __MYTOUCH_H__

#include "cocos2d.h"
#include "MyCommonLayer.h"

USING_NS_CC;

class MyTouch : public MyCommonLayer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MyTouch);
    
    //touch事件监听
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
};

#endif
