//
//  ErasableLayer.h
//  MyCppGame
//
//  Created by zhihuanglai on 15/5/4.
//
//

#ifndef __MyCppGame__ErasableLayer__
#define __MyCppGame__ErasableLayer__

#include "cocos2d.h"

USING_NS_CC;

/**
 *  可擦除的Layer,http://blog.csdn.net/linchaolong
 */
class ErasableLayer :public Layer {

public:
    // 创建ErasableLayer
    //1.遮罩层
    //2.橡皮擦（可以是Sprite或者纹理的路径）
    static ErasableLayer* create(const char* layerPath, const char* erasaPath);
    static ErasableLayer* create(Node *layer, Sprite* erasa);
    static ErasableLayer* create(Node *layer, const char* erasaPath);
    static ErasableLayer* create(const char* layerPath, Sprite* erasa);
    
    // 还原
    void clear();
    // 是否可擦除
    void setErasable(bool);
    
    bool onTouchBegan(Touch* touch, Event  *event);
    void onTouchesMoved(Touch* touch, Event *event);
    void onTouchEnded(Touch* touch, Event  *event);
protected:
    ErasableLayer();
    ~ErasableLayer();
    
    bool init(Node *layer, Sprite* erasa);
    void tick(float);
private:
    Node* layer_;
    Sprite* erasa_;
    bool isErasable_;
    RenderTexture* rt_;
};

#endif /* defined(__MyCppGame__ErasableLayer__) */
