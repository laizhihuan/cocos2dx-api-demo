//
//  HpProgress.h
//  GeDou
//
//  Created by zhihuanglai on 15/6/26.
//
//

#ifndef __GeDou__HpProgress__
#define __GeDou__HpProgress__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class HpProgressView : public Node
{
public:
    HpProgressView();
    
    void setBackgroundTexture(const char *pic_name);
    
    void setForegroundTexture(const char *pic_name);
    
    void setTotalProgress(float total);
    
    void setCurrentProgress(float progress);
    
    float getTotalProgress() const;
    
    float getCurrentProgress() const;
    
private:
    
    void setForegroundTextureRect(const Rect &rect);

    Sprite *m_progress_background; //血条背景
    Sprite *m_progress_foreground; //血条
    
    float m_total_progress;
    float m_current_progress;
    float m_scale;
};

#endif /* defined(__GeDou__HpProgress__) */
