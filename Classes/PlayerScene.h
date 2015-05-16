//
//  PlayerScene.h
//  KinectGame
//
//  Created by ArcherPeng on 15/3/13.
//
//

#ifndef __KinectGame__PlayerScene__
#define __KinectGame__PlayerScene__


#include "SocketHelper.h"
class PlayerScene:public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PlayerScene);
    void callback(cocos2d::EventCustom * event);
    void handDataCallback(cocos2d::EventCustom * event);
    void clickCallback(cocos2d::EventCustom * event);
    void newAnime(float f);
    cocos2d::Vec2 getPos(int x,int y);
    
private:
    cocos2d::Vector<cocos2d::Sprite *> vecAnime;
    cocos2d::Sprite * player;
    void diaoxue();
    int blood = 100;
    cocos2d::Label * bloodLabel;
    
};

#endif /* defined(__KinectGame__PlayerScene__) */
