//  CommonProtocols.h
//  SpaceViking

#ifndef __SpaceVikingX__CommonProtocols__
#define __SpaceVikingX__CommonProtocols__
typedef enum {
    kDirectionLeft,
    kDirectionRight
} PhaserDirection;

typedef enum {
    kStateSpawning,
    kStateIdle,
    kStateCrouching,
    kStateStandingUp,
    kStateWalking,
    kStateAttacking,
    kStateJumping,
    kStateBreathing,
    kStateTakingDamage,
    kStateDead,
    kStateTraveling,
    kStateRotating, 
    kStateDrilling,
    kStateAfterJumping
} CharacterStates; // 1

typedef enum {
    kObjectTypeNone,
    kPowerUpTypeHealth,
    kPowerUpTypeMallet,
    kEnemyTypeRadarDish,
    kEnemyTypeSpaceCargoShip,
    kEnemyTypeAlienRobot,
    kEnemyTypePhaser,
    kVikingType,
    kSkullType,
    kRockType,
    kMeteorType,
    kFrozenVikingType,
    kIceType,
    kLongBlockType,
    kCartType,
    kSpikesType,
    kDiggerType,
    kGroundType    
} GameObjectType;

class GameplayLayerDelegate
{
public:
    virtual void createObjectOfType(GameObjectType objectType,int initialHealth,cocos2d::CCPoint spawnLocation,int ZValue )=0;
    virtual void createPhaseWithDirection(PhaserDirection phaserDirection,cocos2d::CCPoint spawnPosition)=0;
};
#endif /* defined(__SpaceVikingX__CommonProtocols__) */
