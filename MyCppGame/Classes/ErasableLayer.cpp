//
//  ErasableLayer.cpp
//  MyCppGame
//
//  Created by zhihuanglai on 15/5/4.
//
//

#include "ErasableLayer.h"

ErasableLayer::ErasableLayer():isErasable_(true) {}

ErasableLayer::~ErasableLayer()
{
    CC_SAFE_RELEASE(layer_);
    CC_SAFE_RELEASE(erasa_);
}

ErasableLayer* ErasableLayer::create(const char* layerPath, const char* erasaPath)
{
    Sprite* layer = Sprite::create(layerPath);
    Sprite* erasa = Sprite::create(erasaPath);
    
    ErasableLayer* ret = new ErasableLayer;
    if(ret->init(layer, erasa)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

ErasableLayer* ErasableLayer::create(Node *layer, Sprite* erasa)
{
    ErasableLayer* ret = new ErasableLayer;
    if(ret->init(layer, erasa)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

ErasableLayer* ErasableLayer::create(Node *layer, const char* erasaPath)
{
    //Sprite* layer = Sprite::create(layerPath);
    Sprite* erasa = Sprite::create(erasaPath);
    
    ErasableLayer* ret = new ErasableLayer;
    if(ret->init(layer, erasa)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

ErasableLayer* ErasableLayer::create(const char* layerPath, Sprite* erasa)
{
    Sprite* layer = Sprite::create(layerPath);
    //Sprite* erasa = Sprite::create(erasaPath);
    
    ErasableLayer* ret = new ErasableLayer;
    if(ret->init(layer, erasa)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool ErasableLayer::init(Node *layer, Sprite* erasa){
    
    if (! MyCommonLayer::init())
    {
        return false;
    }
    
    layer_ = layer;
    erasa_ = erasa;
    
    layer_->retain();
    erasa_->retain();
    
    this->setContentSize(layer_->getContentSize());
    
    // 设置颜色混合模式
    BlendFunc erasaBf = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA }; //源因子：值为0，橡皮擦颜色为透明；目标因子：目标颜色透明度减去源颜色的透明度
    erasa_->setBlendFunc(erasaBf);
    
    auto size = layer_->getContentSize();
    rt_ = RenderTexture::create(size.width, size.height);
    rt_->setAnchorPoint(Vec2(0, 0));
    rt_->setPosition(Vec2(size.width/2, size.height/2));
    this->addChild(rt_);
    
    clear();
    
    schedule(schedule_selector(ErasableLayer::tick));
    
    // 触摸事件
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(ErasableLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ErasableLayer::onTouchesMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ErasableLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    listener->setSwallowTouches(false);
    
    return true;
}


void ErasableLayer::tick(float){
    if (!isErasable_)
    {
        return;
    }
    
    // 设置源颜色alpha值为最大值，目标颜色alpha值减去源颜色alpha值后就为0了，混合出来的效果就变透明了，这样就实现了橡皮擦效果了。
    erasa_->setOpacity(255);
    
    // 更新RenderTexture
    rt_->begin();
    
    // 绘制
    erasa_->visit();
    
    rt_->end();
}

void ErasableLayer::clear(){
    layer_->setAnchorPoint(Vec2(0, 0));
    layer_->setPosition(Vec2(0, 0));
    
    rt_->begin();
    layer_->visit();
    rt_->end();
}

void ErasableLayer::setErasable(bool flag){
    isErasable_ = flag;
}

bool ErasableLayer::onTouchBegan(Touch* touch, Event  *event)
{
    erasa_->setPosition(this->convertToNodeSpace(touch->getLocation()));
    return true;
}
void ErasableLayer::onTouchesMoved(Touch* touch, Event  *event){
    erasa_->setPosition(this->convertToNodeSpace(touch->getLocation()));
}
void ErasableLayer::onTouchEnded(Touch* touch, Event  *event)
{
    erasa_->setPosition(this->convertToNodeSpace(touch->getLocation()));
}



