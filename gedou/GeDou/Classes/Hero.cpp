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
    
    auto arimation = getAnimation(namePlist, namePng, nameEach, num, runDirection);
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

Animation* Hero::getAnimation(const char *namePlist, const char *namePng, const char *nameEach, const unsigned int num, bool runDirection)
{
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(namePlist, namePng);
    
    mHeroSprite->setTexture(String::createWithFormat("%s1.png",nameEach)->getCString());
    
    auto spriteBatch = SpriteBatchNode::create(namePng);
    addChild(spriteBatch);
    
    Vector<SpriteFrame*> animFrames(num);
    
    for (int i=1; i < num; i++) {
        auto frame = cache->getSpriteFrameByName(String::createWithFormat("%s%d.png",nameEach,i)->getCString());
        animFrames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    return animation;
    
}

void Hero::attackAnimation(const char *name_plist, const char *name_png, const char *name_each,
                     const unsigned int num, bool runDirect)
{
    if (isAttack) {
        return;
    }
    
    auto ani = getAnimation(name_plist, name_png, name_each, num, runDirect);
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







