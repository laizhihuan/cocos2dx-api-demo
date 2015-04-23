//
//  MyCood.h
//  MyCppGame
//
//  Created by zhihuanglai on 15/4/23.
//
//


#ifndef __MYDRAGNODE_
#define __MYDRAGNODE_

#include "cocos2d.h"

USING_NS_CC;

class MyCood : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MyCood);    
};

#endif