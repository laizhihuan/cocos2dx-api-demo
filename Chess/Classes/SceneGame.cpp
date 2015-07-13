//
//  SceneGame.cpp
//  Chess
//
//  Created by zhihuanglai on 15/5/12.
//
//
#include "SceneGame.h"
#include "AI.h"

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

void SceneGame::onEnter()
{
    Layer::onEnter();
    _steps = CCArray::create();
    _steps->retain();
}

void SceneGame::onExit()
{
    Layer::onExit();
    _steps->release();
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
    
    initRegretButton();
    return true;
}

void SceneGame::initRegretButton()
{
	Menu* menu = Menu::create();
	addChild(menu);
    
	MenuItem* item = MenuItemImage::create("regret.jpg", "regret.jpg");
	menu->addChild(item);
    
	item->setTarget(this, menu_selector(SceneGame::regret));
	moveNode(Vec2(200, 100), item);
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
    
    // 纪录走棋信息
    Step* step = Step::create(_selectId, _stone[_selectId]->_row, _stone[_selectId]->_col, row, col, tagetId);
    _steps->addObject(step);
    
    //将棋子移动到目标点
    _stone[_selectId]->move(row, col);
	_selectId = -1;
	_selectFlag->setVisible(false);
    
    //如果走棋信息
    if (tagetId != -1) {
        _stone[tagetId]->_dead=true;
        _stone[tagetId]->setVisible(false);
        
        //检查游戏是否
        checkGameOver(tagetId);
    }
    
    _redTurn = !_redTurn;
    
    // 黑棋加入AI, TODO:AI没有完善需要进一步调试，完善
    if (!_redTurn) {
        //Step* step = _ai->genStep(this, 4);
        //_stone[step->_moveid]->move(step->_rowTo, step->_colTo);
        //
        //if (step->_killid != -1) {
        //    _stone[step->_killid]->_dead = true;
        //    _stone[step->_killid]->setVisible(false);
        //}
        
        //_redTurn = !_redTurn;
        //_steps->addObject(step);
    }
}

void SceneGame::regret(CCObject*)
{
    if (_steps->count() == 0) {
        return;
    }
    
    //将棋子恢复到原来位置
    Object* obj = _steps->lastObject();
    Step* step = (Step*)obj;
    Stone* sMove = _stone[step->_moveid];
    sMove->move(step->_rowFrom, step->_colFrom);
    
    if (step->_killid != -1) {
        Stone* killStone = _stone[step->_killid];
        killStone->_dead = false;
        killStone->setVisible(true);
    }
    
    // 初始化一些和移动相关的中间变量
	_selectId = -1;
	_selectFlag->setVisible(false);
	_redTurn = !_redTurn;
    
	// 把array里的最后一个对象删除
	_steps->removeLastObject();
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

int SceneGame::getStoneCountInLine(int firstRow, int firstCol, int endRow, int endCol)
{
    //如果两点不在同一条直线上，返回－1
    if (firstRow != endRow && firstCol != endCol) return -1;
    
    int count = 0;
    
    if (firstRow == endRow) {
        int min = firstCol < endCol ? firstCol : endCol;
        int max = firstCol + endCol - min;
        for (int col = min + 1; col < max; col++) {
            int id = getStoneIdByRowCol(firstRow, col);
            if (id != -1) {
                count ++;
            }
        }
    } else if(firstCol == endCol) {
        int min = firstRow < endRow ? firstRow : endRow;
        int max = firstRow + endRow - min;
        for (int row = min + 1; row < max; row ++) {
            int id = getStoneIdByRowCol(row, firstCol);
            if (id != -1) {
                count ++;
            }
        }
    }
    
    return count;
}

bool SceneGame::canMoveChe(int moveId, int row, int col, int killid)
{
    if (getStoneCountInLine(row, col, _stone[moveId]->_row, _stone[moveId]->_col) == 0) {
        return true;
    }
    return false;
}

bool SceneGame::canMoveMa(int moveId, int row, int col, int killid)
{
    int r = _stone[moveId]->_row;
    int c = _stone[moveId]->_col;
    
    int d = abs(r-row)*10 + abs(c-col);
    
    //if (!(d == 21 || d == 12) ) {
    if (d != 21 && d != 12) {
        return false;
    }
    
    if (d == 21) {
        int mr = (r+row)/2;
        int mc = c;
        if (getStoneIdByRowCol(mr, mc) != -1) {
            return false;
        }
    } else {
        int mr = r;
        int mc = (r+col)/2;
        if (getStoneIdByRowCol(mr, mc) != -1) {
            return false;
        }
    }
    
    return true;
}

bool SceneGame::canMovePao(int moveId, int row, int col, int killid)
{
    if (killid == -1) {
        return canMoveChe(moveId, row, col, killid);
    }
    
    return getStoneCountInLine(row, col, _stone[moveId]->_row, _stone[moveId]->_col) == 1;
}

bool SceneGame::canMoveBing(int moveId, int row, int col, int killid)
{
    //兵只能走一步
    int r = _stone[moveId]->_row;
    int c = _stone[moveId]->_col;
    
    int d = abs(r - row) * 10 + abs(c - col);
    
    if (d != 10 && d != 1) {
        return false;
    }
    
    //区别是红方还是黑方
    if (_stone[moveId]->isRed == MainScene::_selected) {
        //不能后退
        if (row < r) {
            return false;
        }
        //没有过河，不能平移
        if (r <= 4 && row == r) {
            return false;
        }
    }
    else {
        if (row > r) {
            return false;
        }
        
        if (r >= 4 && row == r) {
            return false;
        }
    }
    
    return true;
}

bool SceneGame::canMoveJiang(int moveId, int row, int col, int killid)
{
    // 老蒋照面
	if (killid != -1 && _stone[killid]->_type == Stone::JIANG)
    {
        return canMoveChe(moveId, row, col, killid);
    }
    
    // 不照面的规则
    if (_stone[moveId]->isRed == MainScene::_selected)
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

void SceneGame::checkGameOver(int killid)
{
    Stone* stone = _stone[killid];
    if (stone->_type == Stone::JIANG) {
        //红棋黑棋位置对调
        
        Director::getInstance()->replaceScene(CreateScene(SceneGame::create(true)));
    }
}

