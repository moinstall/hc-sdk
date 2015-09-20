//
//  GameOverLayer.h
//  slingshot
//
//  Created by HAYER on 25/06/14.
//
//

#ifndef __slingshot__GameOverLayer__
#define __slingshot__GameOverLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class GameOverLayer : public CCLayer {
    
    CCSize screenSize;
    
    CCMenu* menu;
    GameScene* gamelayer;
    
    bool shouldShowNewRecordText;

public:
    
    GameOverLayer();
    ~GameOverLayer();
    
    virtual bool initWithGameLayer(GameScene*);
    
    virtual void onExit();
    virtual void onEnter();
    
    void postToGameCenter();
    
    void buttonClicked(CCObject* sender);
    
    void purchasedSuccessful(CCNode *sender, void *data);
    
    void removeAd();
};

#endif /* defined(__slingshot__GameOverLayer__) */
