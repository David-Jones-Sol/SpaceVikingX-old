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
USING_NS_CC;

static GameScene* create(){
    GameScene *pRet = new GameScene();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}
bool GameScene::init(){
    bool bRet = false;
    bRet =  CCScene::init();
    if(!bRet){
        BackgroundLayer *backgroundLayer =BackgroundLayer::create();
        this->addChild(backgroundLayer,0);
    }
    return bRet;
}
