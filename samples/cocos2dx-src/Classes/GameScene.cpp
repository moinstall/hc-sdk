//
//  GameScene.cpp
//  ZombieHero
//
//  Created by HAYER on 04/01/15.
//
//

#include "GameScene.h"
#include "NDKHelper.h"
#include "Constants.h"
#include "Utility.h"
#include "GameOverLayer.h"

CCScene* GameScene::scene() {
    CCScene *scene = CCScene::create();
    GameScene* layer =  new GameScene();
    layer -> init();
    scene -> addChild(layer);
    return scene;
}

GameScene::GameScene() {
    
    arrayPlateform = new CCArray();
    progressArray = new CCArray();
    redDotArray = new CCArray();
    
    shouldEnableTouch = true;
    zombie = NULL;

    //--- load physics---
    gravity.Set(0.0, -10.0f);
    world = new b2World(gravity);
    world -> SetAllowSleeping(false);
    world -> SetContinuousPhysics(true);
    
    //----loader----
    loader = new LevelHelperLoader("ZombieHeroLevel.plhs");
    loader -> addObjectsToWorld(world, this);
    
    parallax = loader -> parallaxNodeWithUniqueName("Parallax_1");
    setSpeedZero();
    
    brainAppear = false;
    zombieRun = false;
    flipMood = false;
    touchActive = true;
    this->scheduleUpdate();
}

void GameScene::setSpeedZero(){
    parallax -> setSpeed(0);
}

void GameScene::setSpeedNormal(){
    parallax -> setSpeed(100);
}

bool GameScene::init() {
    
    if(!CCLayer::init()) {
        return false;
    }

    screenSize = CCDirector::sharedDirector() -> getWinSize();
    
    hudLayer = new HUDLayer();
    
    hudLayer -> initWithGameLayer(this);
    addChild(hudLayer);
    
    //-----
    Plateform* plateform = new Plateform();
    plateform -> init(this);
    plateform -> setPosition(ccp(screenSize.width * -0.3, plateform->getContentSize().height * 0.5));
    this -> addChild(plateform);
    plateform -> setColor(GameObjects::getRandomColor());
//    plateform->setAnchorPoint(ccp(1, 0.5));
    
    arrayPlateform -> addObject(plateform);
    
    
    //-----Zombie----
    zombie = new Zombie();
    zombie -> init(this);
    zombie -> setScale(0.5);
    zombie -> setPosition(ccp(screenSize.width * 0.2, (plateform->getPositionY() + plateform->getContentSize().height * 0.5 + zombie->getContentSize().height * 0.45 * zombie->getScaleY())));
    this -> addChild(zombie);
    zombie->setAnchorPoint(ccp(1, 0.5));
    
    
    addPlateform();
    
    return true;
}

void GameScene::onEnter() {
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    if(!Utility::isAdFree()){
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("YES"), KBottomAd);
        prms->setObject(CCString::create("NO"), kTopAd);
        prms->setObject(CCString::create("NO"), kMenu);
        prms->setObject(CCString::create("NO"), kGameOver);
        SendMessageWithParams(string("adFunctionalty"), prms);
    }
    
    Utility::stopMusic();
    Utility::playMusic(CCString::create(kMusicBackgroundGame));
    
//    NDKHelper::AddSelector("GameSceneSelectors",
//                           "resumeBackgroundMusic",
//                           callfuncND_selector(GameScene::resumeBackgroundMusic),
//                           this);
}

