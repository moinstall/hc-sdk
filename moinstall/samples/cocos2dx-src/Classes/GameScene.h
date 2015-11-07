//
//  GameScene.h
//  ZombieHero
//
//  Created by HAYER on 04/01/15.
//
//

#ifndef __ZombieHero__GameScene__
#define __ZombieHero__GameScene__

#include <iostream>
#include "cocos2d.h"

#include "LevelHelperLoader.h"
#include "GameObjects.h"
#include "HUDLayer.h"
USING_NS_CC;

class HUDLayer;

class GameScene : public CCLayer {
    bool touchActive;
    CCSize screenSize;
    int gameId;
    
    b2World* world;
    b2Vec2 gravity;
    LHParallaxNode * parallax;
    LevelHelperLoader* loader;
    
    CCArray* arrayPlateform, *progressArray, *redDotArray; 
    float time ;
    bool brainAppear , flipMood;
    Zombie* zombie;
    CCSprite *brainSprites;
public:
    HUDLayer *hudLayer;
    bool zombieCollisionStart;
    CCMoveBy *moveOut_1;
    float newPosX;
     CCProgressTimer* stickProgressBar;
    float posStick ;
    bool zombieRun;
    bool shouldEnableTouch;    
    
    static CCScene* scene();
    
    GameScene();
    ~GameScene();
    
    virtual bool init();
    
    virtual void onExit();
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) ;
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;
   
    void addPlateform();
    void increaseStick();
    void stopAndDecline();
    void makeZombieRun();
    float checkGameStatus();
    
    void addYellowCenter(float posX, CCPoint platformPos);
    void addBrain(float posX , CCPoint platformPos);
    
    void callgameOver();
    
    void resumeBackgroundMusic();
    
    void movePlatform();
    void zombieMove(float);
    void dotMove(float);
    void brainMove(float);
    void progressBarMove(float);
    
    void removeFirstPlatform();
    
    virtual void update(float dt);
    
    void addZombie();
    
    void checkCollisionWithYellow();
    void stopAllObjectsAction();
    
    void setSpeedZero();
    void setSpeedNormal();
    
};


#endif /* defined(__ZombieHero__GameScene__) */
