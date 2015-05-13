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
#include "Stone.h"
USING_NS_CC;

class SceneGame : public Layer
{
public:
    /**
     *  创建游戏场景
     *
     *  @param isRed true表示选择红棋，false表示选择黑棋
     *
     *  @return 游戏场景
     */
    static Scene* createScene(bool isRed);
    
    static SceneGame* create(bool isRed);
    
    bool init(bool red);
    
    Stone* _stone[32];
    
    Point _plateOffset;
};

#endif /* defined(__Chess__SceneGame__) */
