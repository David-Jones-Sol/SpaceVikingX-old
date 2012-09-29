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
#include "SneakyJoystick.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystickSkinnedBase.h"
#include "Constants.h"
#include "CommonProtocols.h"
#include "Viking.h"
#include "RadarDish.h"
USING_NS_CC;
class GameplayLayer:public CCLayer,GameplayLayerDelegate{
public:
    CREATE_FUNC(GameplayLayer);
    virtual bool init();
//      ~GameplayLayer();
     void createObjectOfType(GameObjectType objectType,int initialHealth,CCPoint spawnLocation,int ZValue );
     void createPhaseWithDirection(PhaserDirection phaserDirection,CCPoint spawnPosition);
    void initJoystickAndButtons();
//    void applyJoystick(SneakyJoystick *aJoystick, CCNode *tempNode, float deltaTime);
    void update(float deltaTime);
private:
    CCSprite *vikingSprite;
    SneakyJoystick *leftJoystick;
    SneakyButton *jumpButton;
    SneakyButton *attackButton;
    CCSpriteBatchNode *sceneSpriteBatchNode;
};


#endif
