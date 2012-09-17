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
class GameplayLayer:public cocos2d::CCLayer{
public:
    static GameplayLayer* create();
    virtual bool init();
private:
    cocos2d::CCSprite *vikingSprite;
};


#endif
