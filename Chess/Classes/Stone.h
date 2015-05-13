//
//  Stone.h
//  Chess
//
//  Created by zhihuanglai on 15/5/13.
//
//

#ifndef __Chess__Stone__
#define __Chess__Stone__

#include "Common.h"

class Stone : public Sprite
{
public:
    static Stone* create(int id);
    bool init(int id);
};

#endif /* defined(__Chess__Stone__) */
