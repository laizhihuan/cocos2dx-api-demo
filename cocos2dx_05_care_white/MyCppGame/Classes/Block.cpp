//
//  Block.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 14-8-11.
//
//

#include "Block.h"

Vector<Block*> * Block::blocks = new Vector<Block*>();

Vector<Block*> * Block::getBlocks() {
    return Block::blocks;
}

Block* Block::createWithArgs(Color3B color,Size size, std::string labelStr,float fontSize,
                             Color4B textColor) {
    auto b = new Block();
    b->initWithArgs(color, size, labelStr, fontSize, textColor);
    b->autorelease();
    
    blocks->pushBack(b);
    return b;
}


bool Block::initWithArgs(Color3B color,Size size, std::string labelStr,float fontSize,
                             Color4B textColor) {
    Sprite::init();
    
    lineIndex = 0;
    
    setContentSize(size);
    setAnchorPoint(Point::ZERO);
    setTextureRect(Rect(0,0,size.width,size.height));
    setColor(color);
    
    auto label = Label::create();
    label->setString(labelStr);
    label->setSystemFontSize(fontSize);
    label->setTextColor(textColor);
    addChild(label);
    label->setPosition(size.width/2,size.height/2);
    
    return true;
}

void Block::removeBlock() {
    auto c = getColor();
    
    log("remove block lineIndex color(%d,%d,%d)", c.r,c.g,c.b);
    
    removeFromParent();
    blocks->eraseObject(this);
}

void Block::setLineIndex(int index) {
    this->lineIndex = index;
    log("line index %d ",index);
}

int Block::getLineIndex() {
    return this->lineIndex;
}

void Block::moveDown() {
    this->lineIndex--;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    runAction(Sequence::create(MoveTo::create(0.1f,
                                              Point(getPositionX(),lineIndex*visibleSize.height/4)),
                               CallFunc::create([this](){
        
        //如果行索引小于零表示块已经不在屏幕内，可以移除
        if (lineIndex < 0) {
            this->removeBlock();
        }
        
    }), NULL));
}


