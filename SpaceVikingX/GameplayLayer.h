//
//  GameplayLayer.h
//  SpaceVikingX
//
//  Created by anjun on 12-9-17.
//
//

#ifndef SpaceVikingX_GameplayLayer_h
#define SpaceVikingX_GameplayLayer_h
#include "cocos2d.h"
#include "SneakyJoystick.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystickSkinnedBase.h"
USING_NS_CC;
class GameplayLayer:public cocos2d::CCLayer{
public:
    CREATE_FUNC(GameplayLayer);
    virtual bool init();
    void initJoystickAndButtons();
    void applyJoystick(SneakyJoystick *aJoystick, CCNode *tempNode, float deltaTime);
    void update(float deltaTime);
private:
    CCSprite *vikingSprite;
    SneakyJoystick *leftJoystick;
    SneakyButton *jumpButton;
    SneakyButton *attackButton;
};


#endif
