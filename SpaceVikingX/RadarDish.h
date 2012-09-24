//
//  RadarDish.h
//  SpaceVikingX
//
//  Created by anjun on 12-9-19.
//
//

#ifndef __SpaceVikingX__RadarDish__
#define __SpaceVikingX__RadarDish__
#include "cocos2d.h"
#include "GameCharacter.h"
class RadarDish:public GameCharacter{
public:
    ~RadarDish();
    static RadarDish* createWithSpriteFrameName(const char *pszSpriteFrameName);
    void changeState(CharacterStates newState);
    void updateStateWithDeltaTime(float deltaTime, CCArray *listOfGameObjects);
//    CCRect adjustedBoundingBox();
    void initAnimations();
    bool init();
    CC_SYNTHESIZE_RETAIN(CCAnimation*, tiltingAnim, TiltingAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, transmittingAnim, TransmittingAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, takingAHitAnim, TakingAHitAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, blowingUpAnim, BlowingUpAnim)

private:
    GameCharacter *vikingCharacter;
};
#endif /* defined(__SpaceVikingX__RadarDish__) */
