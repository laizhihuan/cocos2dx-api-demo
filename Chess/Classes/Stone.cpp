//
//  Stone.cpp
//  Chess
//
//  Created by zhihuanglai on 15/5/13.
//
//

#include "Stone.h"
#include "SceneGame.h"

Vec2 Stone::_ptOff;
float Stone::_d; 

Stone* Stone::create(int id)
{
    Stone* s = new Stone();
    s->init(id);
    s->autorelease();
    return s;
};

bool Stone::init(int id)
{
    _id   = id;
    _type = getType(id);
    _row  = getRow(id);
    _col  = getCol(id);
    isRed = _id<16;
    
    
    const char* bfiles[] = { "bche.png", "bma.png", "bpao.png", "bzu.png", "bxiang.png", "bshi.png", "bjiang.png" };
	const char* rfiles[] = { "rche.png", "rma.png", "rpao.png", "rbing.png", "rxiang.png", "rshi.png", "rshuai.png" };
	if (isRed)
	{
		CCSprite::initWithFile(rfiles[_type]);
	}
	else
	{
		CCSprite::initWithFile(bfiles[_type]);
	}
    
	setPosition(getPos());
	setScale(1.1f);
    
	return true;
};

