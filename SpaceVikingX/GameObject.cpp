//
//  GameObject.cpp
//  SpaceVikingX
//
//  Created by anjun on 12-9-19.
//
//

#include "GameObject.h"

using namespace std;
bool GameObject::init(){
    bool bRet = false;

    CCLOG("GameObject init");
    screenSize = CCDirector::sharedDirector()->getWinSize();
    isActive = true;
    gameObjectType = kObjectTypeNone;
    return bRet;
}


void GameObject::changeState(CharacterStates newState) {
    //CCLOG("GameObject->changeState method should be overriden");
}

void GameObject::updateStateWithDeltaTime(float deltaTime, CCArray *listOfGameObjects) {
    //CCLOG("updateStateWithDeltaTime method should be overriden");
}

CCRect GameObject::adjustedBoundingBox() {
    //CCLOG("GameObect adjustedBoundingBox should be overriden");
    return  boundingBox();
}
CCAnimation* GameObject::loadPlistForAnimationWithName(string animationName ,string className) {
    
    CCAnimation *animationToReturn = NULL;

    // 1: Get the Path to the plist file 
    string fullFileName = className+".plist";
    const char* fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fullFileName.c_str());
 // 2: Read in the plist file
    CCDictionary *plistDictionary = CCDictionary::createWithContentsOfFileThreadSafe(fullPath);
    // 3: If the plistDictionary was null, the file was not found.
    if (plistDictionary == NULL) {
        CCLOG("Error reading plist: %s.plist", className.c_str());
        return NULL; // No Plist Dictionary or file found
    }
    // 4: Get just the mini-dictionary for this animation
    CCDictionary *animationSettings =
     static_cast<CCDictionary*>( plistDictionary->objectForKey(animationName));
    if (animationSettings == NULL) {
        CCLOG("Could not locate AnimationWithName:%s",animationName.c_str());
        return NULL;
    }
    // 5: Get the delay value for the animation
    float animationDelay = animationSettings->valueForKey("delay")->floatValue();

    animationToReturn = CCAnimation::create();
    animationToReturn->setDelayPerUnit(animationDelay);
//    CCDictionary *framesDict = static_cast<CCDictionary*> (plistDictionary->objectForKey("frames"));
//    
//    CCArray *keys = framesDict->allKeys();
//    
//    for (int i = 0 ; i < keys->count(); ++i)
//    {
//        CCString *spriteFileName = static_cast<CCString *> (keys->objectAtIndex(i));
//        CCSpriteFrame* sprite =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFileName->getCString());
//        mAnimation->addSpriteFrame(sprite);
//        
//    }

    
    // 6: Add the frames to the animation
    string animationFramePrefix =
    animationSettings->valueForKey("filenamePrefix")->m_sString;
    string  animationFrames =
    animationSettings->valueForKey("animationFrames")->m_sString;
   
    char *strArr=new char[animationFrames.size()+1];
    strArr[animationFrames.size()]=0;
    memcpy(strArr,animationFrames.c_str(),animationFrames.size());
    
    
    const char* p;
    
    for (p = strtok(strArr, "," );  p;  p = strtok( NULL, "," ))
    {

//       char* frameNumber = *p;
        string frameName = animationFramePrefix+p+".png";
        CCSpriteFrame* sprite =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
        animationToReturn->addSpriteFrame(sprite);
        
  
        
    }

    
    return animationToReturn;
}

