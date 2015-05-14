//
//  SceneGame.cpp
//  Chess
//
//  Created by zhihuanglai on 15/5/12.
//
//
#include "SceneGame.h"

Scene* SceneGame::createScene(bool isRed)
{
    Scene* scene = Scene::create();
    SceneGame* layer = SceneGame::create(isRed);
    scene->addChild(layer);
    return scene;
}

SceneGame* SceneGame::create(bool isRed)
{
    SceneGame* pRet = new SceneGame();
    if(pRet)
    {
        if (pRet->init(isRed)) {
            pRet->autorelease();
        } else {
            pRet->release();
        }
    }
    else
    {
        return NULL;
    }
    
    return pRet;
}

bool SceneGame::init(bool red)
{
    if (!Layer::init()) {
        return false;
    }
    
    //画棋盘
    Sprite* plate = CCSprite::create("background.png");
    this->addChild(plate);
    plate->setAnchorPoint(Vec2::ZERO);
    plate->setPosition(_plateOffset);
    plate->setScale((winSize.height -_plateOffset.y *2) / plate->getContentSize().height);
    
    //摆棋子
    Stone::_ptOff = Vec2(51, 27);
	Stone::_d = winSize.height / 10;
    
    for (int i=0; i<32; i++) {
        _stone[i] = Stone::create(i);
        addChild(_stone[i]);
    }
    
    //设置触摸事件
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    //背景精灵
    _selectFlag = Sprite::create("selected.png");
    addChild(_selectFlag);
    _selectFlag->setVisible(false);
    
    _selectId = -1;
    
    return true;
}

bool SceneGame::getRowColByPos(int &row, int& col, Vec2 ptPos)
{
    for (row = 0; row<10; row++)
    {
        for (col = 0; col<9; col++)
        {
            Vec2 pt = getPosByRowCol(row,col);
            if (pt.getDistance(ptPos) < Stone::_d/2)
            {
                return true;
            }
        }
    }
    return false;
}

Vec2 SceneGame::getPosByRowCol(int row, int col)
{
    float d = Stone::_d;
	float x = col * d;
	float y = row * d;
	return Vec2(x, y) + Stone::_ptOff;
}

int SceneGame::getStoneIdByRowCol(int row,int col)
{
    for (int i = 0; i < 32; i++)
	{
		if (_stone[i]->_row == row
            && _stone[i]->_col == col
			&& !_stone[i]->_dead)
			return i;
	}
	return -1;
}


int SceneGame::getClickStone(Touch *touch)
{
    Vec2 ptClick = touch->getLocation();
    int row,col;
    
    if (!getRowColByPos(row, col, ptClick)) {
        return -1;
    }
    return getStoneIdByRowCol(row,col);
}

void SceneGame::selectStone(Touch *touch)
{
    int clickId = getClickStone(touch);
    if (clickId != -1) {
        _selectFlag->setVisible(true);
        _selectFlag->setPosition(_stone[clickId]->getPosition());
        
        _selectId = clickId;
    }
}

bool SceneGame::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true ;
}
void SceneGame::onTouchMoved(Touch *touch, Event *unused_event)
{
}
void SceneGame::onTouchEnded(Touch *touch, Event *unused_event)
{
    
}
void SceneGame::onTouchCancelled(Touch *touch, Event *unused_event)
{
}
