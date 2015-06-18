//
//  GameScene.h
//  GeDou
//
//  Created by zhihuanglai on 15/6/18.
//
//

#ifndef __GeDou__GameScene__
#define __GeDou__GameScene__

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(GameScene);
    
    /**
     *  每帧更新时调用的事件
     *
     *  @param delta 每帧时间间隔
     */
    virtual void update(float delta);
};

#endif /* defined(__GeDou__GameScene__) */
