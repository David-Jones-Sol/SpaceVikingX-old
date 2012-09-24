//
//  GameCharacter.h
//  SpaceVikingX
//
//  Created by anjun on 12-9-19.
//
//

#ifndef __SpaceVikingX__GameCharacter__
#define __SpaceVikingX__GameCharacter__
#include "cocos2d.h"
#include "GameObject.h"
class GameCharacter :public GameObject{
public:
    CC_SYNTHESIZE(int,characterHealth,CharacterHealth)
    CC_SYNTHESIZE(CharacterStates, characterState, CharacterState)
    virtual  void checkAndClampSpritePosition();
    virtual int getWeaponDamage();
  
private:
  
};
#endif /* defined(__SpaceVikingX__GameCharacter__) */
