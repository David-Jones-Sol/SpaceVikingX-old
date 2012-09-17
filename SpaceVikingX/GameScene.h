//
//  GameScene.h
//  SpaceVikingX
//
//  Created by anjun on 12-9-17.
//
//

#ifndef __SpaceVikingX__GameScene__
#define __SpaceVikingX__GameScene__

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "GameplayLayer.h"
class GameScene :public cocos2d::CCScene{
public:
 
    static GameScene *create();
    bool init();

private:
    
};
#endif /* defined(__SpaceVikingX__GameScene__) */
