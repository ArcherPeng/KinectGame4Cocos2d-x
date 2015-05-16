#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SocketHelper.h"

class HelloWorld : public cocos2d::Layer
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
    CREATE_FUNC(HelloWorld);
    void callback(cocos2d::EventCustom * event);
    void handDataCallback(cocos2d::EventCustom * event);
    void clickCallback(cocos2d::EventCustom * event);
    int step = 0;
};

#endif // __HELLOWORLD_SCENE_H__
