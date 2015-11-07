//
//  GameObjects.cpp
//  ZombieHero
//
//  Created by HAYER on 04/01/15.
//
//

#include "GameObjects.h"
#include "Utility.h"
#include "GameScene.h"
#include "Constants.h"


#pragma mark- Zombie

Zombie::Zombie() {
    shouldFallDown = false;
}

bool Zombie::init(GameScene* pGamelayer) {
    gamelayer = pGamelayer;
    screenSize = CCDirector::sharedDirector() -> getWinSize();
    

    if(!CCSprite::initWithSpriteFrameName("zombie_anim_2")) {
        return false;
    }
    
    return true;
}

void Zombie::run() {
    CCAnimate* anim = GameObjects::animate("zombie_anim_", 4, 0.1);
    this -> runAction(CCRepeatForever::create(anim));
}

void Zombie::stopIt() {
    this -> stopAllActions();
    this -> setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("zombie_anim_2"));
}

void Zombie::fallDown() {
    if(shouldFallDown) {
         Utility::playSound(CCString::create(kSoundfalling));
        CCRotateBy* rotate = CCRotateBy::create(0.1, 90);
        gamelayer->stickProgressBar -> runAction(rotate);
        
        CCMoveTo* move = CCMoveTo::create(0.1, ccp(this->getPositionX(), screenSize.height * -0.2));
        CCCallFunc* call = CCCallFunc::create(gamelayer, callfunc_selector(GameScene::callgameOver));
        CCSequence* seq = CCSequence::create(move, call, NULL);
        this -> runAction(seq);
    }
}

Zombie::~Zombie() {
    
}

#pragma mark- Plateform

Plateform::Plateform() {
    
}

bool Plateform::init(GameScene* pGamelayer) {
    gamelayer = pGamelayer;
    
    if(!CCSprite::initWithSpriteFrameName("platform")) {
        return false;
    }
    
    return true;
}

Plateform::~Plateform() {
    
}

#pragma mark- Game Objects common

float GameObjects::getRandomScaleXPlateform() {
    return Utility::randomFloatBetween(0.4, 0.6);
}

ccColor3B GameObjects::getRandomColor() {
    
    unsigned int R = 0;//Utility::randomNumberBetween(0, 255);
    unsigned int G = 0;//Utility::randomNumberBetween(0, 255);
    unsigned int B = 0;//Utility::randomNumberBetween(0, 255);
    
    ccColor3B randomColor = {static_cast<GLubyte>(R), static_cast<GLubyte>(G), static_cast<GLubyte>(B)};
    return randomColor;
}

CCAnimate* GameObjects::animate(const std::string& stringSequence, int totalFrames, float animTime) {
    
    CCArray* arrayAnimFrames = new CCArray();
    
    for(int counter = 0; counter < totalFrames; counter++){
        
        CCString* stringFrameName = CCString::createWithFormat("%s%d", stringSequence.c_str(), counter);
        
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(stringFrameName -> getCString());
        arrayAnimFrames->addObject(frame);
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(arrayAnimFrames, animTime);
    CCAnimate *animate = CCAnimate::create(animation);
    return animate;
}

