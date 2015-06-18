//
//  Hero.cpp
//  GeDou
//
//  Created by zhihuanglai on 15/6/18.
//
//

#include "Hero.h"

Hero::Hero(void)
{
    isRunning = false;
    heroDirection = false;
    heroName = NULL;
}

Hero::~Hero()
{
}

void Hero::initHeroSprite(char *heroName)
{
    this->heroName = heroName;
    this->mHeroSprite = Sprite::create(heroName);
    this->addChild(mHeroSprite);
}

void Hero::setAnimation(const char *namePlist, const char *namePng, const char *nameEach, const unsigned int num, bool runDirection)
{
    if (heroDirection != runDirection) {
        heroDirection = runDirection;
        mHeroSprite->setFlippedX(runDirection);
    }
    
    if (isRunning) {
        return;
    }
    
    SpriteFrameCache *mFrameCache = SpriteFrameCache::getInstance();
    mFrameCache->addSpriteFramesWithFile(namePlist,namePng);
    
    //用一个列表保存所有的SpriteFrameCache
    Vector<SpriteFrame*> frameArray(num);
    
    unsigned int i;
    for (i=2; i<=num; i++) {
        SpriteFrame* frame = mFrameCache->getSpriteFrameByName(String::createWithFormat("%s%d.png",nameEach,i)->getCString());
        frameArray.insert(i, frame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(frameArray);
    
    if (heroDirection != runDirection) {
        heroDirection = runDirection;
    }
    
    animation->setLoops(-1); //表示无限循环播放
    animation->setDelayPerUnit(0.1f); //每俩张图片的时间间隔，图片数目越小，间隔最小就越小
    
    Animate* act = Animate::create(animation);
    
    mHeroSprite->runAction(act);
    isRunning = true;
}

void Hero::stopAnimation()
{
    if (!isRunning) {
        return;
    }
    
    mHeroSprite->stopAllActions(); //停止当前精灵所有的动画
    
    this->removeChild(mHeroSprite,true); //把原来的精灵删掉
    
    mHeroSprite=Sprite::create(heroName); //恢复精灵原来的贴图样子
    this->addChild(mHeroSprite);
    isRunning = false;
}







