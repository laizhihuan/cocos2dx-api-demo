//
//  MyCommonLayer.cpp
//  自定义公共的layer，带有return的按钮
//  MyCppGame
//
//  Created by zhihuanglai on 15/5/6.
//
//

#include "MyCommonLayer.h"
#include "MyMenu.h"

bool MyCommonLayer::init()
{
	CCLayer::init();
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	CCMenuItemImage* item = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png");
	CCMenu* menu = CCMenu::createWithItem(item);
	addChild(menu);
    
	CCSize itemSize = item->getContentSize();
    
	item->setPosition(ccp(winSize.width / 2 - itemSize.width / 2, itemSize.height / 2 - winSize.height / 2));
    
	item->setTarget(this, menu_selector(MyCommonLayer::menuCallback));
    
	menu->setZOrder(10000);
    
	return true;
}

void MyCommonLayer::menuCallback(CCObject*)
{
    CCDirector::sharedDirector()->replaceScene(MyMenu::createScene());
	//CCDirector::sharedDirector()->popScene();
}