void GameScene::addPlateform() {
    
    Plateform* lastPlateform = (Plateform*) arrayPlateform -> objectAtIndex(0);
    float randomDistance = Utility::randomFloatBetween(screenSize.width * 0.1, screenSize.width * 0.5);
    float randomScale = Utility::randomFloatBetween(0.05, 0.2);
   float firstPlatformPos = lastPlateform->getPositionX() + lastPlateform->getContentSize().width/2 * lastPlateform->getScaleX();

    
    Plateform* plateform = new Plateform();
    plateform -> init(this);
    plateform -> setScaleX(randomScale);

    float posX = lastPlateform->getPositionX() +(lastPlateform->getContentSize().width/2 * lastPlateform->getScaleX())+ randomDistance + plateform->getContentSize().width * plateform->getScaleX() * 0.5;
    
    plateform -> setPosition(ccp(screenSize.width * 1.3, plateform->getContentSize().height * 0.5));
    CCMoveTo *moveTo = CCMoveTo::create(0.3, CCPoint(posX, plateform->getPositionY()));
    plateform->runAction(moveTo);
    this -> addChild(plateform);
    
    plateform -> setColor(GameObjects::getRandomColor());
    arrayPlateform -> addObject(plateform);
    
    // add Yellow Image To the Center of Platform
    
    addYellowCenter(posX, CCPoint(plateform->getPositionX(),plateform->getPositionY() + plateform->getContentSize().height/2));
    
    // add Brain
    
    if((posX -(plateform->getContentSize().width/2 * plateform->getScaleX())) > screenSize.width * 0.45){
        float posForBrain = Utility::randomFloatBetween((zombie->getPositionX() + (zombie->getContentSize().width/2 * zombie->getScaleX()) * 1.1), (posX - (plateform->getContentSize().width/2 * plateform->getScaleX()))* 0.9);
        addBrain(posForBrain, CCPoint(plateform->getPositionX(),plateform->getPositionY() + plateform->getContentSize().height * 0.4));
    }
    
}

void GameScene::addYellowCenter(float posX , CCPoint platformPos){
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("red_center");
    sprite->setScale(0.15);
    
    sprite->setPosition(platformPos);
    redDotArray->addObject(sprite);
    sprite->setAnchorPoint(CCPoint(0.5, 1));
    
    CCMoveTo *dotMoveTo = CCMoveTo::create(0.3, CCPoint(posX, sprite->getPositionY()));
    sprite->runAction(dotMoveTo);
    
    this->addChild(sprite);
}

void GameScene::addBrain(float posX , CCPoint platformPos){
    brainAppear = true;
    brainSprites = CCSprite::createWithSpriteFrameName("brain");
    brainSprites->setScale(0.5);
    
    brainSprites->setPosition(platformPos);
    brainSprites->setAnchorPoint(CCPoint(0.5, 1));
    
    CCMoveTo *dotMoveTo = CCMoveTo::create(0.3, CCPoint(posX, brainSprites->getPositionY()));
    brainSprites->runAction(dotMoveTo);
    
    this->addChild(brainSprites);
}

void GameScene::increaseStick() {
    
    stickProgressBar -> setRotation(0);
    gameId =   Utility::playSound(CCString::create(kSoundBuild));
    
    CCProgressFromTo* progressAction = CCProgressFromTo::create(2.0, 0, 100);
    stickProgressBar -> runAction(progressAction);
}

void GameScene::stopAndDecline() {
    stickProgressBar -> stopAllActions();
    Utility::stopSound(gameId);
    
    CCRotateBy* rotate = CCRotateBy::create(0.25, 90);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(GameScene::makeZombieRun));
    CCCallFunc* call_1 = CCCallFunc::create(this, callfunc_selector(GameScene::checkCollisionWithYellow));
    CCSequence* seq = CCSequence::create(rotate,call_1 , call, NULL);
    stickProgressBar -> runAction(seq);
}

void GameScene::checkCollisionWithYellow(){
    CCSprite *yelloWSprite = (CCSprite*)redDotArray->objectAtIndex(0);
    
    float leftBoundary = yelloWSprite->getPositionX() - yelloWSprite->getContentSize().width * 0.5 * yelloWSprite->getScaleX();
    float rightBoundary = yelloWSprite->getPositionX() + yelloWSprite->getContentSize().width * 0.5 * yelloWSprite->getScaleX();
    
    
    float posStick = stickProgressBar->getPositionX() + stickProgressBar->getContentSize().height * (stickProgressBar->getPercentage() / 100);
    if(posStick > leftBoundary && posStick < rightBoundary ){
         Utility::playSound(CCString::create(kSoundCoin));
        hudLayer->specialScore(yelloWSprite->getPosition());
    }else{
        Utility::playSound(CCString::create(kSoundHitGround));
    }
}

void GameScene::makeZombieRun() {
    
    zombie -> run();
    
    posStick = stickProgressBar->getContentSize().height * (stickProgressBar->getPercentage() / 100);
    time = posStick * 0.01;

    float posX = checkGameStatus();
    
    CCMoveTo* moveTo = CCMoveTo::create(time, ccp(posX, zombie->getPositionY()));
    CCCallFunc* stop = CCCallFunc::create(zombie, callfunc_selector(Zombie::stopIt));
    
    CCCallFunc* fall = CCCallFunc::create(zombie, callfunc_selector(Zombie::fallDown));
    CCSequence* seq = CCSequence::create(moveTo, stop, fall, NULL);
    
    zombie -> runAction(seq);
   
}

