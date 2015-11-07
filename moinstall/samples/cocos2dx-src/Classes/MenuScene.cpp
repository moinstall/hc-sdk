//
//  MenuScene.cpp
//  ZombieHero
//
//  Created by HAYER on 04/01/15.
//
//

#include "MenuScene.h"
#include "GameScene.h"
#include "NDKHelper.h"
#include "NativeUtils.h"
#include "Constants.h"
#include "Utility.h"
#include "InstructionScene.h"


#define kTagPlayButton 5001
#define kTagInstructionButton 5004

#define kTagGameCenterButton 5002
#define kTagRateGameButton 5003

#define menuItemMusicOnTag 200
#define menuItemMusicOffTag 201

#define menuItemSoundOnTag 202
#define menuItemSoundOffTag 203




CCScene* MenuScene::scene() {
    CCScene *scene = CCScene::create();
    MenuScene *layer = new MenuScene();
    layer -> init();
    scene -> addChild(layer);
    return scene;
}

MenuScene::MenuScene() {
    
}

bool MenuScene::init() {
    if(!CCLayer::init()) {
        return false;
    }
    
    screenSize = CCDirector::sharedDirector() -> getWinSize();
    return true;
}

void MenuScene::onEnter() {
    CCLayer::onEnter();
    
    if(!Utility::isAdFree()){
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("NO"), KBottomAd);
        prms->setObject(CCString::create("NO"), kTopAd);
        prms->setObject(CCString::create("NO"), kMenu);
        prms->setObject(CCString::create("NO"), kGameOver);
        SendMessageWithParams(string("adFunctionalty"), prms);
    }
    
    Utility::stopMusic();
//    Utility::playMusic(CCString::create(kMusicBackgroundGame));
    
    NDKHelper::AddSelector("MenuSceneSelectors",
                           "resumeBackgroundMusic",
                           callfuncND_selector(MenuScene::resumeBackgroundMusic),
                           this);
    
    CCSprite *bg = CCSprite::createWithSpriteFrameName("background_menu");
    bg->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    addChild(bg);
    
    //----play button---
    CCSprite *playSprite = CCSprite::createWithSpriteFrameName("play");
    CCSprite *playSprite_selected = CCSprite::createWithSpriteFrameName("play");
    playSprite_selected -> setScale(0.975);
    CCMenuItemSprite *playMenuItem = CCMenuItemSprite::create(playSprite,  playSprite_selected, this, menu_selector(MenuScene::menuButtonClicked));
    playMenuItem -> setTag(kTagPlayButton);
    
    CCMenu* playMenu = CCMenu::create(playMenuItem, NULL);
    playMenu -> setPosition(ccp(screenSize.width * 0.5,  screenSize.height * 0.5));
    addChild(playMenu);
    
    //---rate and leaderboard menu----
    CCSprite *rateSprite = CCSprite::createWithSpriteFrameName("rate");
    CCSprite *rateSprite_selected = CCSprite::createWithSpriteFrameName("rate_hold");
    
    CCMenuItemSprite *rateMenuItem = CCMenuItemSprite::create(rateSprite,  rateSprite_selected, this, menu_selector(MenuScene::menuButtonClicked));
    rateMenuItem -> setTag(kTagRateGameButton);
    
    
    CCSprite *leaderboardSprite = CCSprite::createWithSpriteFrameName("leaderboard");
    CCSprite *leaderboardSprite_selected = CCSprite::createWithSpriteFrameName("leaderboard_hold");
    
    CCMenuItemSprite *leaderboardMenuItem = CCMenuItemSprite::create(leaderboardSprite,  leaderboardSprite_selected, this, menu_selector(MenuScene::menuButtonClicked));
    leaderboardMenuItem -> setTag(kTagGameCenterButton);
    
    CCSprite *restoreSprite = CCSprite::create("restore.png");
   
    
    CCMenuItemSprite *restoreSpriteMenuItem = CCMenuItemSprite::create(restoreSprite,  restoreSprite, this, menu_selector(MenuScene::removeAd));
 
    
    //-------music and sound button----
    CCSprite *musicOn = CCSprite::createWithSpriteFrameName("musicOn");
    CCSprite *musicOn_selected = CCSprite::createWithSpriteFrameName("musicOn_hold");
    
    menuItemMusicOn = CCMenuItemSprite::create(musicOn, musicOn_selected, this, menu_selector(MenuScene::musicTapped));
    menuItemMusicOn->setTag(menuItemMusicOnTag);
    
    CCSprite *musicOff = CCSprite::createWithSpriteFrameName("musicOff");
    CCSprite *musicOff_selected = CCSprite::createWithSpriteFrameName("musicOff_hold");
    
    menuItemMusicOff = CCMenuItemSprite::create(musicOff, musicOff_selected, this, menu_selector(MenuScene::musicTapped));
    menuItemMusicOff->setTag(menuItemMusicOffTag);
    
    
    CCMenuItemToggle *musicToggle = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuScene::musicTapped), menuItemMusicOn, menuItemMusicOff, NULL);
    musicToggle->setSelectedIndex((CCUserDefault::sharedUserDefault()->getBoolForKey(keyBackgroundMusic) ? 0 : 1));
    
    CCSprite *soundOn = CCSprite::createWithSpriteFrameName("soundOn");
    CCSprite *soundOn_selected = CCSprite::createWithSpriteFrameName("soundOn_hold");
    
    menuItemSoundOn = CCMenuItemSprite::create(soundOn, soundOn_selected, this, menu_selector(MenuScene::soundTapped));
    menuItemSoundOn->setTag(menuItemSoundOnTag);
    
    CCSprite *soundOff = CCSprite::createWithSpriteFrameName("soundOff");
    CCSprite *soundOff_selected = CCSprite::createWithSpriteFrameName("soundOff_hold");
    
    menuItemSoundOff = CCMenuItemSprite::create(soundOff, soundOff_selected, this, menu_selector(MenuScene::soundTapped));
    menuItemSoundOff->setTag(menuItemSoundOffTag);
    
    
    CCMenuItemToggle *soundToggle = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuScene::soundTapped), menuItemSoundOn, menuItemSoundOff, NULL);
    soundToggle->setSelectedIndex((CCUserDefault::sharedUserDefault()->getBoolForKey(keySound) ? 0 : 1));
    
   
    
    CCMenu* menuMusicOrSound = CCMenu::create(soundToggle , musicToggle , rateMenuItem , leaderboardMenuItem, restoreSpriteMenuItem, NULL);
    menuMusicOrSound->alignItemsHorizontallyWithPadding(screenSize.width * 0.03);
    menuMusicOrSound->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.085));
    this->addChild(menuMusicOrSound);
    
    
    //-----------
    this->setKeypadEnabled(true);
}

