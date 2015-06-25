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
    void initHeroSprite(char *heroName);
    
    /**
     *  设置英雄的动画，可以是跑，攻击，死亡，受伤等
     *
     *  @param name_plist    <#name_plist description#>
     *  @param name_png      <#name_png description#>
     *  @param name_each     英雄图片中每一小张图片的公共名称部分
     *  @param num           图片数量
     *  @param run_direction 英雄朝向，false朝右
     */
    void setAnimation(const char *namePlist,const char *namePng,const char *nameEach,
                      const unsigned int num,bool runDirection);
    
    Animation* getAnimation(const char *namePlist,const char *namePng,const char *nameEach,
                            const unsigned int num,bool runDirection);
    
    void runEnd();
    
    void stopAnimation();
    
    bool isRunning;
    
    bool heroDirection;
    
    CREATE_FUNC(Hero);

private:
    Sprite* mHeroSprite;
    char *heroName;
    
};

#endif /* defined(__GeDou__Hero__) */
