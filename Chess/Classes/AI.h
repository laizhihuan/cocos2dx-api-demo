//
//  AI.h
//  Chess
//
//  Created by zhihuanglai on 15/5/22.
//
//

#ifndef __Chess__AI__
#define __Chess__AI__

#include "SceneGame.h"
#include "Step.h"

class AI
{
public:
    /**
     *  生成ai的步骤
     *
     *  @param game 游戏逻辑
     *
     *  @return ai的棋子下一步
     */
    Step* genStep(SceneGame* game, int level);
    /**
     *  所有可能的走法
     *
     *  @param game <#game description#>
     *
     *  @return <#return value description#>
     */
    CCArray* allPosisibleMove(SceneGame* game);
    /**
     *  模拟移动棋子
     *
     *  @param game <#game description#>
     *  @param step <#step description#>
     */
    void fakeMove(SceneGame* game, Step* step);
    /**
     *  撤销模拟移动
     *
     *  @param game <#game description#>
     *  @param step <#step description#>
     */
    void unfakeMove(SceneGame* game, Step* step);
    /**
     *  计算分数
     *
     *  @param game <#game description#>
     *
     *  @return <#return value description#>
     */
    int calcScore(SceneGame* game);
    
    /**
     *  假移动的step
     */
    Step* _step;
    int _level;
    int getMaxScore(SceneGame* game, int level);
    int getMinScore(SceneGame* game, int level);
    
};

#endif /* defined(__Chess__AI__) */
