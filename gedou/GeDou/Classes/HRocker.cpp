//
//  HRocker.cpp
//  GeDou
//
//  Created by zhihuanglai on 15/6/18.
//
//

#include "HRocker.h"

const double PI = 3.1415;

HRocker::HRocker(void)
{
    rockerRun = false;
}

HRocker::~HRocker()
{
}

HRocker* HRocker::createHRocker(const char *rockerImageName, const char *rockerBgImageName, Point position)
{
    HRocker *layer = HRocker::create();
    if (layer) {
        layer->initRocker(rockerImageName, rockerBgImageName, position);
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

void HRocker::initRocker(const char* rockerImageName, const char* rockerBGImageName, Point position)
{
    Sprite *spRockerBg = Sprite::create(rockerBGImageName);
    spRockerBg->setPosition(position);
    spRockerBg->setVisible(false);
    this->addChild(spRockerBg,0,tag_rockerBG);
    
    Sprite *spRocker = Sprite::create(rockerImageName);
    spRocker->setPosition(position);
    spRocker->setVisible(false);
    this->addChild(spRocker,1,tag_rocker);
    
    rockerBGPostion = position;
    rockerBGR = spRockerBg->getContentSize().width * 0.5;
    rockerDirection = -1; //表示摇杆方向不变
}

void HRocker::startRocker(bool isStopOther)
{
    Sprite *rocker = (Sprite*)this->getChildByTag(tag_rocker);
    rocker->setVisible(true);
    
    Sprite *rockerBg = (Sprite*)this->getChildByTag(tag_rockerBG);
    rockerBg->setVisible(true);
    
    //cocos2dx添加事件的方法
    //Director::sharedDirector()->getTouchDispatcher->addTargetedDelegate(this,-1,isStopOther);
    
    //cocos2dx, 3.0添加事件的方法
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void HRocker::stopRocker()
{
    Sprite *rocker = (Sprite*)this->getChildByTag(tag_rocker);
    rocker->setVisible(false);
    
    Sprite *rockerBg = (Sprite*)this->getChildByTag(tag_rockerBG);
    rockerBg->setVisible(false);
    
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}

float HRocker::getRad(Vec2 pos1, Vec2 pos2)
{
    float px1 = pos1.x;
    float py1 = pos1.y;
    float px2 = pos2.x;
    float py2 = pos2.y;
    
    //得到两点x，y的距离,并根据x,y计算出斜边的长度
    float x = px2 - px1;
    float y = py2 - py1;
    float xie = sqrt(pow(x, 2) + pow(y, 2));
    
    //计算出这个角的余玄值，三角函数中的定理: 角度余玄值 = 邻边/斜边
    float cosAngle = x / xie;
    
    
    float rad = acos(cosAngle);
    if (py2 < py1) {
        rad = -rad;
    }
    
    return rad;
}















