//
//  ActionTools.h
//  gonhu
//
//  Created by zhihuanglai on 15/6/11.
//
//

#ifndef __gonhu__ActionTools__
#define __gonhu__ActionTools__

#include "cocos2d.h"
USING_NS_CC;

class ActionTools
{
public:
    static Animate* animationWithFrameName(const char *frameName, float delay);
    
    static Animate* animationWithFrameAndNum(const char *frameName,int frameCount, float delay);
};

#endif /* defined(__gonhu__ActionTools__) */
