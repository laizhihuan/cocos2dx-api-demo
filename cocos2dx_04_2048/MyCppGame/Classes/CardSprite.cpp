//
//  CardSprite.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 14-8-7.
//
//

#include "CardSprite.h"

USING_NS_CC;

CardSprite* CardSprite::createCardSprite(int number,int wight,int height,float cardSpriteX,float cardSpriteY) {
    CardSprite *card = new CardSprite();
    if (card && card->init()) {
        card->autorelease();
        card->enemyInit(number,wight,height,cardSpriteX,cardSpriteY);
        return card;
    }
    
    CC_SAFE_DELETE(card);
    return NULL;
}

bool CardSprite::init() {
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

void CardSprite::setNumber(int num) {
    number = num;
    
    if (number > 0) {
        labelCardNumber->setString(__String::createWithFormat("%i",number)->getCString());
    } else {
        labelCardNumber->setString("");
    }
}

int CardSprite::getNumber() {
    return number;
}

void CardSprite::enemyInit(int number,int wight,int height,float cardSpriteX,float cardSpriteY) {
    number = number;
    
    layerColor = cocos2d::LayerColor::create(Color4B(200,190,180,255),wight-15,height-15);
    layerColor->setPosition(Point(cardSpriteX,cardSpriteY));
    
    if(number>0) {
        labelCardNumber = cocos2d::Label::create(__String::createWithFormat("%i",number)->getCString(),"HirakakuProN-W6",100);
    } else {
        labelCardNumber = cocos2d::Label::create("","HirakakuProN-W6",100);
    }
    
    Size contentSize = layerColor->getContentSize();
    labelCardNumber->setPosition(Point(contentSize.width/2,contentSize.height/2));
    layerColor->addChild(labelCardNumber);
    this->addChild(layerColor);
}
