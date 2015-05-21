//
//  Common.h
//  Chess
//
//  Created by zhihuanglai on 15/5/11.
//
//

#ifndef __Chess__Common__
#define __Chess__Common__

#include "cocos2d.h"
USING_NS_CC;

#define winSize CCDirector::getInstance()->getWinSize()

//#define DF_WINSIZE ##

/**
 *  通过一个layer，创建一个场景的通用方法
 *
 *  @param layer
 *
 *  @return scene
 */
static inline Scene* CreateScene(Layer* layer)
{
    Scene* scene = Scene::create();
    scene->addChild(layer);
    return scene;
}

/**
 *  移动一个节点到指定位置
 *
 *  @param ptOff 指定位置
 *  @param node  需要移动的节点
 *
 *  @return <#return value description#>
 */
static inline void moveNode(Vec2 ptOff, Node* node)
{
    node->setPosition(node->getPosition()+ptOff);
}

#endif /* defined(__Chess__Common__) */
