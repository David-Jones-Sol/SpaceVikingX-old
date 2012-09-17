//
//  BackgroundLayer.cpp
//  SpaceVikingX
//
//  Created by anjun on 12-9-17.
//
//

#include "BackgroundLayer.h"
USING_NS_CC;
BackgroundLayer * BackgroundLayer::create(){
    BackgroundLayer * pRet = new BackgroundLayer();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool BackgroundLayer::init(){
	if ( !CCLayer::init() )
	{
		return false;
	}
    CCSprite* backgroundImage = CCSprite::create("backgroundiPhone.png");
     
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
   
    backgroundImage->setPosition(
     ccp(screenSize.width/2, screenSize.height/2));
    this->addChild(backgroundImage,0,0);
    
    return true;
}