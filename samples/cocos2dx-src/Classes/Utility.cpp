//
//  Utility.cpp
//  BabyKiss
//
//  Created by HAYER on 10/07/14.
//
//

#include "Utility.h"
#include "NativeUtils.h"
#include "NDKHelper.h"
#include "Constants.h"

bool Utility::isPad = false;
bool Utility::isGooglePlay = false;


SimpleAudioEngine *Utility::soundEngine = NULL;


int Utility::randomNumberBetween(int lowNumber, int highNumber) {
    int randomNumber = arc4random() % (highNumber - lowNumber + 1);
    randomNumber += lowNumber;
    return randomNumber;
}

float Utility::randomFloatBetween(float lowNumber, float highNumber) {
    float randomNumber =  ((highNumber - lowNumber) * ((float)rand() / RAND_MAX)) + lowNumber;
    return randomNumber;
}


void Utility::post(int intValue, const char* leaderboardId_iOS, const char* leaderboardId_android) {
    
    if(isGooglePlay) {
        
        NativeUtils::submitScore(leaderboardId_android, intValue);
    }
    else {
        
        CCDictionary* prms = CCDictionary::create();
        
        CCString *leaderBoardId = CCString::create(leaderboardId_iOS);
        prms -> setObject(leaderBoardId, "LeaderboardId");
        
        CCString *intValueString = CCString::createWithFormat("%d", intValue);
        prms -> setObject(intValueString, "intValue");
        
        // BUG in original game
        // SendMessageWithParams(string("submit"), prms);
    }
}

#pragma mark- Sound functions

bool Utility::shouldPlayBackgroundMusic() {
	bool playBgMusic = CCUserDefault::sharedUserDefault()->getBoolForKey(keyBackgroundMusic);
	return playBgMusic;
}

bool Utility::shouldPlaySounds(){
	bool playSounds = CCUserDefault::sharedUserDefault()->getBoolForKey(keySound);
	return playSounds;
}

void Utility::playOrPauseMusic(CCString *bgMusicFile) {
	if (soundEngine == NULL) {
		//Get the sound engine instance, if something went wrong this will be nil
		soundEngine = SimpleAudioEngine::sharedEngine();
	}
	if(shouldPlayBackgroundMusic()) {
		if(!soundEngine->isBackgroundMusicPlaying()) {
			soundEngine->playBackgroundMusic(bgMusicFile->getCString(), true);
		}
	}else if (soundEngine->isBackgroundMusicPlaying()) {
		soundEngine->stopBackgroundMusic();
	}
}

void Utility::changeVolume(float volume) {
    Utility::soundEngine->setBackgroundMusicVolume(volume);
}

void Utility::playMusic(CCString *bgMusicFile) {
	if(shouldPlayBackgroundMusic()) {
		if (soundEngine == NULL) {
			//Get the sound engine instance, if something went wrong this will be nil
			soundEngine = SimpleAudioEngine::sharedEngine();
		}
		if(!(soundEngine->isBackgroundMusicPlaying())) {
            //			float volume = CCUserDefault::sharedUserDefault()->getFloatForKey(bgMusicFile->getCString());
            //			soundEngine->setBackgroundMusicVolume(volume);
			soundEngine->playBackgroundMusic(bgMusicFile->getCString(), true);
		}
	}
}

void Utility::stopMusic() {
	if (soundEngine == NULL) {
		//Get the sound engine instance, if something went wrong this will be nil
		soundEngine = SimpleAudioEngine::sharedEngine();
	}
	soundEngine->stopBackgroundMusic();
}

int Utility::playSound(CCString *sound ){
	int soundId = -1;
	if(shouldPlaySounds()){
		if (soundEngine == NULL) {
			//Get the sound engine instance, if something went wrong this will be nil
			soundEngine = SimpleAudioEngine::sharedEngine();
		}
		soundId = soundEngine->playEffect(sound->getCString());
	}
	return soundId;
}

int Utility::playSoundLoop(CCString *sound, float volume){
	int soundId = -1;
	if(shouldPlaySounds()){
		if (soundEngine == NULL) {
			//Get the sound engine instance, if something went wrong this will be nil
			soundEngine = SimpleAudioEngine::sharedEngine();
		}
		soundId = soundEngine->playEffect(sound->getCString() , true);
	}
	return soundId;
}

void Utility::stopSound(int soundId){
    soundEngine->stopAllEffects();
    soundEngine -> stopEffect(soundId);
}

void Utility::playAnimation(CCSprite *sprite , int numberOfFrames , CCString *animString, float time, bool loop){
    CCArray *anim = CCArray::createWithCapacity(4);
    char fn[128];
    for(int i = 1;i<numberOfFrames;i++){
        sprintf(fn, "%s%d",animString->getCString() , i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
        anim->addObject(frame);
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(anim,time);
    
    //  animation->setLoops(-1);
    CCAnimate *animate = CCAnimate::create(animation);
    if(loop)
        sprite->runAction(CCRepeatForever::create(animate));
    else
        sprite->runAction(animate);
    
    
}

void Utility::unlockLevel(int levelNumber) {
    CCString* stringIsLevelLocked = CCString::createWithFormat("level_%d_locked", levelNumber);
    CCUserDefault::sharedUserDefault() -> setBoolForKey(stringIsLevelLocked->getCString(), false);
}

bool Utility::isLevelLocked(int levelNumber) {
    
    bool isLocked = false;
    
    if(levelNumber != 1) {
        CCString* stringIsLevelLocked = CCString::createWithFormat("level_%d_locked", levelNumber);
        isLocked = CCUserDefault::sharedUserDefault()->getBoolForKey(stringIsLevelLocked->getCString(), true);
    }
    return isLocked;
}

void Utility::setLevelToPlay(int levelNumber) {
//    CCUserDefault::sharedUserDefault() -> setIntegerForKey(LevelNo, levelNumber);
}

int Utility::getLevelToPlay() {
//    return CCUserDefault::sharedUserDefault() -> getIntegerForKey(LevelNo,1);
}

bool Utility::isAdFree(){
    return CCUserDefault::sharedUserDefault()->getBoolForKey("AdVersion", false);
}

void Utility::setAdFree(){
    CCUserDefault::sharedUserDefault()->setBoolForKey("AdVersion", true);
}


#pragma mark
