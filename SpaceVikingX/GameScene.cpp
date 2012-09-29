//
//  GameScene.cpp
//  SpaceVikingX
//
//  Created by anjun on 12-9-17.
//
//

#include "GameScene.h"
#include "BackgroundLayer.h"
#include "GameplayLayer.h"
#include "ARocker.h"


bool GameScene::init(){
    bool bRet = false;
    bRet =  CCScene::init();
    if(bRet){
        BackgroundLayer *backgroundLayer =BackgroundLayer::create();
        this->addChild(backgroundLayer,0);
        GameplayLayer *gameplayLayer =GameplayLayer::create();
        this->addChild(gameplayLayer,5);
        
//        CCSprite *aJsSprite = CCSprite::create("joystickUp.png");
//        CCSprite *aJsBackGround = CCSprite::create("joystickDown.png");
//        ARocker *aRocker =   ARocker::ARockerWithCenter(ccp(60,60), 30.0f, aJsSprite, aJsBackGround, true);
//        this->addChild(aRocker,2);
    }
    return bRet;
}
