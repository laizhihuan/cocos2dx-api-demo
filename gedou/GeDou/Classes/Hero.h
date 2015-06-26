//
//  Hero.h
//  GeDou
//
//  Created by zhihuanglai on 15/6/18.
//
//

#ifndef __GeDou__Hero__
#define __GeDou__Hero__

#include "cocos2d.h"

USING_NS_CC;

class Hero : public Node
{
public:
    Hero(void);
    ~Hero(void);
    
    /**
     根据英雄名字建立游戏内的英雄模型
     
     :returns: <#return value description#>
     */
    void initHeroSprite(const char *heroName);
    
    /**
     *  设置英雄的动画，可以是跑，攻击，死亡，受伤等
     *
     *  @param name_each     英雄图片中每一小张图片的公共名称部分
     *  @param num           图片数量
     *  @param run_direction 英雄朝向，false朝右
     */
    void setAnimation(const char *nameEach,const unsigned int num,bool runDirection);
    
    
    Animation* getAnimation(const char *nameEach,const unsigned int num,bool runDirection);
    
    /**
     *  攻击动画
     */
    void attackAnimation(const char *name_each,const unsigned int num, bool runDirect);
    
    /**
     *  攻击动画结束
     */
    void attackEnd();
    
    bool judgePostion(Size visibleSize);
    
    void runEnd();
    
    void stopAnimation();
    
    bool isRunning;
    
    bool heroDirection;
    
    bool isAttack;
    
    CREATE_FUNC(Hero);

private:
    Sprite* mHeroSprite;
    const char *heroName;
    
};

#endif /* defined(__GeDou__Hero__) */
