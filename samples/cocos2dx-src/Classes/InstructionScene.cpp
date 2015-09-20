//
//  InstructionScene.cpp
//  BabyKiss
//
//  Created by HAYER on 18/07/14.
//
//

#include "InstructionScene.h"
#include "Constants.h"
#include "GameScene.h"
#include "NDKHelper.h"
#include "Utility.h"
#include "MenuScene.h"


#define kTagLeftButton 5001
#define kTagRightButton 5002

CCScene* InstructionScene::scene() {
    
    CCScene* scene = new CCScene();
    
    InstructionScene* layer =  new InstructionScene();
    layer -> init();
    scene -> addChild(layer);
    
	return scene;
}

InstructionScene::InstructionScene() {
    indexInstruction = 1;
    maxInstructionIndex = 2;
}

void InstructionScene::onEnter() {
 
    CCLayer::onEnter();
    screenSize = CCDirector::sharedDirector() -> getWinSize();
    
    CCLayerColor* layerColor = CCLayerColor::create();
    layerColor->setColor(ccc3(1, 28, 50));
    layerColor -> setOpacity(255);
    layerColor -> setContentSize(ccp(screenSize.width * 1.1, screenSize.height * 1.1));
    layerColor -> setPosition(ccp(screenSize.width * 0, screenSize.height * 0));
    addChild(layerColor);
   
    if(!Utility::isAdFree()){
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("NO"), KBottomAd);
        prms->setObject(CCString::create("NO"), kTopAd);
        prms->setObject(CCString::create("NO"), kMenu);
        prms->setObject(CCString::create("NO"), kGameOver);
        SendMessageWithParams(string("adFunctionalty"), prms);
    }
    
    NDKHelper::AddSelector("InstructionSceneSelectors",
                           "resumeBackgroundMusic",
                           callfuncND_selector(InstructionScene::resumeBackgroundMusic),
                           this);
    
    CCSprite *background = CCSprite::createWithSpriteFrameName("instructions");
    background -> setPosition(ccp(screenSize.width/2, screenSize.height/2));
    addChild(background);
     CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
   
 
}


bool InstructionScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
  
}
void InstructionScene::buttonClicked(CCObject* sender) {
    
    Utility::playSound(CCString::create(kSoundButton));
    CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
 
}

void InstructionScene::resumeGame(){
    Utility::playSound(CCString::create(kSoundButton));
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

void InstructionScene::action() {
    
    }

void InstructionScene::resumeBackgroundMusic(){
    Utility::playOrPauseMusic(CCString::create(kMusicBackgroundGame));
}


void InstructionScene::onExit() {
     CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    if(!Utility::isAdFree()){
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("NO"), KBottomAd);
        prms->setObject(CCString::create("NO"), kTopAd);
        prms->setObject(CCString::create("NO"), kMenu);
        prms->setObject(CCString::create("NO"), kGameOver);
        SendMessageWithParams(string("adFunctionalty"), prms);
    }
    NDKHelper::RemoveSelectorsInGroup("InstructionSceneSelectors");
    
    removeAllChildrenWithCleanup(true);
  
    CCLayer::onExit();
}

InstructionScene::~InstructionScene() {
    
}
