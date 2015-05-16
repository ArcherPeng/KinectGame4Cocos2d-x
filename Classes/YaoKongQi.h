//
//  YaoKongQi.h
//  KinectGame
//
//  Created by ArcherPeng on 15/3/13.
//
//

#ifndef __KinectGame__YaoKongQi__
#define __KinectGame__YaoKongQi__

#include "cocos2d.h"
#include "SocketHelper.h"
class YaoKongQi : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void touchendedCall(cocos2d::Touch*, cocos2d::Event*);
    bool touchbenganCall(cocos2d::Touch*, cocos2d::Event*);
    
    
    void jiexi (std::string str);
    // implement the "static create()" method manually
    CREATE_FUNC(YaoKongQi);
    void callback(cocos2d::EventCustom * event);
    void handDataCallback(cocos2d::EventCustom * event);
    void clickCallback(cocos2d::EventCustom * event);
    int step = 0;
};
#endif /* defined(__KinectGame__YaoKongQi__) */
