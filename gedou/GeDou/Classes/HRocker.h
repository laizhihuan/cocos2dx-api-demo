//
//  HRocker.h
//  摇杆的实现
//
//  Created by zhihuanglai on 15/6/18.
//
//

#ifndef __GeDou__HRocker__
#define __GeDou__HRocker__

#include "cocos2d.h"

USING_NS_CC;

/**
 用于标示摇杆与摇杆的背景
 */
typedef enum {
    tag_rocker,
    tag_rockerBG,
}tagForHRocker;

/**
 用于标示摇杆的方向
 */
typedef enum {
    rocker_stay,
    rocker_right,
    rocker_up,
    rocker_left,
    rocker_down,
}tagDirection;


class HRocker : public Layer
{
public:
    HRocker(void);
    ~HRocker(void);
    
    /**
     *  创建摇杆
     *
     *  @param rockerImageName   摇杆的图片名字
     *  @param rockerBgImageName 摇杆的背景图片名字
     *  @param position          摇杆的出生位置
     *
     *  @return 游戏中的摇杆
     */
    static HRocker* createHRocker(const char *rockerImageName, const char *rockerBgImageName, Point position);
    
    /**
     *  启动摇杆
     *
     *  @param isStopOther 是否停止摇杆的监听事件
     */
    void startRocker(bool isStopOther);
    
    /**
     *  停止摇杆
     */
    void stopRocker();
    /**
     *  当前人物行走方向，用来判断精灵的朝向，精灵朝右还是朝左
     */
    bool rockerRun;
    /**
     *  摇杆方向
     */
    int rockerDirection;
    
    CREATE_FUNC(HRocker);

private:
    /**
     自定义摇杆init函数
     
     :returns:
     */
    void initRocker(const char* rockerImageName, const char* rockerBGImageName, Point position);
    /**
     *  是否可以操作摇杆
     */
    bool isCanMove;
    /**
     *  获取当前摇杆浴用户触屏点的角度
     *
     *  @param pos1 <#pos1 description#>
     *  @param pos2 <#pos2 description#>
     *
     *  @return <#return value description#>
     */
    float getRad(Point pos1, Point pos2);
    /**
     *  摇杆背景图标
     */
    Point rockerBGPostion;
    /**
     *  摇杆半径
     */
    float rockerBGR;
    
    //触屏事件
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    virtual void update(float delta);
    
};

#endif /* defined(__GeDou__HRocker__) */
