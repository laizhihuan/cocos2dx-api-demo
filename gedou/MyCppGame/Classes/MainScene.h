//
//  MainScene.h
//  MyCppGame
//
//  Created by zhihuanglai on 15/6/16.
//
//

#ifndef __MyCppGame__MainScene__
#define __MyCppGame__MainScene__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocostudio;

class MainScene : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(MainScene);
    
    //void touchStartBtn(Object* obj, ui::TouchEventType type);
};


#endif /* defined(__MyCppGame__MainScene__) */
