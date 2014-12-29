//
//  CardNumSprite.h
//  MyCppGame
//
//  Created by zhihuanglai on 14-8-7.
//
//

#ifndef __MyCppGame__CardNumSprite__
#define __MyCppGame__CardNumSprite__

#include "cocos2d.h"

class CardNumSprite:public cocos2d::Sprite {
public:
    static CardNumSprite *createCardSprite(int number,int wight,int height,float cardSpriteX,float cardSpriteY);
    virtual bool init();
    CREATE_FUNC(CardNumSprite);
    
    void setNumber(int num);
    int getNumber();
    
private:
    int number;
    
    void enemyInit(int number,int wight,int height,float cardSpriteX,float cardSpriteY);
    
    cocos2d::Label *labelCardNumber;
    
    cocos2d::LayerColor *layerColor;
};



#endif /* defined(__MyCppGame__CardNumSprite__) */
