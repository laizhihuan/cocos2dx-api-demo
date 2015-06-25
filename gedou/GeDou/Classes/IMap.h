//
//  Map.h
//  GeDou，副本中的地图信息
//
//  Created by zhihuanglai on 15/6/25.
//
//

#ifndef __GeDou__Map__
#define __GeDou__Map__

#include "cocos2d.h"
USING_NS_CC;

class IMap : public Node
{
public:
    IMap();
    ~IMap();
    
    //init地图, window_size为控制台大小
    void initMap(const char *map_name, const Size window_size);
    
    void moveMap(Node *hero, Size visible_size);
    
    bool judgeMap(Node *hero,Size visibleSize);
    
    CREATE_FUNC(IMap);
    
private:
    Sprite *m_map; //地图精灵
};

#endif /* defined(__GeDou__Map__) */
