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
    
    switch (number) {
        case 2:
            layerColor->setColor(Color3B(200,190,180));
            break;
        case 4:
            layerColor->setColor(Color3B(240,220,200));
            break;
        case 6:
            layerColor->setColor(Color3B(240,190,180));
            break;
        case 8:
            layerColor->setColor(Color3B(240,180,160));
            break;
        case 16:
            layerColor->setColor(Color3B(240,170,150));
            break;
        case 32:
            layerColor->setColor(Color3B(240,160,140));
            break;
        case 64:
            layerColor->setColor(Color3B(240,150,130));
            break;
        case 128:
            layerColor->setColor(Color3B(240,140,120));
            break;
        case 256:
            layerColor->setColor(Color3B(240,130,110));
            break;
        case 512:
            layerColor->setColor(Color3B(240,120,100));
            break;
        case 1024:
            layerColor->setColor(Color3B(240,100,80));
            break;
        default:
            layerColor->setColor(Color3B(200,190,180));
            break;
    }
    
    if (number > 0) {
        labelCardNumber->setString(__String::createWithFormat("%i",number)->getCString());
    } else {
        labelCardNumber->setString("");
    }
    //TODO:setSystemFontSize好像没有变化
    if(number>=0) {
        labelCardNumber->setSystemFontSize(100);
    } else if(number >= 16) {
        labelCardNumber->setSystemFontSize(80);
    } else if(number >= 128) {
        labelCardNumber->setSystemFontSize(50);
    } else if(number >= 1024) {
        labelCardNumber->setSystemFontSize(20);
    }
}

int CardSprite::getNumber() {
    return number;
}

void CardSprite::enemyInit(int num,int wight,int height,float cardSpriteX,float cardSpriteY) {
    number = num;
    
    layerColor = cocos2d::LayerColor::create(Color4B(200,190,180,255),wight-15,height-15);
    layerColor->setPosition(Point(cardSpriteX,cardSpriteY));
    
    if(number>0) {
        labelCardNumber = cocos2d::Label::createWithSystemFont(__String::createWithFormat("%i",number)->getCString(),"HirakakuProN-W6",60);
    } else {
        labelCardNumber = cocos2d::Label::createWithSystemFont("","HirakakuProN-W6",60);
    }
    
    Size contentSize = layerColor->getContentSize();
    labelCardNumber->setPosition(Point(contentSize.width/2,contentSize.height/2));
    layerColor->addChild(labelCardNumber);
    this->addChild(layerColor);
}
