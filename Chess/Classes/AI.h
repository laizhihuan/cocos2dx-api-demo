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
    
    Step* genStep(Game* game);
    
    ccArray* allPosisibleMove(SceneGame* game);
    
    void fakeMove(SceneGame* game, Step* step);
    
    void unfakeMove(SceneGame* game, Step* step);
    
    int calcScore(SceneGame* game);
    
};

#endif /* defined(__Chess__AI__) */
