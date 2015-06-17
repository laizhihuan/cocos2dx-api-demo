//
//  MainScene.h
//  GeDou
//
//  Created by zhihuanglai on 15/6/16.
//
//

#ifndef __GeDou__MainScene__
#define __GeDou__MainScene__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class MainScene : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(MainScene);
};

#endif /* defined(__GeDou__MainScene__) */
