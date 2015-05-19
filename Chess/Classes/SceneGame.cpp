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
    Stone::_ptOff = Vec2(60, 36);
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
    
    _redTurn = true;
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
    if (clickId != -1)
    {
        if (_redTurn == _stone[clickId]->isRed)
        {
            _selectFlag->setVisible(true);
            _selectFlag->setPosition(_stone[clickId]->getPosition());
            
            _selectId = clickId;
        }
    }
}

void SceneGame::moveStone(Touch *touch)
{
    int tagetId = getClickStone(touch);
    
    // 先要判断，目标是不是己方的棋子，如果是，那么换选择
	if (tagetId != -1 && isSameColor(tagetId, _selectId))
	{
		_selectId = tagetId;
		_selectFlag->setPosition(_stone[tagetId]->getPosition());
		return;
	}
    
    int row,col;
    //如果点击的目标位置，不在棋盘内，不能走
    if (!getRowColByPos(row, col, touch->getLocation())) {
        return;
    }
    
    // TODO:加入走棋规则的判断
    if (!canMove(_selectId, row, col, tagetId)) {
        return;
    }
    
    //将棋子移动到目标点
    _stone[_selectId]->move(row, col);
	_selectId = -1;
	_selectFlag->setVisible(false);
    
    //如果走棋信息
    if (tagetId != -1) {
        _stone[tagetId]->_dead=true;
        _stone[tagetId]->setVisible(false);
    }
    
    _redTurn = !_redTurn;
}

bool SceneGame::canMove(int moveId, int row, int col, int killid)
{
    switch (_stone[moveId]->_type) {
        case Stone::CHE:
            return canMoveChe(moveId, row, col, killid);
            break;
        case Stone::MA:
            return canMoveMa(moveId, row, col, killid);
            break;
        case Stone::PAO:
            return canMovePao(moveId, row, col, killid);
            break;
        case Stone::BING:
            return canMoveBing(moveId, row, col, killid);
            break;
        case Stone::JIANG:
            return canMoveJiang(moveId, row, col, killid);
            break;
        case Stone::SHI:
            return canMoveShi(moveId, row, col, killid);
            break;
        case Stone::XIANG:
            return canMoveXiang(moveId, row, col, killid);
            break;
        default:
            break;
    }
    return true;
}


bool SceneGame::canMoveChe(int moveId, int row, int col, int killid)
{
    return true;
}
bool SceneGame::canMoveMa(int moveId, int row, int col, int killid)
{
    return true;
}
bool SceneGame::canMovePao(int moveId, int row, int col, int killid)
{
    return true;
}
bool SceneGame::canMoveBing(int moveId, int row, int col, int killid)
{
    return true;
}

bool SceneGame::canMoveJiang(int moveId, int row, int col, int killid)
{
    if (_stone[moveId]->isRed)
    {
        if (row > 2 || row < 0) {
            return false;
        }
    }
    else
    {
        if (row > 9 || row < 7) {
            return false;
        }
    }
    
    if (col < 3 || col > 5) {
        return false;
    }
    
    int r = _stone[moveId]->_row;
    int c = _stone[moveId]->_col;
    
    int d = abs(r - row) * 10 + abs(c - col);
    
    if (d == 10 || d == 1) {
        return true;
    }
    
    return false;
}

bool SceneGame::canMoveShi(int moveId, int row, int col, int killid)
{
    if (_stone[moveId]->isRed)
    {
        if (row > 2 || row < 0) {
            return false;
        }
    }
    else
    {
        if (row > 9 || row < 7) {
            return false;
        }
    }
    
    if (col < 3 || col > 5) {
        return false;
    }
    
    int r = _stone[moveId]->_row;
    int c = _stone[moveId]->_col;
    
    int d = abs(r - row) * 10 + abs(c - col);
    
    if (d == 11) {
        return true;
    }
    
    return false;
}

bool SceneGame::canMoveXiang(int moveId, int row, int col, int killid)
{
    //相不能过河
    if (_stone[moveId]->isRed) {
        if (row > 4) {
            return false;
        }
    } else {
        if (row < 5) {
            return false;
        }
    }
    
    //相行田
    int r = _stone[moveId]->_row;
    int c = _stone[moveId]->_col;
    
    int d = abs(r - row) * 10 + abs(c - col);
    if (d != 22) {
        return false;
    }
    
    //伴相眼
    int mr = (r+row)/2;
    int mc = (c+col)/2;
    int id = getStoneIdByRowCol(mr, mc);
    if (id != -1) {
        return false;
    }
    return true;
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
    //首先选择一个棋子，然后是走棋
    if (_selectId == -1)
    {
        selectStone(touch);
    }
    else
    {
        moveStone(touch);
    }
}

void SceneGame::onTouchCancelled(Touch *touch, Event *unused_event)
{
}
