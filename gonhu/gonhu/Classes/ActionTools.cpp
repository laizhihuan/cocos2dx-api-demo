//
//  ActionTools.cpp
//  gonhu
//
//  Created by zhihuanglai on 15/6/11.
//
//

#include "ActionTools.h"

Animate* animationWithFrameName(const char *frameName,float delay)
{
    SpriteFrame* frame = NULL;
    Animation* animation = Animation::create();
    int index = 1;
    do
    {
        String* name = String::createWithFormat("%s%d",frameName,index++);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());
        if (frame == NULL) {
            break;
        }
        animation->addSpriteFrame(frame);
    } while(true);
    
    animation->setDelayPerUnit(delay);
    animation->setRestoreOriginalFrame(true);
    Animate* animate = Animate::create(animation);
    
    return animate;
}

Animate* animationWithFrameAndNum(const char *frameName,int frameCount, float delay)
{
    SpriteFrame* frame = NULL;
    Animation* animation = Animation::create();
    
    for (int index=1; index<=frameCount; index++) {
        String* name = String::createWithFormat("%s%d",frameName,index++);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());
        if (frame == NULL) {
            continue;
        }
        animation->addSpriteFrame(frame);
    }
    
    animation->setDelayPerUnit(delay);
    animation->setRestoreOriginalFrame(true);
    Animate* animate = Animate::create(animation);
    
    return animate;
}