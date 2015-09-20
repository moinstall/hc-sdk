//
//  HUDLayer.h
//  BabyKiss
//
//  Created by HAYER on 10/07/14.
//
//

#ifndef __BabyKiss__HUDLayer__
#define __BabyKiss__HUDLayer__

#include <iostream>

#include "cocos2d.h"

class GameScene;


USING_NS_CC;

class HUDLayer : public CCLayer {
    CCLabelBMFont* timelabel;
    CCSize screenSize;
   
   
    CCMenu* pauseMenu;
    CCArray *heartArray;
    int totalHeart ;
public:
     CCLabelBMFont* scoreLabel ,*brainLabel;
     CCLabelBMFont *instructionBMFont;
     GameScene* gamelayer;
   
    int score , time , brain;
    
    HUDLayer();
    ~HUDLayer();
    
    virtual bool initWithGameLayer(GameScene*);
    virtual void onExit();
    virtual void onEnter();
    
    void pauseButtonClicked(CCObject*);
    void arrowButtonClicked(CCObject*);
    
    void activateControls(bool);

    void setScore() ;
    void updateScore(int addUpScore) ;
    
    void startIncreasingDistance(float dt);
    
    void addHeart();
    
    void reduceHeart();
    
    void setTime();
    void updateTime();
    void startTimer();
    void stopTimer();
    void restartTimer();
    void reduceTime(CCPoint );
    
    
    void updateBrainScore();
    
    void enableThirdLayer();
    void disbaleInstruction(CCLabelBMFont *obj);
    void changeInstruction(int number);
    
    void specialScore(CCPoint);
    void removeLabel(CCLabelBMFont*);
};

#endif /* defined(__BabyKiss__HUDLayer__) */
