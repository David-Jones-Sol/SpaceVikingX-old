//
//  GameplayLayer.cpp
//  SpaceVikingX
//
//  Created by anjun on 12-9-17.
//
//

#include "GameplayLayer.h"
USING_NS_CC;
GameplayLayer * GameplayLayer::create(){
    GameplayLayer * pRet = new GameplayLayer();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool GameplayLayer::init(){
	if ( !CCLayer::init() )
	{
		return false;
	}
    CCSprite* backgroundImage = CCSprite::create("sv_anim_1.png");
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    backgroundImage->setPosition(
                                 ccp(screenSize.width/2, screenSize.height/2));
    this->addChild(backgroundImage,0,0);
    
    return true;
}