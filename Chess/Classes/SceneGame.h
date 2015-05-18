//
//  SceneGame.h
//  Chess
//
//  Created by zhihuanglai on 15/5/12.
//
//

#ifndef __Chess__SceneGame__
#define __Chess__SceneGame__

#include "Common.h"
#include "cocos2d.h"
#include "Stone.h"
USING_NS_CC;

class SceneGame : public Layer
{
public:
    /**
     *  创建游戏场景
     *
     *  @param isRed true表示选择红棋，false表示选择黑棋
     *
     *  @return 游戏场景
     */
    static Scene* createScene(bool isRed);
    
    static SceneGame* create(bool isRed);
    
    bool init(bool red);
    
    /**
     *  游戏中的棋子数组
     */
    Stone* _stone[32];
    
    Point _plateOffset;
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
    
    /**
     *  选择棋子的id
     */
    int _selectId;
    
    /**
     *  选中一个棋子
     *
     *  @param touch 触摸
     */
    void selectStone(Touch *touch);
    /**
     *  移动一个棋子
     *
     *  @param touch <#touch description#>
     */
    void moveStone(Touch *touch);
    /**
     *  获取触摸点id
     *
     *  @param touch
     */
    int getClickStone(Touch *touch);
    
    /**
     *  轮到谁走了
     */
    bool _redTurn;
    
    /**
     *  选中棋子后显示一个背景精灵
     */
    Sprite* _selectFlag;
    
    bool getRowColByPos(int &row, int& col, Vec2 ptPos);
    
    int getStoneIdByRowCol(int row,int col);
    
    Vec2 getPosByRowCol(int row, int col);
    
    bool isSameColor(int id1, int id2)
	{
		return _stone[id1]->isRed == _stone[id2]->isRed;
	}
    /**
     *  判断选择的棋子是否可以移动
     *
     *  @param moveId 移动的棋子id
     *  @param row    移动目标行
     *  @param col    移动目标列
     *  @param killid 移动目标可能出现的棋子
     *
     *  @return true表示可以移动，false表示不能移动
     */
    bool canMove(int moveId, int row, int col, int killid);
    
    bool canMoveChe(int moveId, int row, int col, int killid);
    bool canMoveMa(int moveId, int row, int col, int killid);
    bool canMovePao(int moveId, int row, int col, int killid);
    bool canMoveBing(int moveId, int row, int col, int killid);
    bool canMoveJiang(int moveId, int row, int col, int killid);
    bool canMoveShi(int moveId, int row, int col, int killid);
    /**
     *  实现蒋的移动规则
     */
    bool canMoveXiang(int moveId, int row, int col, int killid);
};

#endif /* defined(__Chess__SceneGame__) */
