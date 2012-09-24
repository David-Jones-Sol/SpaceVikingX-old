//
//  RadarDish.cpp
//  SpaceVikingX
//
//  Created by anjun on 12-9-19.
//
//

#include "RadarDish.h"

RadarDish::~RadarDish(){
    CC_SAFE_RELEASE(tiltingAnim);
    CC_SAFE_RELEASE(transmittingAnim);
    CC_SAFE_RELEASE(takingAHitAnim);
    CC_SAFE_RELEASE(blowingUpAnim);
}
void RadarDish::changeState(CharacterStates newState){
    this->stopAllActions();
    void *action = NULL;
    this->setCharacterState(newState);
    
    switch (newState) {
        case kStateSpawning:
            CCLOG("RadarDish->Starting the Spawning Animation");
            action =CCAnimate::create(tiltingAnim);
            break;
            
        case kStateIdle:
            CCLOG("RadarDish->Changing State to Idle");
            action = CCAnimate::create(transmittingAnim);
            break;
            
        case kStateTakingDamage:
            CCLOG("RadarDish->Changing State to TakingDamage");
            characterHealth =
            characterHealth - vikingCharacter->getWeaponDamage();
            if (characterHealth <= 0.0f) {
                this->changeState(kStateDead);
            } else {
                action = CCAnimate::create(takingAHitAnim);
            }
            break;
            
        case kStateDead:
            CCLOG("RadarDish->Changing State to Dead");
            action = CCAnimate::create(blowingUpAnim);
            break;
            
        default:
            CCLOG("Unhandled state %d in RadarDish", newState);
            break;
    }
    if (action != NULL) {
        this->runAction((CCAction*)action);
    }
}
void RadarDish::updateStateWithDeltaTime(float deltaTime, CCArray *listOfGameObjects){
    if (characterState == kStateDead)
        return;                                                    // 1
    
    vikingCharacter =
    (GameCharacter*)this->getParent()->getChildByTag(kVikingSpriteTagValue);
                  
    
    
    CCRect vikingBoudingBox =
    vikingCharacter->adjustedBoundingBox();                 // 3
    CharacterStates vikingState = vikingCharacter->getCharacterState();

    
    // Calculate if the Viking is attacking and nearby
    if ((vikingState == kStateAttacking) &&
        (CCRect::CCRectIntersectsRect(vikingCharacter->adjustedBoundingBox(), vikingBoudingBox))) {                                              // 5
        if (characterState != kStateTakingDamage) {
            // If RadarDish is NOT already taking Damage
            this->changeState(kStateTakingDamage);
            return;
        }
    }
    
    if ((this->numberOfRunningActions() == 0) &&
        (characterState != kStateDead)) {
        CCLOG("Going to Idle");
        this->changeState(kStateIdle);                 // 6
        return;
    }
    
}
CCRect RadarDish::adjustedBoundingBox(){
}
void RadarDish::initAnimations(){
    
    this->setTiltingAnim(this->loadPlistForAnimationWithName("tiltingAnim",typeid(this).name()));
    this->setTransmittingAnim(this->loadPlistForAnimationWithName("transmittingAnim"
                                                             ,typeid(this).name()));
    this->setTakingAHitAnim(this->loadPlistForAnimationWithName("takingAHitAnim"
                                                             ,typeid(this).name()));
    this->setBlowingUpAnim(this->loadPlistForAnimationWithName("blowingUpAnim"
                                                             ,typeid(this).name()));

}
bool RadarDish::init(){
    bool  bRet = GameCharacter::init();
    if( bRet) {
        CCLOG("### RadarDish initialized");
        this->initAnimations();                                  // 1
        characterHealth = 100.0f;                                // 2
        gameObjectType = kEnemyTypeRadarDish;                    // 3
        this->changeState(kStateSpawning);
    }
    return bRet;
  
}
RadarDish* RadarDish::createWithSpriteFrameName(const char *pszSpriteFrameName) {
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
    
    RadarDish *pobSprite = new RadarDish();
    pobSprite->init();
    if (pobSprite && pobSprite->initWithSpriteFrame(pFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}