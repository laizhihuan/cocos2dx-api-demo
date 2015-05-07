//
//  MyActions.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 15/5/7.
//
//

#include "MyActions.h"

static const char* _actionName[] =
{
	"CCMoveBy",
	"CCMoveTo",
	"CCRotateBy",
	"CCRotateTo",
	"CCScaleBy",
	"CCScaleTo",
	"CCSkewBy",
	"CCSkewTo",
	"CCJumpBy",
	"CCJumpTo",
	"CCBezierBy",
	"CCBezierTo",
	"CCFadeIn",
	"CCFadeOut",
	"CCTintTo",
	"CCTintBy",
	"CCBlink",
	"CCDelayTime",
	"CCOrbitCamera",
	"CCCardinalSplineTo",
	"CCCardinalSplineBy",
	"CCCatmullRomTo",
	"CCCatmullRomBy",
	"CCCallFunc",
	"CCCallFuncN",
	"CCCallFuncND"
};


CCScene* MyActions::scene()
{
	CCScene* s = CCScene::create();
	MyActions* layer = MyActions::create();
	s->addChild(layer);
	return s;
}

bool MyActions::init()
{
	MyCommonLayer::init();
    
	CCMenu* menu = CCMenu::create();
	for (int i = 0; i < sizeof(_actionName) / sizeof(*_actionName); i++)
	{
		CCMenuItemFont* item = CCMenuItemFont::create(_actionName[i]);
		item->setTag(1000 + i);
		item->setTarget(this, menu_selector(MyActions::menuCallback));
		menu->addChild(item);
	}
    
	addChild(menu);
	menu->alignItemsVertically();
    
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
    
	return true;
}

void MyActions::menuCallback(CCObject* sender)
{
	CCMenuItemFont* item = (CCMenuItemFont*)sender;
	int tag = item->getTag() - 1000;
	const char* actionName = _actionName[tag];
	
	//CCDirector::sharedDirector()->replaceScene(ActionsDisplay::scene(actionName));
    Director::sharedDirector()->pushScene(ActionsDisplay::scene(actionName));

}
