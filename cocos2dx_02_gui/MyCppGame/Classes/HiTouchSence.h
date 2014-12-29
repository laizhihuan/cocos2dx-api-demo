//
//  HiTouchSence.h
//  MyCppGame
//
//  Created by zhihuanglai on 14-8-6.
//
//

#ifndef __MyCppGame__HiTouchSence__
#define __MyCppGame__HiTouchSence__

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;

class HiTouchSence:public Layer {
public:
    virtual bool init();
    
    static Scene* createScene();
    
    CREATE_FUNC(HiTouchSence);
};

#endif /* defined(__MyCppGame__HiTouchSence__) */
