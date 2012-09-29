//
//  Health.cpp
//  SpaceVikingX
//
//  Created by anjun on 12-9-28.
//
//

#include "Health.h"
Health::~Health(){
    CC_SAFE_DELETE(healthAnim);
}
void Health::changeState(CharacterStates newState){
    if (newState == kStateSpawning){
        void* action = CCRepeatForever::create(CCAnimate::create(healthAnim));
        this->runAction((CCAction*)action);
    }else {
        this->setVisible(false);
        this->removeAllChildrenWithCleanup(true);
    }

}
void Health::updateStateWithDeltaTime(float dt, cocos2d::CCArray *listOfGameObjects){
    float groundHeight = screenSize.height*0.065f;
    if (this->getPosition().y>groundHeight) {
        this->setPosition(ccp(this->getPosition().x,this->getPosition().y-5.0f));
    }
}
void Health::initAnimations(){
    this->setHealthAnim(this->loadPlistForAnimationWithName("healthAnim", typeid(this).name()));
}
bool Health::init(){
    bool bRet=true;
    if (bRet) {
        screenSize = CCDirector::sharedDirector()->getWinSize();
        this->initAnimations();
        this->changeState(kStateSpawning);
        gameObjectType = kPowerUpTypeHealth;
    }
    return bRet;
}
