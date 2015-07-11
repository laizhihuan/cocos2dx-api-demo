//
//  AI.cpp
//  Chess
//
//  Created by zhihuanglai on 15/5/22.
//
//

#include "AI.h"

CCArray* AI::allPosisibleMove(SceneGame* game)
{
    CCArray* arr = CCArray::create();
	
    int start;
	
    if (game->_redTurn)
	{
		start = 0;
	}
	else
	{
		start = 16;
	}
    
	for (int i = start; i < start+16; i++)
	{
		Stone* s = game->_stone[i];
		// 已经死掉的棋子，不能移动
		if (s->_dead) continue;
        
		for (int row = 0; row < 9; row++)
            for (int col = 0; col < 8; col++)
            {
                int killid = game->getStoneIdByRowCol(row, col);
                if (game->canMove(i, row, col, killid))
                {
                    Step* step = Step::create(i, s->_row, s->_col, row, col, killid);
                    arr->addObject(step);
                }
            }
	}
    
    return arr;
}


int AI::calcScore(SceneGame* game)
{
    // enum STONE_TYPE {CHE, MA, PAO, BING, XIANG, SHI, JIANG}
    static int stoneScore[] = {100, 50, 50, 10, 20, 20, 1500};
    int scoreBlack = 0;
    int scoreRed = 0;
    
    //累加红旗的分
    for (int i = 0; i < 16; i++) {
        if (!game->_stone[i]->_dead) {
            scoreRed += stoneScore[game->_stone[i]->_type];
        }
    }
    
    //累加黑棋的分
    for (int i = 16; i < 32; i++) {
        if (!game->_stone[i]->_dead) {
            scoreBlack += stoneScore[game->_stone[i]->_type];
        }
    }
    
    return scoreBlack - scoreRed;
}

void AI::fakeMove(SceneGame* game, Step* step)
{
    Stone* sMove = game->_stone[step->_moveid];
    sMove->_row = step -> _rowTo;
    sMove->_col = step -> _colTo;
    
    if (_step->_killid != -1) {
        Stone* sKill = game->_stone[step->_killid];
        sKill->_dead = false;
    }
    
    //虽然是假的移动，但时轮到谁走的状态一样要重置
    game->_redTurn = !game->_redTurn;
}

void AI::unfakeMove(SceneGame* game, Step* step)
{
    Stone* sMove = game->_stone[step->_moveid];
    sMove->_row = step->_rowFrom;
    sMove->_col = step->_colFrom;
    
    if (step -> _killid != -1) {
        Stone* sKill = game -> _stone[step->_killid];
        sKill->_dead = false;
    }
    
    game->_redTurn = !game->_redTurn;
}

int AI::getMinScore(SceneGame* game, int level)
{
    if (level == 0) {
        return calcScore(game);
    }
    
    CCArray* allMove = allPosisibleMove(game);
    int minScore = 100000;
    
    for (int i=0; i < allMove->count(); i++) {
        Step* step = (Step*) allMove->objectAtIndex(i);
        fakeMove(game, step);
        
        int score = getMaxScore(game, level - 1);
        if (score < minScore) {
            minScore = score;
            
            if (level == _level) {
                _step = step;
            }
        }
        
        unfakeMove(game, step);
    }
    
    return minScore;
}

int AI::getMaxScore(SceneGame *game, int level)
{
    if (level == 0) {
        return calcScore(game);
    }
    
    CCArray* allMove = allPosisibleMove(game);
    int maxScore = -100000;
    
    for (int i = 0; i < allMove->count(); i++) {
        Step* step = (Step*)allMove->objectAtIndex(i);
        fakeMove(game, step);
        
        int score = getMinScore(game, level - 1);
        if (score > maxScore) {
            if (level == _level) {
                _step = step;
            }
        }
        unfakeMove(game, step);
    }
    
    return maxScore;
}

Step* AI::genStep(SceneGame* game, int level)
{
    _step = NULL;
    _level = level;
    getMaxScore(game, level);
    return _step;
}





























