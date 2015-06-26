//
//  HpProgress.cpp
//  GeDou
//
//  Created by zhihuanglai on 15/6/26.
//
//

#include "HpProgress.h"

HpProgressView::HpProgressView()
    :m_progress_background(NULL)
    ,m_progress_foreground(NULL)
    ,m_total_progress(0.0f)
    ,m_current_progress(0.0f)
    ,m_scale(1.0f)
{
    
}

void HpProgressView::setBackgroundTexture(const char *name)
{
    m_progress_background = Sprite::create(name);
    this->addChild(m_progress_background);
}

void HpProgressView::setForegroundTexture(const char *name)
{
    m_progress_foreground = Sprite::create(name);
    m_progress_foreground->setAnchorPoint(Vec2(0.0f, 0.5f));
    m_progress_foreground->setPosition(Vec2(-m_progress_foreground->getContentSize().width * 0.5f, 0));
    this->addChild(m_progress_foreground);
}

void HpProgressView::setTotalProgress(float total)
{
    if (m_progress_foreground == NULL) {
        return;
    }
    m_scale = m_progress_foreground->getContentSize().width / total;
    m_total_progress = total;
}

void HpProgressView::setCurrentProgress(float progress)
{
    if (m_progress_foreground == NULL) {
        return;
    }
    
    if (progress < 0.0f) {
        progress = 0.0f;
    }
    
    if (progress > m_total_progress) {
        progress = m_total_progress;
    }
    
    m_current_progress = progress;
    float rectWidth = progress * m_scale;
    const Vec2 from = m_progress_foreground->getTextureRect().origin;
    const Rect rect = Rect(from.x, from.y, rectWidth, m_progress_foreground->getContentSize().height);
    setForegroundTextureRect(rect);
}

void HpProgressView::setForegroundTextureRect(const Rect &rect)
{
    m_progress_foreground->setTextureRect(rect);
}

float HpProgressView::getTotalProgress() const
{
    return m_total_progress;
}

float HpProgressView::getCurrentProgress() const
{
    return m_current_progress;
}



