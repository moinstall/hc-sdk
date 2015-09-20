//
//  Utility.h
//  BabyKiss
//
//  Created by HAYER on 10/07/14.
//
//

#ifndef __BabyKiss__Utility__
#define __BabyKiss__Utility__

#include <iostream>
#include "cocos2d.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

class Utility {

public:
    
    static bool isPad;
    
    static bool isGooglePlay;
    
    
    static CocosDenshion::SimpleAudioEngine *soundEngine;
    static int playSound(CCString *sound);
    static bool shouldPlayBackgroundMusic();
    static bool shouldPlaySounds();
    static void playOrPauseMusic(CCString *bgMusicFile);
    static void changeVolume(float volume);
    static void playMusic(CCString *bgMusicFile);
    static void stopMusic();
    static void stopSound(int soundId);
    static int playSoundLoop(CCString *sound ,float volume);

    static int randomNumberBetween(int lowNumber, int highNumber);
    static float randomFloatBetween(float lowNumber, float highNumber);
    
    static void post(int intValue, const char* leaderboardId_iOS, const char* leaderboardId_android);
     static void playAnimation(CCSprite *sprite , int , CCString *, float , bool);
    
    static void unlockLevel(int levelNumber);
    static bool isLevelLocked(int levelNumber);
    static void setLevelToPlay(int levelNumber);
    static int getLevelToPlay();
    
    static bool isAdFree();
    static void setAdFree();
};


#endif /* defined(__BabyKiss__Utility__) */
