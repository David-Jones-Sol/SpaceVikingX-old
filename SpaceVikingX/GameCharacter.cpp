//
//  GameCharacter.cpp
//  SpaceVikingX
//
//  Created by anjun on 12-9-19.
//
//

#include "GameCharacter.h"
int GameCharacter::getWeaponDamage(){
    CCLOG("getWeaponDamage should be overriden");
    return 0;
}
void GameCharacter::checkAndClampSpritePosition(){
    CCPoint currentSpritePosition = this->getPosition();
    if (currentSpritePosition.x < 24.0f) {
        this->setPosition(ccp(24.0f, currentSpritePosition.y));
    } else if (currentSpritePosition.x > 456.0f) {
        this->setPosition(ccp(456.0f, currentSpritePosition.y));
    }
}
/*
 
 @implementation GameCharacter
 @synthesize characterHealth;
 @synthesize characterState;
 
 -(void) dealloc {
 [super dealloc];
 }
 
 -(int)getWeaponDamage {
 // Default to zero damage
 CCLOG(@"getWeaponDamage should be overriden");
 return 0;
 }
 
 -(void)checkAndClampSpritePosition {
 CGPoint currentSpritePosition = [self position];
 
 if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
 // Clamp for the iPad
 if (currentSpritePosition.x < 30.0f) {
 [self setPosition:ccp(30.0f, currentSpritePosition.y)];
 } else if (currentSpritePosition.x > 1000.0f) {
 [self setPosition:ccp(1000.0f, currentSpritePosition.y)];
 }
 } else {
 // Clamp for iPhone, iPhone 4, or iPod touch
 if (currentSpritePosition.x < 24.0f) {
 [self setPosition:ccp(24.0f, currentSpritePosition.y)];
 } else if (currentSpritePosition.x > 456.0f) {
 [self setPosition:ccp(456.0f, currentSpritePosition.y)];
 }
 }
 }
 @end

*/