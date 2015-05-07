//
//  MyActions.h
//  MyCppGame
//
//  Created by zhihuanglai on 15/5/7.
//
//

#ifndef __MyCppGame__MyActions__
#define __MyCppGame__MyActions__

#include "MyCommonLayer.h"

class MyActions : public MyCommonLayer
{
public:
	static CCScene* scene();
	CREATE_FUNC(MyActions);
	bool init();
    
	void menuCallback(CCObject* sender);
    
	bool onTouchBegan(CCTouch* t, CCEvent* e)
	{
		return true;
	}
    
	void onTouchMoved(CCTouch* t, CCEvent*e)
	{
		setPositionY(getPositionY() + t->getDelta().y);
	}
};


#endif /* defined(__MyCppGame__MyActions__) */
