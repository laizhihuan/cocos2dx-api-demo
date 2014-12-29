//
//  HiImageSence.h
//  MyCppGame
//
//  Created by zhihuanglai on 14-8-5.
//
//

#ifndef __MyCppGame__HiImageSence__
#define __MyCppGame__HiImageSence__

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;

class HiImageSence:public Layer {

public:
    virtual bool init();
    
    static Scene* createSence();
    
    CREATE_FUNC(HiImageSence);
};


#endif /* defined(__MyCppGame__HiImageSence__) */
