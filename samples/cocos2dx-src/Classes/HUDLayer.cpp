//
//  HUDLayer.cpp
//  BabyKiss
//
//  Created by HAYER on 10/07/14.
//
//

#include "HUDLayer.h"

#include "GameScene.h"
#include "Constants.h"

HUDLayer::HUDLayer() {
    brain = 0;
    score = 0;
}

bool HUDLayer::initWithGameLayer(GameScene* pGameLayer) {
    if(!CCLayer::init()) {
        return false;
    }
    
    gamelayer = pGameLayer;
    
    screenSize = CCDirector::sharedDirector() -> getWinSize();
    
      //----pause button---
//    CCSprite *pauseSprite = CCSprite::createWithSpriteFrameName("pause");
//    CCSprite *pauseSprite_selected = CCSprite::createWithSpriteFrameName("pause_hold");
//    
//    CCMenuItemSprite *pauseMenuItem = CCMenuItemSprite::create(pauseSprite,  pauseSprite_selected, this, menu_selector(HUDLayer::pauseButtonClicked));
//    pauseMenuItem -> setScale(1);
//   
//    
//    pauseMenu = CCMenu::create(pauseMenuItem, NULL);
//    pauseMenu ->setPosition(ccp(screenSize.width * 0.1,  screenSize.height * 0.92));
//    addChild(pauseMenu);
//    pauseMenu->setVisible(true);
    
    CCSprite *brainSprite = CCSprite::createWithSpriteFrameName("brain");
    brainSprite->setScale(0.5);
    brainSprite->setPosition(ccp(brainSprite->getContentSize().width/2 - brainSprite->getScaleX(), screenSize.height * 0.95));
    addChild(brainSprite);
    
    CCString* brainLabel_string = CCString::createWithFormat("x %d", brain);
    brainLabel = CCLabelBMFont::create(brainLabel_string->getCString(), kFontFile);
    brainLabel->setPosition(ccp(brainSprite->getPositionX() + brainSprite->getContentSize().width * 0.55, screenSize.height * 0.938));
    brainLabel -> setAlignment(kCCTextAlignmentLeft);
    brainLabel -> setScale(0.3);
    brainLabel -> setAnchorPoint(ccp(0.5, 0));
    addChild(brainLabel);
    
    
        //---score----
    CCString* scoreString = CCString::createWithFormat("%d", score);
    scoreLabel = CCLabelBMFont::create(scoreString->getCString(), kFontFile);
    scoreLabel->setPosition(ccp(screenSize.width * 0.5,  screenSize.height * 0.9));
    scoreLabel -> setAlignment(kCCTextAlignmentLeft);
    scoreLabel -> setScale(1.2);
    scoreLabel -> setAnchorPoint(ccp(0.5, 1));
    addChild(scoreLabel);
        
    // instruction
    instructionBMFont= CCLabelBMFont::create("Use Left And Right Arrow", kFontFile);
    instructionBMFont->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.8));
    instructionBMFont->setScale(0.4);
   // addChild(instructionBMFont);
    
    return true;
}

void HUDLayer::onEnter() {
    CCLayer::onEnter();
}

void HUDLayer::addHeart(){
    
}

#pragma mark- update score.

void HUDLayer::setScore() {
    
    if(score < 0) {
        score = 0;
    }
    
    CCString* scoreString = CCString::createWithFormat("%d", score);
    scoreLabel -> setString(scoreString->getCString());
}


void HUDLayer::specialScore(CCPoint pos){
    CCLabelBMFont *label = CCLabelBMFont::create("+1", kFontFile);
    label->setPosition(pos);
    label->setScale(0.6);
    
    CCMoveTo *move = CCMoveTo::create(0.5, CCPoint(pos.x, pos.y + screenSize.height * 0.1));
    CCCallFuncND *callFun = CCCallFuncND::create(this, callfuncND_selector(HUDLayer::removeLabel), label);
    label->runAction(CCSequence::create(move , callFun , NULL));
    
    addChild(label);
}

void HUDLayer::removeLabel(CCLabelBMFont *spr){
    spr->removeFromParentAndCleanup(true);
    updateScore(1);
}

void HUDLayer::updateBrainScore(){
    brain++;
    CCString* scoreString = CCString::createWithFormat("x %d", brain);
    brainLabel -> setString(scoreString->getCString());
}

void HUDLayer::updateScore(int addUpScore) {
    
    score += addUpScore;
    
    setScore();
}

#pragma mark

void HUDLayer::activateControls(bool boolValue) {
    if(boolValue) {
        startTimer();
    }
    else {
        stopTimer();
    }
    pauseMenu->setVisible(boolValue);
    pauseMenu -> setEnabled(boolValue);
}

void HUDLayer::pauseButtonClicked(CCObject* sender) {

//    Utility::playSound(CCString::create(kSoundButton));
//    
//    gamelayer -> commonThings(false);
//    
//    PauseLayer* pauseLayer = new PauseLayer();
//    pauseLayer -> initWithGameLayer(gamelayer);
//
//    GameScene* scene = (GameScene*) this -> getParent();
//    scene -> addChild(pauseLayer,200);
//    
//    pauseLayer -> setTag(kTagPauseLayer);

   
}

void HUDLayer::onExit() {
    removeAllChildrenWithCleanup(true);
    CCLayer::onExit();
}

HUDLayer::~HUDLayer() {
    
}

void HUDLayer::reduceHeart(){
     totalHeart--;
    if(totalHeart > 0){
       
        CCSprite *sprite = (CCSprite*)heartArray->objectAtIndex(0);
        sprite->removeFromParentAndCleanup(true);
        heartArray->removeObjectAtIndex(0);
    }else{
        
    }
}

#pragma mark- timer methods

void HUDLayer::setTime() {
    
    
}

void HUDLayer::updateTime() {
    
}

void HUDLayer::startTimer() {
   
}

void HUDLayer::stopTimer() {
    
}

void HUDLayer::restartTimer() {
   
}

void HUDLayer::reduceTime(CCPoint pos){
    
}


void HUDLayer::enableThirdLayer(){

}

void HUDLayer::disbaleInstruction(CCLabelBMFont *obj){
    obj->removeFromParentAndCleanup(true);
}
void HUDLayer::changeInstruction(int number){
    
}






