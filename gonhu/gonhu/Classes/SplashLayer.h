//
//  SplashLayer.h
//  gonhu
//
//  Created by zhihuanglai on 15/6/15.
//
//

#ifndef __gonhu__SplashLayer__
#define __gonhu__SplashLayer__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class SplashLayer : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(SplashLayer);

private:
    Sprite* logoSprite;
    //资源加载
    void loadingTextureCallback(Texture2D * texture);
    void loadingAudio();
    
    /**
     *  切换场景
     *
     *  @param dt
     */
    void nextScene(float dt);
    
    void onExit();
    
    void initUserData();
    
    int m_iNumOfLoad;
    
    std::thread* _loadingAudioThread;
};

#endif /* defined(__gonhu__SplashLayer__) */
