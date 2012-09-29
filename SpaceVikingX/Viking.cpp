//
//  Viking.cpp
//  SpaceVikingX
//
//  Created by anjun on 12-9-19.
//
//

#include "Viking.h"
#include <typeinfo>
//Viking::~Viking(){
//{
//    //    joystick = nil;
//    //    jumpButton = nil;
//    //    attackButton = nil;
//    CC_SAFE_RELEASE(breathingAnim);
//    CC_SAFE_RELEASE(breathingMalletAnim);
//    CC_SAFE_RELEASE(walkingAnim);
//    CC_SAFE_RELEASE(walkingMalletAnim);
//    CC_SAFE_RELEASE(crouchingAnim);
//    CC_SAFE_RELEASE(crouchingMalletAnim);
//    CC_SAFE_RELEASE(standingUpAnim);
//    CC_SAFE_RELEASE(standingUpMalletAnim);
//    CC_SAFE_RELEASE(jumpingAnim);
//    CC_SAFE_RELEASE(jumpingMalletAnim);
//    CC_SAFE_RELEASE(afterJumpingAnim);
//    CC_SAFE_RELEASE(afterJumpingMalletAnim);
//    CC_SAFE_RELEASE(rightPunchAnim);
//    CC_SAFE_RELEASE(leftPunchAnim);
//    CC_SAFE_RELEASE(malletPunchAnim);
//    CC_SAFE_RELEASE(phaserShockAnim);
//    CC_SAFE_RELEASE(deathAnim);
//
//    CC_SAFE_RELEASE(breathingAnim);
//    CC_SAFE_RELEASE(breathingAnim);
//    CC_SAFE_RELEASE(breathingAnim);
//    CC_SAFE_RELEASE(breathingAnim);
//}
//bool Viking::isCarryingWeapon(){
//    return isCarryingMallet;
//}
int Viking::getWeaponDamage() {
    if (isCarryingMallet) {
        return kVikingMalletDamage;
    }
    return kVikingFistDamage;
}
void Viking::applyJoystick(SneakyJoystick *aJoystick ,float deltaTime)
{
    CCPoint scaledVelocity = ccpMult(aJoystick->getVelocity(), 128.0f);
    CCPoint oldPosition = this->getPosition();
    CCPoint newPosition =
    ccp(oldPosition.x +
        scaledVelocity.x * deltaTime,
        oldPosition.y);                                          // 1
    this->setPosition(newPosition);                              // 2
    
    if (oldPosition.x > newPosition.x) {
        this->setFlipX(true);                                      // 3
    } else {
        this->setFlipX(false);
    }
}
void Viking::checkAndClampSpritePosition() {
    if (this->getCharacterState()!=kStateJumping) {
        if (this->getPosition().y>110.f) {
            this->setPosition(ccp(this->getPosition().x,110.f));
        }
    }
    GameCharacter::checkAndClampSpritePosition();

}
void Viking::changeState(CharacterStates newState){
              
    this->stopAllActions();
    void* action = NULL;
    void* movementAction = NULL;
    CCPoint newPosition;
    this->setCharacterState(newState);
    switch (newState) {
        case kStateIdle:
            if (isCarryingMallet) {
                this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sv_mallet_1.png"));
            } else {
                this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sv_anim_1.png"));
            }
            break;
        case kStateWalking:
            if (isCarryingMallet) {
                action =CCAnimate::create(walkingMalletAnim);
            } else {
//                action =CCAnimate::create(walkingAnim);
     
                action = CCAnimate::create(this->getWalkingAnim());
            }
            break;
        case kStateCrouching:
            if (isCarryingMallet) {
                  action =CCAnimate::create(crouchingMalletAnim);
            } else {
                  action =CCAnimate::create(crouchingAnim);
            }
            break;
        case kStateStandingUp:
            if (isCarryingMallet) {
                action =CCAnimate::create(standingUpMalletAnim);
            } else {
                action =CCAnimate::create(standingUpAnim);
            }
            break;
            
        case kStateBreathing:
            if (isCarryingMallet) {
                action =CCAnimate::create(breathingMalletAnim);
            } else {

                action =CCAnimate::create(this->getBreathingAnim());
            }
            break;
            
        case kStateJumping:
            newPosition = ccp(screenSize.width * 0.2f, 0.0f);
            if (this->isFlipX()==true) {
                newPosition = ccp(newPosition.x * -1.0f, 0.0f);
            }
            movementAction = CCJumpBy::create(0.5f, newPosition, 160.0f, 1);
          
            
            if (isCarryingMallet) {
                // Viking Jumping animation with the Mallet
                action = CCSequence::create(CCArray::create(
                    CCAnimate::create(crouchingMalletAnim),
                    CCAnimate::create(jumpingMalletAnim),
                    CCAnimate::create(afterJumpingMalletAnim)));
    
            } else {
                // Viking Jumping animation without the Mallet

                action = CCSequence::create(CCAnimate::create(crouchingAnim),CCAnimate::create(jumpingAnim),movementAction,CCAnimate::create(afterJumpingAnim),NULL);
     
            }
            break;
            
        case kStateAttacking:
            if (isCarryingMallet == true) {
                action = CCAnimate::create(malletPunchAnim);
            } else {
                if (kLeftHook == myLastPunch) {
                    // Execute a right hook
                    myLastPunch = kRightHook;
                    action = CCAnimate::create(rightPunchAnim);
                } else {
                    // Execute a left hook
                    myLastPunch = kLeftHook;
                    action = CCAnimate::create(leftPunchAnim);
                }
            }
            break;
            
        case kStateTakingDamage:
            this->setCharacterHealth(this->getCharacterHealth() - 10.0f);
                action = CCAnimate::create(phaserShockAnim);
            break;
            
        case kStateDead:
                action = CCAnimate::create(deathAnim);
            break;
            
        default:
            break;
    }
    if (action != NULL) {
        this->runAction((CCAction*)action);
    }


}
void Viking::updateStateWithDeltaTime(float deltaTime, CCArray* listOfGameObjects){

    
    if (this->getCharacterState() == kStateDead)
        return; // Nothing to do if the Viking is dead
    
    
    if ((this->getCharacterState() == kStateTakingDamage) &&
        (this->numberOfRunningActions() > 0))
        return; // Currently playing the taking damage animation
    
    // Check for collisions
    // Change this to keep the object count from querying it each time
    CCRect myBoundingBox = this->adjustedBoundingBox();
    GameCharacter* character;
 
    for (int i=0; i<listOfGameObjects->count(); ++i) {
     character = (GameCharacter*)listOfGameObjects->objectAtIndex(i);
        if (character->getTag() == kVikingSpriteTagValue) continue;
        CCRect characterBox = character->adjustedBoundingBox();

        if (myBoundingBox.intersectsRect(characterBox)) {
            if (character->getGameObjectType() == kEnemyTypePhaser) {
                this->changeState(kStateTakingDamage);
                character->changeState(kStateDead);
            }else if (character->getGameObjectType() == kPowerUpTypeMallet){
                // Update the frame to indicate Viking is
                // carrying the mallet
                isCarryingMallet = true;
              
                 this->changeState(kStateIdle);
                // Remove the Mallet from the scene
              character->changeState(kStateDead);
            }else if (character->getGameObjectType() == kPowerUpTypeHealth){
                 this->setCharacterHealth(100.0f);
                // Remove the health power-up from the scene
                character->changeState(kStateDead);
            }
        }
    }

    this->checkAndClampSpritePosition();
    if (this->getCharacterState() == kStateIdle||
        this->getCharacterState() == kStateStandingUp||
        this->getCharacterState() == kStateWalking||
        this->getCharacterState() == kStateCrouching||
        this->getCharacterState() == kStateBreathing) {
        if (jumpButton->getIsActive()) {
            this->changeState(kStateJumping);
        }else if (attackButton->getIsActive()){
            this->changeState(kStateAttacking);
        }else if ((joystick->getVelocity().x == 0.0f) && (joystick->getVelocity().y == 0.0f)){
            if (this->getCharacterState() == kStateCrouching) 
                this->changeState(kStateStandingUp);
            
        }else if (joystick->getVelocity().y<-0.45f){
            if (this->getCharacterState() !=kStateCrouching) 
                this->changeState(kStateCrouching);
            
        }else if (joystick->getVelocity().x !=0.0f){
            if (this->getCharacterState() !=kStateWalking) 
                this->changeState(kStateWalking);
            this->applyJoystick(joystick,deltaTime);
        }
    }
 
    if (this->numberOfRunningActions() == 0) {
        if (this->getCharacterHealth() <= 0.0f) {
            this->changeState(kStateDead);
        }else if (this->getCharacterState() == kStateIdle){
            millisecondsStayingIdle = millisecondsStayingIdle + deltaTime;
            if (millisecondsStayingIdle > kVikingIdleTimer) {
                this->changeState(kStateBreathing);
            }
        }else if ((this->getCharacterState() != kStateCrouching) && (this->getCharacterState() != kStateIdle)){
            millisecondsStayingIdle = 0.0f;
         
            this->changeState(kStateIdle);
            
        }
    }

   
}
#pragma mark -
CCRect Viking::adjustedBoundingBox() {
    // Adjust the bouding box to the size of the sprite
    // without the transparent space
//    CCRect vikingBoundingBox = this->boundingBox();
  
    CCRect vikingBoundingBox = CCRect::CCRect(0,0,100.0f,100.0f);
    float xOffset;
    float xCropAmount = vikingBoundingBox.size.width * 0.5482f;
    float yCropAmount = vikingBoundingBox.size.height * 0.095f;
    
    if (this->isFlipX() == false) {
        // Viking is facing to the rigth, back is on the left
        xOffset = vikingBoundingBox.size.width * 0.1566f;
    } else {
        // Viking is facing to the left; back is facing right
        xOffset = vikingBoundingBox.size.width * 0.4217f;
    }
    vikingBoundingBox =
    CCRectMake(vikingBoundingBox.origin.x + xOffset,
               vikingBoundingBox.origin.y,
               vikingBoundingBox.size.width - xCropAmount,
               vikingBoundingBox.size.height - yCropAmount);
    
    if (characterState == kStateCrouching) {
        // Shrink the bounding box to 56% of height
        // 88 pixels on top on iPad
        vikingBoundingBox = CCRectMake(vikingBoundingBox.origin.x,
                                       vikingBoundingBox.origin.y,
                                       vikingBoundingBox.size.width,
                                       vikingBoundingBox.size.height * 0.56f);
    }
    
    return vikingBoundingBox;
};
#pragma mark -
void Viking::initAnimations() {
    
    this->setBreathingAnim(this->loadPlistForAnimationWithName("breathingAnim",typeid(this).name()));
    this->setBreathingMalletAnim(this->loadPlistForAnimationWithName("breathingMalletAnim",typeid(this).name()));
    this->setWalkingAnim(this->loadPlistForAnimationWithName("walkingAnim" ,typeid(this).name()));
    this->setWalkingMalletAnim(this->loadPlistForAnimationWithName("walkingMalletAnim",typeid(this).name()));
    this->setCrouchingAnim(this->loadPlistForAnimationWithName("crouchingAnim" ,typeid(this).name()));
    this->setCrouchingMalletAnim(this->loadPlistForAnimationWithName("crouchingMalletAnim",typeid(this).name()));
    this->setStandingUpAnim(this->loadPlistForAnimationWithName("standingUpAnim",typeid(this).name()));
    this->setStandingUpMalletAnim(this->loadPlistForAnimationWithName("standingUpMalletAnim",typeid(this).name()));
    this->setJumpingAnim(this->loadPlistForAnimationWithName("jumpingAnim"  ,typeid(this).name()));
    this->setJumpingMalletAnim(this->loadPlistForAnimationWithName("jumpingMalletAnim",typeid(this).name()));
    this->setAfterJumpingAnim(this->loadPlistForAnimationWithName("afterJumpingAnim",typeid(this).name()));
    this->setAfterJumpingMalletAnim(this->loadPlistForAnimationWithName("afterJumpingMalletAnim",typeid(this).name()));
    this->setRightPunchAnim(this->loadPlistForAnimationWithName("rightPunchAnim"  ,typeid(this).name()));
    this->setLeftPunchAnim(this->loadPlistForAnimationWithName("leftPunchAnim" ,typeid(this).name()));
    this->setMalletPunchAnim(this->loadPlistForAnimationWithName("malletPunchAnim" ,typeid(this).name()));
// Taking Damage and Death
    this->setPhaserShockAnim(this->loadPlistForAnimationWithName("phaserShockAnim" ,typeid(this).name()));
    this->setVikingDeathAnim(this->loadPlistForAnimationWithName("vikingDeathAnim" ,typeid(this).name()));

}

#pragma mark -
bool Viking::init() {
    bool  bRet =true;// = GameCharacter::init();
    if( bRet) {
//        joystick = nil;
//        jumpButton = nil;
//        attackButton = nil;
        this->setGameObjectType(kVikingType);
        myLastPunch = kRightHook;
        millisecondsStayingIdle = 0.0f;
        isCarryingMallet = false;
        this->initAnimations();
        
    }
    return bRet;
}
Viking* Viking::createWithSpriteFrameName(const char *pszSpriteFrameName) {
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
    
    Viking *pobSprite = new Viking();
    if (pobSprite && pobSprite->initWithSpriteFrame(pFrame))
    {
        pobSprite->init();//create with  这个方法可能要重写
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}