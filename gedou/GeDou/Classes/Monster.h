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
    
    /**
     *  可视范围内，怪物跟随英雄运动
     *
     *  @param m_hero m_hero description
     *  @param m_map  <#m_map description#>
     */
    void followRun(Node* m_hero, Node* m_map);
    /**
     *  判断是否攻击
     */
    void judegeAttack();
    /**
     *  怪物巡逻路线
     */
    void monsterSeeRun();
    /**
     *  启动英雄监听器
     *
     *  @param m_hero <#m_hero description#>
     *  @param m_map  <#m_map description#>
     */
    void startListen(Node* m_hero, Node* m_map);
    /**
     *  每隔3秒检测一下，计算英雄与怪物的距离
     *
     *  @param delta <#delta description#>
     */
    void updateMonster(float delta);
    /**
     *  更新函数，如果英雄在可视范围内，不断触发
     *
     *  @param delta <#delta description#>
     */
    void update(float delta);
    
private:
    Sprite* m_monster_sprite;
    
    const char *monster_name;
    
    HpProgressView* monster_xue;
    
    /**
     *  当前英雄
     */
    Node* my_hero;
    /**
     *  当前地图
     */
    Node* my_map;
    /**
     *  当前怪物和英雄的距离
     */
    float dis;
};

#endif /* defined(__GeDou__Monster__) */
