//
//  Mallet.h
//  SpaceVikingX
//
//  Created by anjun on 12-9-28.
//
//

#ifndef __SpaceVikingX__Mallet__
#define __SpaceVikingX__Mallet__

#include "cocos2d.h"
#include "GameObject.h"
USING_NS_CC;
class Mallet:public GameObject{
public:
    ~Mallet();
      bool init();
      void initAnimations();
      void changeState(CharacterStates newState);
      void updateStateWithDeltaTime(float dt,CCArray *listOfGameObjects);
    CC_SYNTHESIZE_RETAIN(CCAnimation*, malletAnim, MalletAnim)
    
};

#endif /* defined(__SpaceVikingX__Mallet__) */
