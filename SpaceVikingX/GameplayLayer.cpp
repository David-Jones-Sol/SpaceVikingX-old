//
//  GameplayLayer.cpp
//  SpaceVikingX
//
//  Created by anjun on 12-9-17.
//
//

#include "GameplayLayer.h"


bool GameplayLayer::init(){
    bool bRet = false;
    bRet = CCLayer::init();
	if ( bRet )
	{
        vikingSprite = CCSprite::create("sv_anim_1.png");
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        vikingSprite->setPosition(ccp(screenSize.width/2, screenSize.height/2));
        this->addChild(vikingSprite,5);

        this->initJoystickAndButtons();
        this->scheduleUpdate();

    }
    return bRet;
}
void GameplayLayer::initJoystickAndButtons() {
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();    
    CCRect joystickBaseDimensions = CCRect(0, 0, 128.0f, 128.0f);                      
    CCRect jumpButtonDimensions = CCRect(0, 0, 64.0f, 64.0f);
    CCRect attackButtonDimensions =  CCRect(0, 0, 64.0f, 64.0f);
    CCPoint joystickBasePosition;                                  
    CCPoint jumpButtonPosition;
    CCPoint attackButtonPosition;
    
 
    // The device is an iPhone or iPod touch.
    CCLOG("Positioning Joystick and Buttons for iPhone");
    joystickBasePosition = ccp(screenSize.width*0.07f,
                               screenSize.height*0.11f);
    
    jumpButtonPosition = ccp(screenSize.width*0.93f,
                             screenSize.height*0.11f);
    
    attackButtonPosition = ccp(screenSize.width*0.93f,
                               screenSize.height*0.35f);
    
    
    SneakyJoystickSkinnedBase *joystickBase =
    SneakyJoystickSkinnedBase::create();
    joystickBase->setPosition(joystickBasePosition);
    joystickBase->setBackgroundSprite(CCSprite::create("dpadDown.png"));

    joystickBase->setThumbSprite(CCSprite::create("joystickDown.png"));

    SneakyJoystick*  joystick=new SneakyJoystick();
    joystick->initWithRect(joystickBaseDimensions);
    joystick->autorelease();
    joystickBase->setJoystick(joystick);
    joystick->retain();
    leftJoystick = joystick;
    this->addChild(joystickBase);
    
    SneakyButtonSkinnedBase *jumpButtonBase = SneakyButtonSkinnedBase::create();

    jumpButtonBase->setPosition(jumpButtonPosition);
    jumpButtonBase->setDefaultSprite(CCSprite::create("jumpUp.png"));
    jumpButtonBase->setActivatedSprite(CCSprite::create("jumpDown.png"));
    jumpButtonBase->setPressSprite(CCSprite::create("jumpDown.png"));
    SneakyButton *button = new SneakyButton();
    button->initWithRect(jumpButtonDimensions);
    button->autorelease();
    jumpButtonBase->setButton(button);
    button->retain();
    jumpButton = button;
   
    jumpButton->setIsToggleable(false);
    this->addChild(jumpButtonBase);

    
    SneakyButtonSkinnedBase *attackButtonBase = SneakyButtonSkinnedBase::create();
    attackButtonBase->setPosition(attackButtonPosition);
    attackButtonBase->setDefaultSprite(CCSprite::create("handUp.png"));                                  
    attackButtonBase->setActivatedSprite(CCSprite::create("handDown.png"));
    attackButtonBase->setPressSprite(CCSprite::create("handDown.png"));
    
    SneakyButton *aButton = new SneakyButton();
    aButton->autorelease();
    aButton->initWithRect(attackButtonDimensions);
    attackButtonBase->setButton(aButton);
    aButton->retain();
    attackButton = aButton;
    attackButton->setIsToggleable(false);
    this->addChild(attackButtonBase);
}
void GameplayLayer::applyJoystick(SneakyJoystick *aJoystick, CCNode *tempNode, float deltaTime)
{
    CCPoint scaledVelocity = ccpMult(aJoystick->getVelocity(), 1024.0f); // 1
    
    CCPoint newPosition =
    ccp(tempNode->getPositionX() + scaledVelocity.x * deltaTime,
        tempNode->getPositionY() + scaledVelocity.y * deltaTime);       // 2
    tempNode->setPosition(newPosition);                            // 3
    
    if (jumpButton->getIsActive() == true) {
        CCLOG("Jump button is pressed.");                         // 4
    }
    if (attackButton->getIsActive() == true) {
        CCLOG("Attack button is pressed.");                       // 5
    }
}
void GameplayLayer::update(float deltaTime)
{

    this->applyJoystick(leftJoystick,vikingSprite,
        deltaTime);
}