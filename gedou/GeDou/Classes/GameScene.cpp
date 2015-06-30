//
//  GameScene.cpp
//  GeDou
//
//  Created by zhihuanglai on 15/6/18.
//
//

#include "GameScene.h"

bool GameScene::isRectCollision(cocos2d::Rect rect1, cocos2d::Rect rect2)
{
    //矩形1中心点和宽高
    float x1 = rect1.origin.x;
    float y1 = rect1.origin.y;
    float w1 = rect1.size.width;
    float h1 = rect1.size.height;
    
    float x2 = rect2.origin.x;
    float y2 = rect2.origin.y;
    float w2 = rect2.size.width;
    float h2 = rect2.size.height;
    
    if (x1 + w1 * 0.5 < x2 - w2 * 0.5) {
        return false;
    }
    else if (x1 - w1 * 0.5 > x2 + w2 * 0.5) {
        return false;
    }
    else if (y1 + h1 * 0.5 < y2 - h2*0.5) {
        return false;
    }
    else if (y1 - h1 * 0.5 > y2 + h2 * 0.5)
    {
        return false;
    }
    
    return true;
}


Scene* GameScene::createScene()
{
    Scene *scene = Scene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //添加攻击按钮
    attackBtn = cocos2d::extension::ControlButton::create("Attack", "fonts/Marker Felt.ttf", 30);
    attackBtn->setPosition(Vec2(visibleSize.width-200,100));
    this->addChild(attackBtn,7);
    
    //添加游戏背景
    //Sprite *pSprite = Sprite::create("background_1.jpg");
    //pSprite->setPosition(Vec2(visibleSize.width/2+origin.x, visibleSize.height/2 + origin.y));
    //this->addChild(pSprite,0);
    
    //添加地图
    node_map = IMap::create();
    node_map->initMap("12.png", visibleSize);
    this->addChild(node_map,0);
    
    //添加英雄精灵
    hero = Hero::create();
    hero->initHeroSprite("hero.png");
    hero->setPosition(Vec2(300, 100));
    this->addChild(hero,1);
    //hero->setAnimation("run_animation.plist", "run_animation.png", 8, true);
    
    //添加怪物
    monster_1 = Monster::create();
    monster_1->initMonsterSprite("monster.png","xue_back.png","xue_fore.png");
    monster_1->setPosition(Vec2(visibleSize.width-100, visibleSize.height/2-100));
    //this->addChild(monster_1,1);
    node_map->addChild(monster_1);
    monster_1->startListen(hero, node_map);
    
    //添加摇杆
    rocker = HRocker::createHRocker("Direction_bt.png", "Direction_bc.png", Vec2(110,60));
    this->addChild(rocker,2);
    rocker->startRocker(true);
    
    //设置英雄血条
    m_progress_view = new HpProgressView();
    m_progress_view->setPosition(Vec2(150, 450));
    m_progress_view->setScale(2.2f);
    m_progress_view->setBackgroundTexture("xue_back.png");
    m_progress_view->setForegroundTexture("xue_fore.png");
    m_progress_view->setTotalProgress(100.0f);
    m_progress_view->setCurrentProgress(100.0f);
    this->addChild(m_progress_view,2);
    
    //添加血条样式
    Sprite *xuekuang = Sprite::create("kuang.png");
    xuekuang->setPosition(Vec2(m_progress_view->getPositionX(), m_progress_view->getPositionY()));
    Sprite *touxiang = Sprite::create("touxiang.png");
    touxiang->setPosition(m_progress_view->getPositionX()-120,m_progress_view->getPositionY());
    this->addChild(touxiang,2);
    this->addChild(xuekuang,2);
    
    
    //启动update事件
    this->scheduleUpdate();
    
    return true;
}

void GameScene::update(float delta)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    switch (rocker->rockerDirection) {
        case 1:
            hero->setAnimation("hero_run", 8, rocker->rockerRun);
            //向右走
            //不让精灵超出右边，
            if (hero->getPositionX()<=visibleSize.width - 8) {
                if (!hero->judgePostion(visibleSize) || node_map->judgeMap(hero, visibleSize)) {
                    hero->setPosition(Vec2(hero->getPosition().x+2, hero->getPosition().y));
                }
                node_map->moveMap(hero, visibleSize);
            }
            //hero->setPosition(Vec2(hero->getPosition().x+1,hero->getPosition().y));
            break;
        case 2:
            hero->setAnimation("hero_run", 8, rocker->rockerRun);
            //向上走
            hero->setPosition(Vec2(hero->getPosition().x,hero->getPosition().y+2));
            break;
        case 3:
            hero->setAnimation("hero_run", 8, rocker->rockerRun);
            //向左走
            if(hero->getPositionX() >= 8) {
                hero->setPosition(Vec2(hero->getPosition().x-1,hero->getPosition().y));
            }
            break;
        case 4:
            hero->setAnimation("hero_run", 8, rocker->rockerRun);
            //向下走
            hero->setPosition(Vec2(hero->getPosition().x,hero->getPosition().y-1));
            break;
        default:
            //停止所有的动画和运动
            hero->stopAnimation();
            break;
    }
    
    //攻击
    if (attackBtn->isHighlighted()) {
        hero->attackAnimation("hero_attack", 6, rocker->rockerRun);
        log("attack----->");
    }
    
    if (hero -> isAttack) {
        log("hero attack ....");
        
        //怪物和英雄应该在一个差不多的水平高度上，攻击才有效
        bool isValidAttack = abs(hero->getPositionY() - monster_1->getPositionY()) < 30;
        
        if (isValidAttack) {
            
            log("is valid attack");
            
            auto hero_rect=Rect::Rect(hero->getPositionX(),hero->getPositionY(), hero->getContentSize().width-70, hero->getContentSize().height-30);
            auto monster_rect=Rect::Rect(monster_1->getPositionX(),monster_1->getPositionY(),hero->getContentSize().width-30,monster_1->getContentSize().height - 20);
            
            if (this->isRectCollision(hero_rect,monster_rect)) {
                log("hero attack ....monster");
                //怪物受伤
                monster_1->hurtAnimation("monster_run",6,monster_1->monsterDirection);
            }
            
        }
    }
    
}