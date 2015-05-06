//
//  MyCood.h
//  MyCppGame
//
//  Created by zhihuanglai on 15/4/23.
//
//


#ifndef __MYCood_
#define __MYCood_

#include "cocos2d.h"
#include "MyCommonLayer.h"

USING_NS_CC;

class MyCood : public MyCommonLayer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MyCood);    
};

#endif