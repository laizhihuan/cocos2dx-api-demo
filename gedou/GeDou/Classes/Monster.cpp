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

void Monster::followRun(cocos2d::Node *m_hero, cocos2d::Node *m_map)
{
    //得到两点x的距离
    float x = m_hero->getPositionX() - (this->getPositionX() + m_map->getPositionX());
    //得到两点y的距离
    float y = m_hero->getPositionY() - (this->getPositionY() + m_map->getPositionY());
    
    //先计算怪物和英雄的距离
    dis = sqrt(pow(x, 2)+pow(y, 2));
    
    if (dis >= 300) {
        return;
    }
    
    if (dis <= 100) {
        this -> stopAnimation();
        judegeAttack();
        return;
    }
    
    //判断怪物横坐标和英雄的距离
    if (x < -100) {
        monsterDirection = true;
        //设置方向
        m_monster_sprite -> setFlippedX(monsterDirection);
        
        if (isAttack) {
            return;
        }
        
        //设置怪物向英雄移动
        this->setPosition(this->getPositionX()-1, this->getPositionY());
        //播放动画
        this->setAnimation("monster_run", 6, monsterDirection);
    }
    else if (x > 100)
    {
        monsterDirection = false;
        m_monster_sprite->setFlippedX(monsterDirection); //设置方向
        if (isAttack) {
            return;
        }
        this->setPosition(this->getPositionX()+1,this->getPositionY());
        this->setAnimation("monster_run", 6, monsterDirection);
    }
    else if (x <= 100 || x > -100)
    {
        if (m_hero->getPositionY() > this->getPositionY()) {
            m_monster_sprite->setFlippedX(monsterDirection);
            if (isAttack) {
                return;
            }
            this->setPosition(this->getPositionX(), this->getPositionY()+1);
            this->setAnimation("monster_run", 6, monsterDirection);
        }
        else if (m_hero->getPositionY() < this->getPositionY())
        {
            m_monster_sprite->setFlippedX(monsterDirection);
            if (isAttack) {
                return;
            }
            this->setPosition(this->getPositionX(), this->getPositionY()-1);
            this->setAnimation("monster_run", 6, monsterDirection);
        }
    }
}

void Monster::judegeAttack()
{
    int x = random(0,100);
    log("attack----->%d",x);
    if (x>50) {
        this->attackAnimation("monster_attack", 5, monsterDirection);
    }
}

void Monster::monsterSeeRun()
{
    if (dis < 300) {
        return;
    }
    
    this->setAnimation("monster_run", 6, monsterDirection);
    
    MoveBy *moveBy1;
    
    if (monsterDirection == true) {
        moveBy1 = MoveBy::create(1, Vec2(-70, 0));
    } else {
        moveBy1 = MoveBy::create(1, Vec2(70,0));
    }
    
    auto callFunc = CallFunc::create(CC_CALLBACK_0(Monster::stopAnimation, this));
    //创建连续动作
    auto xunluo = Sequence::create(moveBy1, callFunc, NULL);
    this->runAction(xunluo);
}

void Monster::startListen(cocos2d::Node *m_hero, cocos2d::Node *m_map)
{
    my_hero = m_hero;
    my_map = m_map;
    this->schedule(schedule_selector(Monster::updateMonster), 3.0f);
    this->scheduleUpdate();
}

void Monster::updateMonster(float delta)
{
    //得到两点x的距离,当hero移动的屏幕一般的时候，hero就只是做移动的动作，而真正移动的是map,如果比较hero和monster的距离，是出错的
    float x = my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
    //得到两点y的距离
    float y = my_hero->getPositionY() - (this->getPositionY() + my_map->getPositionY());
    
    //先计算怪物和英雄的距离
    dis = sqrt(pow(x, 2)+pow(y, 2));
    
    if (dis >= 300) {
        if (!isRunning) {
            monsterSeeRun();
        }
    }
}

void Monster::update(float delta)
{
    if (dis<300) {
        followRun(my_hero, my_map);
    }
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