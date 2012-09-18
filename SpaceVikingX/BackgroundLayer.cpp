//
//  BackgroundLayer.cpp
//  SpaceVikingX
//
//  Created by anjun on 12-9-17.
//
//

#include "BackgroundLayer.h"
USING_NS_CC;

bool BackgroundLayer::init(){
    bool bRet = false;
    bRet = CCLayer::init();
	if ( bRet )
	{
	
        CCSprite* backgroundImage = CCSprite::create("backgroundiPhone.png");
         
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
       
        backgroundImage->setPosition(
         ccp(screenSize.width/2, screenSize.height/2));
        this->addChild(backgroundImage,0,0);
    }
    return bRet;
}