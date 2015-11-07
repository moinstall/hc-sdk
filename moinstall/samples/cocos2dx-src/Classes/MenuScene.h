//
//  MenuScene.h
//  ZombieHero
//
//  Created by HAYER on 04/01/15.
//
//

#ifndef __ZombieHero__MenuScene__
#define __ZombieHero__MenuScene__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public CCLayer {
    
    CCSize screenSize;
    CCMenu* mainMenu;
    
    CCMenuItemSprite *menuItemMusicOn;
    CCMenuItemSprite *menuItemMusicOff;
    CCMenuItemSprite *menuItemSoundOn;
    CCMenuItemSprite *menuItemSoundOff;
    
public:
    
    MenuScene();
    ~MenuScene();
    
    static CCScene* scene();
    bool init();
    virtual void onEnter();
    virtual void onExit();
    
    void menuButtonClicked(CCObject* sender);
    
    virtual void keyBackClicked();
    void resetListener(CCNode *sender, void *data);
    
    void soundTapped(CCObject *sender) ;
    void musicTapped(CCObject *sender);
    void resumeBackgroundMusic();
    
    void purchasedSuccessful(CCNode *sender, void *data);
    
    void removeAd();
};


#endif /* defined(__ZombieHero__MenuScene__) */
