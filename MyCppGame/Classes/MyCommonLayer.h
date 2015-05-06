//
//  MyCommonLayer.cpp
//  自定义公共的layer，带有return的按钮
//  MyCppGame
//
//  Created by zhihuanglai on 15/5/6.
//
//

#ifndef __MyCppGame__MyCommonLayer__
#define __MyCppGame__MyCommonLayer__

#include "cocos2d.h"
USING_NS_CC;

class MyCommonLayer : public Layer
{
public:
    CREATE_FUNC(MyCommonLayer);
    bool init();
    
    void menuCallback(Object* sender);
};


#endif /* defined(__MyCppGame__MyCommonLayer__) */
