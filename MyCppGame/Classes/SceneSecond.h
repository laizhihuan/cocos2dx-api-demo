//
//  SceneSecond.h
//  MyCppGame
//
//  Created by zhihuanglai on 15/4/17.
//
//
#ifndef __SCENESECOND_H__
#define __SCENESECOND_H__

#include "cocos2d.h"
#include "MyCommonLayer.h"

USING_NS_CC;

class SceneSecond : public MyCommonLayer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(SceneSecond);
};

#endif