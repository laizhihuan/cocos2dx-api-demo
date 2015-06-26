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
    isAttack = false;
}

Hero::~Hero()
{
}

void Hero::initHeroSprite(const char *heroName)
{
    this->heroName = heroName;
    this->mHeroSprite = Sprite::create(heroName);
    this->addChild(mHeroSprite);
}

void Hero::setAnimation(const char *nameEach, const unsigned int num, bool runDirection)
{
    if (heroDirection != runDirection) {
        heroDirection = runDirection;
        mHeroSprite->setFlippedX(runDirection);
    }
    
    if (isRunning) {
        return;
    }
    
    auto arimation = getAnimation(nameEach, num, runDirection);
    auto action = Animate::create(arimation);
    auto ccback = CallFunc::create(CC_CALLBACK_0(Hero::runEnd, this));
    auto act = Sequence::create(action,ccback,NULL);
    mHeroSprite->runAction(act);
    
    isRunning = true;
}

void Hero::runEnd()
{
    isRunning = false;
}

Animation* Hero::getAnimation(const char *nameEach, const unsigned int num, bool runDirection)
{
    auto animation = Animation::create();
    
    for (int i=1; i < num; i++) {
        animation->addSpriteFrameWithFile(String::createWithFormat("%s%d.png",nameEach,i)->getCString());
    }
    
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(1);
    return animation;
    
}

void Hero::attackAnimation(const char *name_each,const unsigned int num, bool runDirect)
{
    if (isAttack) {
        return;
    }
    
    auto ani = getAnimation(name_each, num, runDirect);
    auto action = Animate::create(ani);
    
    auto ccBack = CallFunc::create(CC_CALLBACK_0(Hero::attackEnd, this));
    auto act = Sequence::create(action,ccBack, NULL);
    mHeroSprite->runAction(act);
    isAttack = true;

}

void Hero::attackEnd()
{
    //恢复精灵原来的init贴图
    this->removeChild(mHeroSprite,true);
    mHeroSprite=Sprite::create(heroName);
    this->addChild(mHeroSprite);
    
    isAttack = false;
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

bool Hero::judgePostion(Size visibleSize)
{
    if (this->getPositionX() != visibleSize.width/2) {
        return false;
    } else {
        return true;
    }
}







