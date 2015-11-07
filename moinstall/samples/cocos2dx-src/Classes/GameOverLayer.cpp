//
//  GameOverLayer.cpp
//  slingshot
//
//  Created by HAYER on 25/06/14.
//
//

#include "GameOverLayer.h"
#include "MenuScene.h"
#include "Constants.h"
#include "NDKHelper.h"
#include "GameScene.h"
#include "InstructionScene.h"
#include "Utility.h"
#include "NativeUtils.h"

#define kTagMenuItemRestart 2501
#define kTagMenuItemHome 2502
#define kTagMenuItemRate 2503
#define kTagMenuItemShare 2504

#define menuRemoveAdsTag 204

GameOverLayer::GameOverLayer() {
    shouldShowNewRecordText = false;
}

bool GameOverLayer::initWithGameLayer(GameScene* pgamelayer) {
    if(!CCLayer::init()) {
        return false;
    }
    gamelayer = pgamelayer;
    screenSize = CCDirector::sharedDirector() -> getWinSize();
    return true;
}

void GameOverLayer::onEnter() {
    
    CCLayer::onEnter();

    NativeUtils::showAd();

    //---sound/music---
//    Utility::stopMusic();
//    Utility::playSound(CCString::create(kSoundGameOver));
   
    
    //----set best ----
    int bestScore = CCUserDefault::sharedUserDefault() -> getIntegerForKey(keyBestScore, 0);
    int currentScore = CCUserDefault::sharedUserDefault() -> getIntegerForKey(keyCurrentScore, 0);

    if(currentScore > bestScore) {
        CCUserDefault::sharedUserDefault() -> setIntegerForKey(keyBestScore,currentScore);
        bestScore = gamelayer->hudLayer->score;
    }
    
    postToGameCenter();

    
    //----ads call----
    if(!Utility::isAdFree()){
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("NO"), KBottomAd);
        prms->setObject(CCString::create("NO"), kTopAd);
        prms->setObject(CCString::create("NO"), kMenu);
        prms->setObject(CCString::create("YES"), kGameOver);
        SendMessageWithParams(string("adFunctionalty"), prms);
    }
    
    
    CCSprite* bg = CCSprite::createWithSpriteFrameName("transparent_bg");
    bg -> setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.5));
    this -> addChild(bg);

    //----level complete/failed-----
//    CCLabelBMFont* gameover = CCLabelBMFont::create("Game Over", kFontFile);
//    gameover -> setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.75));
//    gameover -> setScale(0.75);
//    addChild(gameover);
    CCSprite* gameover = CCSprite::createWithSpriteFrameName("game_over_text");
    gameover -> setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.825));
    this -> addChild(gameover);

    //---score holder--
    CCSprite* spriteScoreHolder = CCSprite::createWithSpriteFrameName("score_holder");
    spriteScoreHolder -> setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.575));
    this -> addChild(spriteScoreHolder);

    //----level/total score----
    CCString* scoreString = CCString::createWithFormat("%d",currentScore);
    CCLabelBMFont* yourScorLabel = CCLabelBMFont::create(scoreString->getCString(), kFontFile);
    yourScorLabel -> setPosition(ccp(spriteScoreHolder->getContentSize().width * 0.5, spriteScoreHolder->getContentSize().height * 0.625));
    spriteScoreHolder -> addChild(yourScorLabel);
    yourScorLabel -> setColor(ccBLACK);
    yourScorLabel -> setScale(0.7);

    CCString* bestScoreString = CCString::createWithFormat("%d", bestScore);
    CCLabelBMFont* bestScoreLabel = CCLabelBMFont::create(bestScoreString->getCString(), kFontFile);
    bestScoreLabel -> setPosition(ccp(spriteScoreHolder->getContentSize().width * 0.5, spriteScoreHolder->getContentSize().height * 0.175));
    spriteScoreHolder -> addChild(bestScoreLabel);
    bestScoreLabel -> setColor(ccBLACK);
    bestScoreLabel -> setScale(0.7);

    if(shouldShowNewRecordText) {
        
//        CCSprite *newRecord = CCSprite::createWithSpriteFrameName("new_best_text");
//        newRecord -> setPosition(ccp(spriteScoreHolder->getContentSize().width * 0.75, spriteScoreHolder->getContentSize().height * 0.435));
//        newRecord -> setScale(1.4);
//        spriteScoreHolder -> addChild(newRecord);
//        
//        CCBlink* blinkACtion = CCBlink::create(2.0, 5);
//        newRecord -> runAction(blinkACtion);
    }
    
    //----menu--------
    //----restart button---
    CCSprite *restartSprite = CCSprite::createWithSpriteFrameName("restart");
    CCSprite *restartSprite_selected = CCSprite::createWithSpriteFrameName("restart_hold");
    CCMenuItemSprite *restartMenuItem = CCMenuItemSprite::create(restartSprite,  restartSprite_selected, this, menu_selector(GameOverLayer::buttonClicked));
    restartMenuItem -> setTag(kTagMenuItemRestart);
    
    //----menu button---
    CCSprite *menuSprite = CCSprite::createWithSpriteFrameName("home");
    CCSprite *menuSprite_selected = CCSprite::createWithSpriteFrameName("home_hold");
    CCMenuItemSprite *mainMenuItem = CCMenuItemSprite::create(menuSprite,  menuSprite_selected, this, menu_selector(GameOverLayer::buttonClicked));
    mainMenuItem -> setTag(kTagMenuItemHome);
    
    //----rate button---
    CCSprite *rateSprite = CCSprite::createWithSpriteFrameName("rate");
    CCSprite *rateSprite_selected = CCSprite::createWithSpriteFrameName("rate_hold");
    CCMenuItemSprite *rateMenuItem = CCMenuItemSprite::create(rateSprite,  rateSprite_selected, this, menu_selector(GameOverLayer::buttonClicked));
    rateMenuItem -> setTag(kTagMenuItemRate);
    
    CCMenu* menu = CCMenu::create(restartMenuItem, mainMenuItem, rateMenuItem, NULL);
    menu -> setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.275));
    menu -> alignItemsHorizontallyWithPadding(screenSize.width * 0.05);
    addChild(menu);
    
    CCSprite *restore = CCSprite::create("no_ads.png");
    CCSprite *restore_selected = CCSprite::create("no_ads_hold.png");
    restore_selected->setScale(0.95);
    
    CCMenuItemSprite *restoreMenuItem = CCMenuItemSprite::create(restore,  restore_selected, this, menu_selector(GameOverLayer::removeAd));
    restoreMenuItem -> setTag(menuRemoveAdsTag);
    
    CCMenu *removeAdsMenu = CCMenu::create(restoreMenuItem , NULL);
    removeAdsMenu->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.1));
    this->addChild(removeAdsMenu);
    

    //----share menu----
