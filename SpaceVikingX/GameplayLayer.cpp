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
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        this->setTouchEnabled(true);
        srandom(time(NULL)); // Seeds the random number generator

        CCSpriteFrameCache::sharedSpriteFrameCache()->
         addSpriteFramesWithFile("scene1atlasiPhone.plist");          
        sceneSpriteBatchNode =
       
        CCSpriteBatchNode::create("scene1atlasiPhone.png");
        
        this->addChild(sceneSpriteBatchNode,0);                // 3
        this->initJoystickAndButtons();                           // 4
        Viking *viking = Viking::createWithSpriteFrameName("sv_anim_1.png");
        viking->setJoystick(leftJoystick);
        viking->setjumpButton(jumpButton);
        viking->setattackButton(attackButton);
        viking->setPosition(ccp(screenSize.width*0.35f,screenSize.height*0.14f));
        viking->setCharacterHealth(100);

        sceneSpriteBatchNode->addChild(viking,kVikingSpriteZValue,kVikingSpriteTagValue);
        this->createObjectOfType(kEnemyTypeRadarDish, 100, ccp(screenSize.width*0.878f,screenSize.height*0.13f), 10);

        this->scheduleUpdate();

    }
    return bRet;
}

void GameplayLayer::createObjectOfType(GameObjectType objectType,int initialHealth,cocos2d::CCPoint spawnLocation,int ZValue ){
    if (objectType == kEnemyTypeRadarDish) {
        CCLOG("Creating the Radar Enemy");
        RadarDish *radarDish =RadarDish::createWithSpriteFrameName("radar_1.png");
        radarDish->setCharacterHealth(initialHealth);
        radarDish->setPosition(spawnLocation);
        sceneSpriteBatchNode->addChild(radarDish,ZValue,kRadarDishTagValue);

    }
}
void GameplayLayer::createPhaseWithDirection(PhaserDirection phaserDirection,cocos2d::CCPoint spawnPosition){
    CCLOG("Placeholder for chapter 5, see below");
    return;
}
void GameplayLayer::update(float deltaTime)
{
    CCArray *listOfGameObjects = sceneSpriteBatchNode->getChildren();
     GameCharacter* tempChar ;
    for (int i=0; i<listOfGameObjects->count(); ++i) {
        tempChar = (GameCharacter*)listOfGameObjects->objectAtIndex(i);
        tempChar->updateStateWithDeltaTime(deltaTime, listOfGameObjects);
    }

    //    this->applyJoystick(leftJoystick,vikingSprite,deltaTime);
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
//void GameplayLayer::applyJoystick(SneakyJoystick *aJoystick, CCNode *tempNode, float deltaTime)
//{
//    CCPoint scaledVelocity = ccpMult(aJoystick->getVelocity(), 1024.0f); // 1
//    
//    CCPoint newPosition =
//    ccp(tempNode->getPositionX() + scaledVelocity.x * deltaTime,
//        tempNode->getPositionY() + scaledVelocity.y * deltaTime);       // 2
//    tempNode->setPosition(newPosition);                            // 3
//    
//    if (jumpButton->getIsActive() == true) {
//        CCLOG("Jump button is pressed.");                         // 4
//    }
//    if (attackButton->getIsActive() == true) {
//        CCLOG("Attack button is pressed.");                       // 5
//    }
//}

