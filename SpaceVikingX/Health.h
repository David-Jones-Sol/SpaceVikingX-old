//
//  Health.h
//  SpaceVikingX
//
//  Created by anjun on 12-9-28.
//
//

#ifndef __SpaceVikingX__Health__
#define __SpaceVikingX__Health__

#include "cocos2d.h"
#include "GameObject.h"
USING_NS_CC;
class Health:public GameObject{
public:
    ~Health();
    bool init();
    void initAnimations();
    void changeState(CharacterStates newState);
    void updateStateWithDeltaTime(float dt,CCArray *listOfGameObjects);
    CC_SYNTHESIZE_RETAIN(CCAnimation*, healthAnim, HealthAnim)
};

#endif /* defined(__SpaceVikingX__Health__) */