//    if(!Utility::isGooglePlay()) {
//        CCSprite *shareSprite = CCSprite::createWithSpriteFrameName("share");
//        CCSprite *shareSprite_selected = CCSprite::createWithSpriteFrameName("share_hold");
//        CCMenuItemSprite *shareMenuItem = CCMenuItemSprite::create(shareSprite,  shareSprite_selected, this, menu_selector(GameOverLayer::buttonClicked));
//        shareMenuItem -> setTag(kTagMenuItemShare);
//        shareMenuItem -> setScale(0.75);
//        CCMenu * menuShare = CCMenu::create(shareMenuItem, NULL);
//        menuShare -> setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.1));
//        addChild(menuShare);
//    }
}

void GameOverLayer::removeAd(){
    NDKHelper::AddSelector("GameOverSceneSelectors",
                           "purchasedSuccessful",
                           callfuncND_selector(GameOverLayer::purchasedSuccessful),
                           this);
    CCDictionary* prms = CCDictionary::create();
    SendMessageWithParams(string("startPuchaseFlow"), prms);
}

void GameOverLayer::purchasedSuccessful(CCNode *sender, void *data){
    Utility::setAdFree();
    CCDictionary* prms = CCDictionary::create();
    prms->setObject(CCString::create("NO"), KBottomAd);
    prms->setObject(CCString::create("NO"), kTopAd);
    prms->setObject(CCString::create("NO"), kMenu);
    prms->setObject(CCString::create("NO"), kGameOver);
    SendMessageWithParams(string("adFunctionalty"), prms);
}

void GameOverLayer::postToGameCenter() {
    
    int totalScore = CCUserDefault::sharedUserDefault() -> getIntegerForKey(keyBestScore, 0);
    Utility::post(totalScore, leaderboard_iTunes_TotalTimerSurvived, leaderboard_GooglePlay_TotalTimerSurvived);
    
//    int counterAttempt = CCUserDefault::sharedUserDefault()->getIntegerForKey(keyAttemptNumber, 0);
//    Utility::post(counterAttempt, leaderboard_iTunes_TotalAttempts, leaderboard_GooglePlay_TotalAttempts);
}

void GameOverLayer::buttonClicked(CCObject *sender) {
    
    Utility::playSound(CCString::create(kSoundButton));
    
    CCMenuItemLabel* menuItem = (CCMenuItemLabel *) sender;
    
    if (menuItem -> getTag() == kTagMenuItemRestart) {
        
        int noOfCall = CCUserDefault::sharedUserDefault()->getIntegerForKey(kCallRate, 1);
        if(noOfCall <= 5){
            noOfCall++;
            CCUserDefault::sharedUserDefault()->setIntegerForKey(kCallRate, noOfCall);
            CCDirector::sharedDirector() -> replaceScene(InstructionScene::scene());
            
        }else{
            CCDirector::sharedDirector() -> replaceScene(GameScene::scene());
        }
    }
    else if (menuItem -> getTag() == kTagMenuItemHome) {
        
        CCDirector::sharedDirector() -> replaceScene(MenuScene::scene());
    }
    else if (menuItem -> getTag() == kTagMenuItemRate) {
        
        SendMessageWithParams(string("rateButtonClicked"), NULL);
    }
    else if (menuItem -> getTag() == kTagMenuItemShare) {
        
        CCDictionary* prms = CCDictionary::create();
        int totalScore = CCUserDefault::sharedUserDefault() -> getIntegerForKey(keyBestScore, 0);
        CCString *score = CCString::createWithFormat("%d", totalScore);
        prms -> setObject(score, "game_score");
        
        int counterAttempt = CCUserDefault::sharedUserDefault()->getIntegerForKey(keyAttemptNumber, 0);
        CCString *attempts = CCString::createWithFormat("%d", counterAttempt);
        prms -> setObject(attempts, "game_attempt");
        
        //        SendMessageWithParams(string("shareToSocialNetwork"), prms);
    }
}

void GameOverLayer::onExit() {
    
     NDKHelper::RemoveSelectorsInGroup("GameOverSceneSelectors");
    
    if(!Utility::isAdFree()){
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("NO"), KBottomAd);
        prms->setObject(CCString::create("NO"), kTopAd);
        prms->setObject(CCString::create("NO"), kMenu);
        prms->setObject(CCString::create("NO"), kGameOver);
        SendMessageWithParams(string("adFunctionalty"), prms);
    }
    
    removeAllChildrenWithCleanup(true);
    CCLayer::onExit();
}

GameOverLayer::~GameOverLayer() {

}
