//
//  GameObject.h
//  SpaceVikingX
//
//  Created by anjun on 12-9-19.
//
//

#ifndef __SpaceVikingX__GameObject__
#define __SpaceVikingX__GameObject__

#include "cocos2d.h"
#include "Constants.h"
#include "CommonProtocols.h"

USING_NS_CC;
using namespace std;

class GameObject :public CCSprite  {
public:
    CC_SYNTHESIZE(bool,isActive,IsActive)
    CC_SYNTHESIZE(bool, reactsToScreenBoundaries, ReactsToScreenBoundaries)
    CC_SYNTHESIZE(CCSize, screenSize, ScreenSize)
    CC_SYNTHESIZE(GameObjectType, gameObjectType, GameObjectType)
    CREATE_FUNC(GameObject)
    
    virtual  bool init();
    virtual  void changeState(CharacterStates newState);
    virtual  void updateStateWithDeltaTime(float dt,CCArray *listOfGameObjects);
    virtual  CCRect adjustedBoundingBox();
    virtual  CCAnimation * loadPlistForAnimationWithName(string animationName,string className);
   
   
private:
    
};



#endif /* defined(__SpaceVikingX__GameObject__) */
