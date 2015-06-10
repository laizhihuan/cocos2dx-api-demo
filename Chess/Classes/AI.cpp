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
    
    for (int i=16; i<32; i++) {
        Stone* stone = game->_stone[i];
        //已经死掉的棋子，不能移动
        if (stone->_dead) {
            continue;
        }
        
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 8; col++)
            {
                int killid = game->getStoneIdByRowCol(row, col);
                if (game->canMove(i, row, col, killid))
                {
                    Step* step = Step::create(i, stone->_row, stone->_col, row, col, killid);
                    arr->addObject(step);
                }
            }

        }
    }
    
    return arr;
}


int AI::calcScore(SceneGame* game)
{
    return 0;
}

Step* AI::genStep(SceneGame* game)
{
    return NULL;
}

void AI::fakeMove(SceneGame* game, Step* step)
{
}

void AI::unfakeMove(SceneGame* game, Step* step)
{
    
}