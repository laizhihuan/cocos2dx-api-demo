//
//  Map.cpp
//  GeDou
//
//  Created by zhihuanglai on 15/6/25.
//
//

#include "IMap.h"

IMap::IMap():m_map(NULL)
{
    
}

IMap::~IMap()
{
    
}

void IMap::initMap(const char *map_name, const Size window_size)
{
    this->m_map=Sprite::create(map_name);
    m_map->setAnchorPoint(Vec2(0,0));
    this->setAnchorPoint(Vec2(0,0));
    this->addChild(m_map);
}

void IMap::moveMap(Node *hero, Size visibleSize)
{
    if (hero->getPositionX() == visibleSize.width/2) {
        if (this->getPositionX() != -(m_map->getContentSize().width - visibleSize.width)) {
            this->setPosition(this->getPositionX()-1,this->getPositionY());
        }
    }
}

bool IMap::judgeMap(Node *hero, Size visibleSize)
{
    if (this->getPositionX() != -(m_map->getContentSize().width - visibleSize.width)) {
        return false;
    } else {
        return true;
    }
}



