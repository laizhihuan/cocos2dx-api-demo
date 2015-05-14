//
//  Stone.h
//  Chess
//
//  Created by zhihuanglai on 15/5/13.
//
//

#ifndef __Chess__Stone__
#define __Chess__Stone__

#include "Common.h"

class Stone : public Sprite
{
public:
    enum STONE_TYPE {CHE,MA,PAO,BING,XIANG,SHI,JIANG};
    
    Vec2 getPos()
    {
        float d = _d;
        float x = _col * d;
        float y = _row * d;
        return Vec2(x, y) + _ptOff;
    };
    
    STONE_TYPE getType(int id)
    {
        static Stone::STONE_TYPE type[32] = { CHE, MA, XIANG, SHI, JIANG, SHI, XIANG, MA, CHE,
            PAO, PAO,
            BING, BING, BING, BING, BING,
            BING, BING, BING, BING, BING,
            PAO, PAO,
            CHE, MA, XIANG, SHI, JIANG, SHI, XIANG, MA, CHE, };
        return type[id];
    };
    
    
    int getRow(int id)
    {
        static int row[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,
            2, 2,
            3, 3, 3, 3, 3,
            6, 6, 6, 6, 6,
            7, 7,
            9, 9, 9, 9, 9, 9, 9, 9, 9, };
        return  row[id];
    };
    
    int getCol(int id)
    {
        static int col[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8,
            1, 7,
            0, 2, 4, 6, 8,
            0, 2, 4, 6, 8,
            1, 7,
            0, 1, 2, 3, 4, 5, 6, 7, 8, };
        return  col[id];
    };
    
public:
    static Stone* create(int id);
    bool init(int id);
    
    /**
     *  棋子id
     */
    int _id;
    /**
     *  是否为红棋，true表示红棋，false表示黑棋
     */
    bool isRed;
    /**
     *  棋子的类型，车马炮
     */
    STONE_TYPE _type;
    
    /**
     *  棋盘中的坐标，row行，col列
     */
    int _row;
    int _col;
    
    /**
     *  是否死亡
     */
    bool _dead;
    /**
     *  棋子摆放的偏移量
     */
    static Vec2 _ptOff;
    /**
     *  棋子的直径
     */
    static float _d;
    
};

#endif /* defined(__Chess__Stone__) */
