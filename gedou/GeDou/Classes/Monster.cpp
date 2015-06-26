//
//  Monster.cpp
//  GeDou
//
//  Created by zhihuanglai on 15/6/26.
//
//

#include "Monster.h"


Monster::Monster(void)
{
    isRunning = false;
    monsterDirection = true;
    monster_name = NULL;
    isAttack = false;
}

Monster::~Monster()
{
}

void Monster::initMonsterSprite(const char *monsterName)
{
    this->monster_name = monsterName;
    this->m_monster_sprite = Sprite::create(monsterName);
    this->addChild(m_monster_sprite);
}

void Monster::initMonsterSprite(const char *monsterName, const char *xue_back, const char *xue_fore)
{
    initMonsterSprite(monsterName);
    monster_xue = new HpProgressView();
    //设置血条到怪物的头顶上
    monster_xue->setPosition(Vec2(m_monster_sprite->getPositionX(), m_monster_sprite->getPositionY()+50));
    monster_xue->setBackgroundTexture(xue_back);
    monster_xue->setForegroundTexture(xue_fore);
    monster_xue->setTotalProgress(300.0f);
    monster_xue->setCurrentProgress(300.0f);
    this->addChild(monster_xue);
}

void Monster::setAnimation(const char *nameEach, const unsigned int num, bool runDirection)
{
    if (monsterDirection != runDirection) {
        monsterDirection = runDirection;
        m_monster_sprite->setFlippedX(runDirection);
    }
    
    if (isRunning) {
        return;
    }
    
    auto arimation = getAnimation(nameEach, num, runDirection);
    auto action = Animate::create(arimation);
    auto ccback = CallFunc::create(CC_CALLBACK_0(Monster::runEnd, this));
    auto act = Sequence::create(action,ccback,NULL);
    m_monster_sprite->runAction(act);
    
    isRunning = true;
}

void Monster::runEnd()
{
    isRunning = false;
}

Animation* Monster::getAnimation(const char *nameEach, const unsigned int num, bool runDirection)
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

void Monster::attackAnimation(const char *name_each,const unsigned int num, bool runDirect)
{
    if (isAttack) {
        return;
    }
    
    auto ani = getAnimation(name_each, num, runDirect);
    auto action = Animate::create(ani);
    
    auto ccBack = CallFunc::create(CC_CALLBACK_0(Monster::attackEnd, this));
    auto act = Sequence::create(action,ccBack, NULL);
    m_monster_sprite->runAction(act);
    isAttack = true;
    
}

void Monster::attackEnd()
{
    //恢复精灵原来的init贴图
    this->removeChild(m_monster_sprite,true);
    m_monster_sprite=Sprite::create(monster_name);
    this->addChild(m_monster_sprite);
    
    isAttack = false;
}

void Monster::stopAnimation()
{
    if (!isRunning) {
        return;
    }
    
    m_monster_sprite->stopAllActions(); //停止当前精灵所有的动画
    
    this->removeChild(m_monster_sprite,true); //把原来的精灵删掉
    
    m_monster_sprite=Sprite::create(monster_name); //恢复精灵原来的贴图样子
    this->addChild(m_monster_sprite);
    
    isRunning = false;
}

bool Monster::judgePostion(Size visibleSize)
{
    if (this->getPositionX() != visibleSize.width/2) {
        return false;
    } else {
        return true;
    }
}