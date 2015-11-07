//
//  InstructionScene.h
//  BabyKiss
//
//  Created by HAYER on 18/07/14.
//
//

#ifndef __BabyKiss__InstructionScene__
#define __BabyKiss__InstructionScene__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class InstructionScene : public CCLayer {
    
    CCSize screenSize;
    
    int indexInstruction ;
    int maxInstructionIndex;
    CCSprite* instruction;
    
public:
    
    static CCScene* scene();
    
    InstructionScene();
    ~InstructionScene();
    
    virtual void onExit();
    virtual void onEnter();
    
    void resumeBackgroundMusic();
    
    void buttonClicked(CCObject*);
    void resumeGame();
    void action();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) ;
};


#endif /* defined(__BabyKiss__InstructionScene__) */
