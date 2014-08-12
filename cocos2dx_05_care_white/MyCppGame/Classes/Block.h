//
//  Block.h
//  MyCppGame
//
//  Created by zhihuanglai on 14-8-11.
//
//

#ifndef __MyCppGame__Block__
#define __MyCppGame__Block__

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;

class Block:public Sprite {

private:
    static Vector<Block*> * blocks;
    
    int lineIndex = 0;
    
public:
    static Block* createWithArgs(Color3B color,Size size, std::string labelStr,float fontSize,
                                 Color4B textColor);
    
    virtual bool initWithArgs(Color3B color,Size size, std::string labelStr,float fontSize,
                              Color4B textColor);
    
    void removeBlock();
    
    void setLineIndex(int index);
    
    int getLineIndex();
    
    static Vector<Block*> * getBlocks();
    
    void moveDown();
};

#endif /* defined(__MyCppGame__Block__) */
