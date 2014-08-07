//
//  CardSprite.h
//  MyCppGame
//
//  Created by zhihuanglai on 14-8-7.
//
//

#ifndef __MyCppGame__CardSprite__
#define __MyCppGame__CardSprite__

#include "cocos2d.h"

class CardSprite:public cocos2d::Sprite {
public:
    static CardSprite *createCardSprite(int number,int wight,int height,float cardSpriteX,float cardSpriteY);
    virtual bool init();
    CREATE_FUNC(CardSprite);
    
    void setNumber(int num);
    int getNumber();
    
private:
    int number;
    
    void enemyInit(int number,int wight,int height,float cardSpriteX,float cardSpriteY);
    
    cocos2d::Label *labelCardNumber;
    
    cocos2d::LayerColor *layerColor;
};

#endif /* defined(__MyCppGame__CardSprite__) */
