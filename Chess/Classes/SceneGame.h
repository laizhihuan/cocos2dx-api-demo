//
//  SceneGame.h
//  Chess
//
//  Created by zhihuanglai on 15/5/12.
//
//

#ifndef __Chess__SceneGame__
#define __Chess__SceneGame__

#include "Common.h"
#include "cocos2d.h"
USING_NS_CC;

class SceneGame : public Layer
{
public:
    static Scene* createScene(bool isRed);
    static SceneGame* create(bool isRed);
    bool init(bool red);
    
    Point _plateOffset;
};

#endif /* defined(__Chess__SceneGame__) */
