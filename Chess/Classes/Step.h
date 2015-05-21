//
//  Step.h
//  Chess
//
//  Created by zhihuanglai on 15/5/21.
//
//

#ifndef __Chess__Step__
#define __Chess__Step__

#include "cocos2d.h"
USING_NS_CC;

class Step : public Object
{
public:
	static Step* create(int moveid, int rowFrom, int colFrom, int rowTo, int colTo, int killid)
	{
		Step* step = new Step;
		step->_moveid = moveid;
		step->_rowFrom = rowFrom;
		step->_colFrom = colFrom;
		step->_rowTo = rowTo;
		step->_colTo = colTo;
		step->_killid = killid;
        
		step->autorelease();
		return step;
	}
	int _moveid;
	int _rowFrom;
	int _colFrom;
	int _rowTo;
	int _colTo;
	int _killid;
};


#endif /* defined(__Chess__Step__) */