void MenuScene::removeAd(){
    NDKHelper::AddSelector("MenuSceneSelectors",
                           "purchasedSuccessful",
                           callfuncND_selector(MenuScene::purchasedSuccessful),
                           this);
    CCDictionary* prms = CCDictionary::create();
    SendMessageWithParams(string("restorePurchase"), prms);
}

void MenuScene::purchasedSuccessful(CCNode *sender, void *data){
    Utility::setAdFree();
    CCDictionary* prms = CCDictionary::create();
    prms->setObject(CCString::create("NO"), KBottomAd);
    prms->setObject(CCString::create("NO"), kTopAd);
    prms->setObject(CCString::create("NO"), kMenu);
    prms->setObject(CCString::create("NO"), kGameOver);
    SendMessageWithParams(string("adFunctionalty"), prms);
}

void  MenuScene::soundTapped(CCObject *sender) {
    Utility::playSound(CCString::create(kSoundButton));
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    CCMenuItemToggle *toggleItem = (CCMenuItemToggle*)sender;
    if (toggleItem->selectedItem() == menuItemSoundOn) {
        defaults->setBoolForKey(keySound, true);
    } else if (toggleItem->selectedItem() == menuItemSoundOff) {
        defaults->setBoolForKey(keySound, false);
    }
}



void MenuScene::musicTapped(CCObject *sender){
    Utility::playSound(CCString::create(kSoundButton));
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    CCMenuItemToggle *toggleItem = (CCMenuItemToggle*)sender;
    if (toggleItem->selectedItem() == menuItemMusicOn) {
        defaults->setBoolForKey(keyBackgroundMusic, true);
    } else if (toggleItem->selectedItem() == menuItemMusicOff) {
        defaults->setBoolForKey(keyBackgroundMusic, false);
    }
    Utility::playOrPauseMusic(CCString::create(kMusicBackgroundGame));
}


void MenuScene::menuButtonClicked(CCObject *sender) {
    
    Utility::playSound(CCString::create(kSoundButton));
    
    CCMenuItemLabel* menuItem = (CCMenuItemLabel *) sender;
    
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    
    if(menuItem -> getTag() == kTagPlayButton) {
        
        int noOfCall = CCUserDefault::sharedUserDefault()->getIntegerForKey(kCallRate, 1);
        if(noOfCall <= 5){
            noOfCall++;
            CCUserDefault::sharedUserDefault()->setIntegerForKey(kCallRate, noOfCall);
            CCDirector::sharedDirector() -> replaceScene(InstructionScene::scene());
        }else{
            CCDirector::sharedDirector() -> replaceScene(GameScene::scene());
        }
    }
    else if (menuItem -> getTag() == kTagInstructionButton) {
        
//        defaults -> setBoolForKey(kPlayingFirstTimeKey, true);
//        CCDirector::sharedDirector() -> replaceScene(InstructionScene::scene());
    }
    else if (menuItem -> getTag() == kTagGameCenterButton) {
        
        if(Utility::isGooglePlay){
            NativeUtils::showLeaderboards();
        }else{
            SendMessageWithParams(string("openLeaderBoard"), NULL);
        }
    }
    else if (menuItem -> getTag() == kTagRateGameButton) {
                SendMessageWithParams(string("rateButtonClicked"), NULL);
    }
}

void MenuScene::keyBackClicked(){
    NDKHelper::AddSelector("MenuSceneSelectors",
                           "resetListener",
                           callfuncND_selector(MenuScene::resetListener),
                           this);
    SendMessageWithParams(string("quitGame"), NULL);
}

void MenuScene::resetListener(CCNode *sender, void *data){
    
    CCDirector::sharedDirector()->end();
}

void MenuScene::resumeBackgroundMusic(){
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    Utility::playOrPauseMusic(CCString::create(kMusicBackgroundGame));
}


void MenuScene::onExit() {
    
    if(!Utility::isAdFree()){
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("NO"), KBottomAd);
        prms->setObject(CCString::create("NO"), kTopAd);
        prms->setObject(CCString::create("NO"), kMenu);
        prms->setObject(CCString::create("NO"), kGameOver);
        SendMessageWithParams(string("adFunctionalty"), prms);
    }

    
    NDKHelper::RemoveSelectorsInGroup("MenuSceneSelectors");
    
    removeAllChildrenWithCleanup(true);
    CCLayer::onExit();
}

MenuScene::~MenuScene() {
    
}
