//
//  MainScene.h
//  Chess
//
//  Created by zhihuanglai on 15/5/8.
//
//

#ifndef __Chess__MainScene__
#define __Chess__MainScene__

#include "cocos2d.h"
USING_NS_CC;

class MainScene : public Layer
{
public:
    CREATE_FUNC(MainScene);
    bool init();
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
    
    Sprite* _red;    //红方
    Sprite* _black;  //黑方
    
    bool _selected;  //选择了那一方,ture红方，false黑方
    
    void update(float delta);  //帧循环
    
};

#endif /* defined(__Chess__MainScene__) */
