//
//  ARocker.h
//  SpaceVikingX
//
//  Created by anjun on 12-9-17.
//
//

#ifndef __SpaceVikingX__ARocker__
#define __SpaceVikingX__ARocker__

#include "cocos2d.h"
USING_NS_CC;
class ARocker:public cocos2d::CCLayer{
public:
    
    static ARocker*  ARockerWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole);
  
    void Active();
  
    void Inactive();
private:
    
    ARocker * initWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole);
    
    CCPoint centerPoint;//摇杆中心
    
    CCPoint currentPoint;//摇杆当前位置
    
    bool active;//是否激活摇杆
    
    float radius;//摇杆半径
    
    CCSprite *jsSprite;
    
    bool isFollowRole;//是否跟随用户点击
    
    CCPoint getDirection();
    
    float getVelocity();
    
    void  updatePos(CCTime dt);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    CREATE_FUNC(ARocker);
};

#endif /* defined(__SpaceVikingX__ARocker__) */