void GameScene::movePlatform(){
    setSpeedNormal();
    
    touchActive = false;
    hudLayer->updateScore(1);

    float timeForMove =  0.0001;
    
    //  Platform movement
    for(int i = 0 ; i < arrayPlateform->count() ; i++){
        LHSprite *sprite = (LHSprite*)arrayPlateform->objectAtIndex(i);
        CCMoveBy *moveOut = CCMoveBy::create(timeForMove, CCPoint(kMovementSpeed, 0));
        sprite->runAction(CCRepeatForever::create(moveOut));
    }

    // brain Move
    if(brainAppear){
        CCMoveBy *moveOut = CCMoveBy::create(timeForMove, CCPoint(kMovementSpeed, 0));
        brainSprites->runAction(CCRepeatForever::create(moveOut));
    }
    
    //  dot,  progress, zombie movement
    dotMove(timeForMove);
    progressBarMove(timeForMove);
    zombieMove(timeForMove);
    
    zombieRun = true;
   
}

void GameScene::dotMove(float timeForMove){
    LHSprite *dotSprite = (LHSprite*)redDotArray->objectAtIndex(0);
    CCMoveBy * dotOut_1 = CCMoveBy::create(timeForMove, CCPoint(kMovementSpeed , 0));
    dotSprite->runAction(CCRepeatForever::create(dotOut_1));
}

void GameScene::progressBarMove(float timeForMove){
    for(int i = 0 ; i < progressArray->count() ; i++){
        CCMoveBy *progressBarOut = CCMoveBy::create(timeForMove, CCPoint(kMovementSpeed , 0));
        CCProgressTimer *progressTimer = (CCProgressTimer*)progressArray->objectAtIndex(i);
        progressTimer->runAction(CCRepeatForever::create(progressBarOut));
    }
}

void GameScene::zombieMove(float timeForMove){
    CCMoveBy *zombieOut = CCMoveBy::create(timeForMove, CCPoint(kMovementSpeed , 0));
    zombie->runAction(CCRepeatForever::create(zombieOut));
}



void GameScene::removeFirstPlatform(){
    setSpeedZero();
    
    zombieRun = false;
    shouldEnableTouch = true;
    
    // remove Brain
    if(brainAppear){
        brainAppear = false;
        brainSprites->removeFromParentAndCleanup(true);
    }
    
    // remove Dot
    
    LHSprite *dotSprite = (LHSprite*)redDotArray->objectAtIndex(0);
    redDotArray->removeObject(dotSprite);
    
    dotSprite->removeFromParentAndCleanup(true);
    
    // remove 1st Platform
    LHSprite *sprite = (LHSprite*)arrayPlateform->objectAtIndex(0);
    arrayPlateform->removeObjectAtIndex(0);
    sprite->removeFromParentAndCleanup(true);
    
    // add neXt Platform
    addPlateform();
    
}

void GameScene::update(float dt){
    if(zombieRun){
       
        if(zombie->getPositionX() < screenSize.width * 0.2 && zombie->getPositionX() > screenSize.width * 0.15){
            LHSprite *dotSprite = (LHSprite*)redDotArray->objectAtIndex(0);
            for(int i = 0 ; i < arrayPlateform->count() ; i++){
                LHSprite *sprite = (LHSprite*)arrayPlateform->objectAtIndex(i);
                sprite->stopAllActions();
            }
            touchActive = true;
            zombieRun = false;
            stickProgressBar->stopAllActions();
            zombie->stopAllActions();
            dotSprite->stopAllActions();
            removeFirstPlatform();
        }
    }
    if(flipMood ){
        LHSprite *sprite = (LHSprite*)arrayPlateform->objectAtIndex(1);
        if(zombie->getPositionX() >  (sprite->getPositionX() - (sprite->getContentSize().width/2 * sprite->getScaleX()))){
            this->unschedule(schedule_selector(GameScene::movePlatform));
            flipMood = false;
            zombie -> shouldFallDown = true;
            zombie->stopAllActions();
            zombie->fallDown();
            
        }
    }
    if(brainAppear){
        if(zombie->boundingBox().containsPoint(brainSprites->getPosition())){
            Utility::playSound(CCString::create(kSoundCoin));
            brainAppear = false;
            brainSprites->removeFromParentAndCleanup(true);
            hudLayer->updateBrainScore();
           
            
        }
    }
}

