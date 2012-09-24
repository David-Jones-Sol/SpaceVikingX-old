//
//  Viking.h
//  SpaceVikingX
//
//  Created by anjun on 12-9-19.
//
//

#ifndef __SpaceVikingX__Viking__
#define __SpaceVikingX__Viking__

#include "cocos2d.h"
#include "GameCharacter.h"
#include "SneakyButton.h"
#include "SneakyJoystick.h"
typedef enum {
    kLeftHook,
    kRightHook
} LastPunchType;
class Viking : public GameCharacter{
public:
    CREATE_FUNC(Viking);
   static Viking* createWithSpriteFrameName(const char *pszSpriteFrameName);
//    ~Viking();
    bool isCarryingWeapon();
    int getWeaponDamage();
    void applyJoystick(SneakyJoystick *aJoystick ,float deltaTime);
    void checkAndClampSpritePosition();
    void changeState(CharacterStates newState);
    void updateStateWithDeltaTime(float deltaTime, CCArray *listOfGameObjects);
    CCRect adjustedBoundingBox();
    void initAnimations();
    bool init();
    
    // Standing, Breathing, Walking
    CC_SYNTHESIZE_RETAIN(CCAnimation*, breathingAnim, BreathingAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, breathingMalletAnim, BreathingMalletAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, walkingAnim, WalkingAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, walkingMalletAnim, WalkingMalletAnim)
    // Crouching, Standing Up, Jumping
    CC_SYNTHESIZE_RETAIN(CCAnimation*, crouchingAnim, CrouchingAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, crouchingMalletAnim, CrouchingMalletAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, standingUpAnim, StandingUpAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, standingUpMalletAnim, StandingUpMalletAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, jumpingAnim, JumpingAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, jumpingMalletAnim, JumpingMalletAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, afterJumpingAnim, AfterJumpingAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, afterJumpingMalletAnim, AfterJumpingMalletAnim)
    
    // Punching
    CC_SYNTHESIZE_RETAIN(CCAnimation*, rightPunchAnim, RightPunchAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, leftPunchAnim, LeftPunchAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, malletPunchAnim, MalletPunchAnim)
    // Taking Damage and Death
    CC_SYNTHESIZE_RETAIN(CCAnimation*, phaserShockAnim, PhaserShockAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, deathAnim, DeathAnim)

    CC_SYNTHESIZE(SneakyJoystick, joystick, Joystick)
    CC_SYNTHESIZE(SneakyButton, jumpButton, jumpButton)
    CC_SYNTHESIZE(SneakyButton, attackButton, attackButton)

private:
    LastPunchType myLastPunch;
    bool isCarryingMallet;
    CCSpriteFrame *standingFrame;
     float millisecondsStayingIdle;
};

#endif /* defined(__SpaceVikingX__Viking__) */
