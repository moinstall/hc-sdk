//
//  GameObjects.h
//  ZombieHero
//
//  Created by HAYER on 04/01/15.
//
//

#ifndef __ZombieHero__GameObjects__
#define __ZombieHero__GameObjects__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class GameScene;

class Zombie : public CCSprite {
    
    CCSize screenSize;
    GameScene* gamelayer;
    
public:
    
    bool shouldFallDown;
    
    Zombie();
    virtual bool init(GameScene*);
    void run();
    void stopIt();
    void fallDown();
    ~Zombie();
};

class Plateform : public CCSprite {
    
    CCSize screenSize;
    GameScene* gamelayer;
    
public:
    
    Plateform();
    virtual bool init(GameScene*);
    ~Plateform();
};

class GameObjects {
    
public:
    static float getRandomScaleXPlateform();
    static ccColor3B getRandomColor();
    static CCAnimate* animate(const std::string& stringSequence, int totalFrames, float animTime);
};

#endif /* defined(__ZombieHero__GameObjects__) */
