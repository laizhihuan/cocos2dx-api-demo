//
//  MyDragNode.h
//  MyCppGame
//
//  Created by zhihuanglai on 15/4/21.
//
//

#ifndef __MYDRAGNODE_
#define __MYDRAGNODE_

#include "cocos2d.h"
#include "MyCommonLayer.h"

USING_NS_CC;

class MyDragNode : public MyCommonLayer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MyDragNode);
    
    Sprite* _sprite;
    
    //touch事件监听
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
};

#endif
