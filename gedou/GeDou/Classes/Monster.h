//
//  Monster.h
//  怪物
//
//  Created by zhihuanglai on 15/6/26.
//
//

#ifndef __GeDou__Monster__
#define __GeDou__Monster__

#include <iostream>
#include "cocos2d.h"
#include "HpProgress.h"

USING_NS_CC;

class Monster : public Node
{
public:
    Monster(void);
    ~Monster(void);
    
    /**
     * 根据怪物名字建立游戏内的怪物模型
     */
    void initMonsterSprite(const char *monsterName);
    
    void initMonsterSprite(const char *monsterName, const char *xue_back, const char *xue_fore);
    
    /**
     *  设置怪物的动画，可以是跑，攻击，死亡，受伤等
     *
     *  @param name_each     怪物图片中每一小张图片的公共名称部分
     *  @param num           图片数量
     *  @param run_direction 怪物朝向，false朝右
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
    
    bool monsterDirection;
    
    bool isAttack;
    
    CREATE_FUNC(Monster);
    
private:
    Sprite* m_monster_sprite;
    
    const char *monster_name;
    
    HpProgressView* monster_xue;
};

#endif /* defined(__GeDou__Monster__) */
