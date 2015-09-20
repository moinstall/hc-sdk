//
//  ZombieHeroAppDelegate.cpp
//  ZombieHero
//
//  Created by HAYER on 04/01/15.
//  Copyright __MyCompanyName__ 2015. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "MenuScene.h"
#include "Constants.h"
#include "Utility.h"
#include "GameScene.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    CCSpriteFrameCache::sharedSpriteFrameCache() -> purgeSharedSpriteFrameCache();
    CCSpriteFrameCache::sharedSpriteFrameCache() -> removeSpriteFrames();
    CCTextureCache::sharedTextureCache() -> removeAllTextures();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    
    // turn on display FPS
    pDirector->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCSize frameSize = pEGLView->getFrameSize();
    CCSize designSize = CCSizeMake(320, 480);
    vector<string> searchPaths;
    
    CCSize resourceSize;
    
//    Utility :: isIPad = true;
    searchPaths.push_back("hd");
    resourceSize = CCSizeMake(640, 960);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width , designSize.height, kResolutionExactFit);
    pDirector->setContentScaleFactor(resourceSize.width/designSize.width);
    
    searchPaths.push_back("font");
    searchPaths.push_back("sounds");
    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(searchPaths);
    
    //-----set bools----
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    if(!defaults->getBoolForKey(kFirstTimeRunKey)){
        defaults->setBoolForKey(kFirstTimeRunKey, true);
        defaults->setBoolForKey(keyBackgroundMusic, true);
        defaults->setBoolForKey(keySound, true);
    }
    
    //----load graphics----
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ZombieHero_menu.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ZombieHero_hud.plist");    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ZombieHero_game_objects.plist");
    
    //----load sound effects----

    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(kMusicBackgroundGame);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundButton);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundBuild);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundCoin);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundfalling);
     SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundHitGround);
    //-----call scene----
    CCScene *pScene = MenuScene::scene();
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    
    if(defaults->getBoolForKey(keyBackgroundMusic)){
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    if(defaults->getBoolForKey(keySound)){
        SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    }
}