void GameScene::stopAllObjectsAction(){
    
}

float GameScene::checkGameStatus() {
    Plateform* lastPlatform = (Plateform*)arrayPlateform -> objectAtIndex(arrayPlateform->count()-1);
    
    float leftBoundary = lastPlatform->getPositionX() - lastPlatform->getContentSize().width * 0.5 * lastPlatform->getScaleX();
    float rightBoundary = lastPlatform->getPositionX() + lastPlatform->getContentSize().width * 0.5 * lastPlatform->getScaleX();
   
    if( (stickProgressBar->getPositionX() + posStick )>= leftBoundary && (stickProgressBar->getPositionX() + posStick) <= rightBoundary) {
        this->scheduleOnce(schedule_selector(GameScene::movePlatform), time + 0.2);
        return (rightBoundary );
    }
    else {
        zombie -> shouldFallDown = true;
        return zombie->getPositionX() + zombie->getContentSize().width * 0.5 * zombie->getScale() + posStick ;
    }
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)  {
    if(touchActive){
        if(shouldEnableTouch) {
            shouldEnableTouch = false;
            //----stick progress bar---
            LHSprite *plateform = (LHSprite*)arrayPlateform->objectAtIndex(0);
            
            CCSprite* stick = CCSprite::createWithSpriteFrameName("stick");
            
            stickProgressBar = CCProgressTimer::create(stick);
            stickProgressBar -> setPosition(ccp(plateform->getPositionX() + (plateform->getContentSize().width/2 * plateform->getScaleX()) , plateform->getContentSize().height));
            stickProgressBar -> setType(kCCProgressTimerTypeBar);
            stickProgressBar -> setMidpoint(ccp(0.5, 0));
            stickProgressBar -> setBarChangeRate(ccp(0, 1));
            stickProgressBar -> setPercentage(0);
            stickProgressBar -> setAnchorPoint(ccp(0.5, 0));
            stickProgressBar->setScaleX(0.5);
            addChild(stickProgressBar);
            
            progressArray->addObject(stickProgressBar);
            
            increaseStick();
            
            return true;
        }else{
            if(flipMood){
                flipMood = false;
                zombie->setAnchorPoint(ccp(1, 0.5));
                zombie->setFlipY(false);
            }else{
                flipMood = true;
                zombie->setAnchorPoint(ccp(1, 1.4));
                zombie->setFlipY(true);
            }
            
        }
    }
    return false;
}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    
//    hudlayer->powerProgressTimer -> setVisible(false);
//    float percentagePower = hudlayer -> powerProgressTimer -> getPercentage();
//    stickman -> jumpAnim(percentagePower);
//    hudlayer -> stopAndRemovePower();
    if(!shouldEnableTouch){
        stopAndDecline();
    }
}

void GameScene::callgameOver() {
    CCUserDefault::sharedUserDefault() -> setIntegerForKey(keyCurrentScore, hudLayer->score);
    
    GameOverLayer* gameOverLayer = new GameOverLayer();
    gameOverLayer -> initWithGameLayer(this);
    
    CCScene *scene = (CCScene*)this -> getParent();
    scene -> addChild(gameOverLayer);
}

void GameScene::resumeBackgroundMusic(){
//    Utility::playOrPauseMusic(CCString::create(kMusicBackgroundGame));
}

void GameScene::onExit() {
    
    if(!Utility::isAdFree()){
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("NO"), KBottomAd);
        prms->setObject(CCString::create("NO"), kTopAd);
        prms->setObject(CCString::create("NO"), kMenu);
        prms->setObject(CCString::create("NO"), kGameOver);
        SendMessageWithParams(string("adFunctionalty"), prms);
    }
//
//    Utility::changeVolume(1.0);
//    Utility::stopAllSoundEffects();
    
    NDKHelper::RemoveSelectorsInGroup("GameSceneSelectors");
    
    removeAllChildrenWithCleanup(true);
    CCLayer::onExit();
}

GameScene::~GameScene() {
    
}

