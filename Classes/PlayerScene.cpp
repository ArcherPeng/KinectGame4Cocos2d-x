//
//  PlayerScene.cpp
//  KinectGame
//
//  Created by ArcherPeng on 15/3/13.
//
//

#include "PlayerScene.h"
#include "cocostudio/CocoStudio.h"
#include "Config.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
cocos2d::Scene* PlayerScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayerScene::create();
    scene->addChild(layer);
    return scene;
    
}
bool PlayerScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
//    SimpleAudioEngine::getInstance()->playEffect("res/1.mp3");
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("SocketMessage",CC_CALLBACK_1(PlayerScene::callback, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("handData",CC_CALLBACK_1(PlayerScene::handDataCallback, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("click",CC_CALLBACK_1(PlayerScene::clickCallback, this));
    this->schedule(schedule_selector(PlayerScene::newAnime), 2);
    this->player = Sprite::create("res/gun.png");
    int xx = Director::getInstance()->getVisibleSize().width/2;
    int yy = Director::getInstance()->getVisibleSize().height/2;
    xx -= 611*0.6;
    yy -= 911*0.6;
    this->player->setPosition(xx,yy);
    this->player->setAnchorPoint(Vec2(0,0));
    this->player->setLocalZOrder(100);
    this->player->setScale(0.6);
    this->addChild(this->player);
    auto spBg =  Sprite::create("res/bg.jpg");
    spBg->setPosition(Director::getInstance()->getVisibleSize().width/2,Director::getInstance()->getVisibleSize().height/2);
    this->addChild(spBg);
    this->bloodLabel = Label::createWithSystemFont("血量:100", "Arial", 26);
    this->bloodLabel->setPosition(this->bloodLabel->getContentSize().width/2,this->bloodLabel->getContentSize().height/2);
    this->bloodLabel->setLocalZOrder(100);
    this->addChild(this->bloodLabel);
    return true;
}
void PlayerScene::diaoxue()
{
    this->blood -= 1;
    this->bloodLabel->setString(StringUtils::format("血量:%d",this->blood));
    if (this->blood<0)
    {
        this->blood = 100;
    }
}
cocos2d::Vec2 PlayerScene::getPos(int x,int y)
{
    float xx = (x-Config::getInstance()->LeftX);
    xx=xx/(Config::getInstance()->RightX-Config::getInstance()->LeftX);
    xx=xx*Director::getInstance()->getVisibleSize().width;
    float yy = (y-Config::getInstance()->downY);
    yy=yy/(Config::getInstance()->upY-Config::getInstance()->downY);
    yy=yy*Director::getInstance()->getVisibleSize().height;
    xx -= 611*0.6;
    yy -= 911*0.6;
    return Vec2(xx, yy);
}
void PlayerScene::newAnime(float f)
{
    auto sp = Sprite::create("res/person.png");
    auto visableSize = Director::getInstance()->getVisibleSize();
    
    int y =CCRANDOM_0_1()*(visableSize.height-sp->getContentSize().height)+sp->getContentSize().height/2;
    int x =CCRANDOM_0_1()*(visableSize.height-sp->getContentSize().width)+sp->getContentSize().width/2;
    
    sp->setPosition(Vec2(x,y));
    this->addChild(sp);
    sp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(3),CallFunc::create(CC_CALLBACK_0(PlayerScene::diaoxue, this)), NULL)));
    vecAnime.pushBack(sp);
}
void PlayerScene::callback(cocos2d::EventCustom * event)
{
    do
    {
        auto c =(char*)event->getUserData();
        CC_BREAK_IF(!c);
        std::string str=c;
        rapidjson::Document jsonData;
        jsonData.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
        if (jsonData.HasParseError())
        {
            CCLOG("GetParseError : %s",jsonData.GetParseError());
            break;
        }
        if(!jsonData.IsObject())
        {
            CCLOG("not Object");
            break;
        }
        
        
        //是否有此成员
        if(!jsonData.HasMember("methodId"))
        {
            CCLOG("no Member methodId");
            break;
        }
        
        const rapidjson::Value &jMethodId = jsonData["methodId"];
        int methodId = jMethodId.GetInt();      //得到int值
        if (methodId == 1007)
        {
//            cocos2d::EventCustom event("handData");
            HandData*hd = new HandData();
            const rapidjson::Value &jx = jsonData["x"];
            hd->x = jx.GetInt();
            const rapidjson::Value &jy = jsonData["y"];
            hd->y = jy.GetInt();
            const rapidjson::Value &jz = jsonData["z"];
            hd->z = jz.GetInt();
//            event.setUserData((void *) hd);
            Config::getInstance()->handData.x = hd->x;
            Config::getInstance()->handData.y = hd->y;
            Config::getInstance()->handData.z = hd->z;
//            cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
//            CCLOG("X %d  Y %d  Z %d",hd->x,hd->y,hd->z);
            this->player->setPosition(getPos(hd->x,hd->y));
            delete hd;
        }
        else if(methodId == 9000)
        {
            cocos2d::EventCustom event("click");
            cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
            
        }
    } while (false);
}
void PlayerScene::handDataCallback(cocos2d::EventCustom * event)
{
//    auto * handData = (HandData*)event->getUserData();
    //    handData->x
//    CCLOG("X %d  Y %d  Z %d",handData->x,handData->y,handData->z);
//    Config::getInstance()->handData.x = handData->x;
//    Config::getInstance()->handData.y = handData->y;
//    Config::getInstance()->handData.z = handData->z;
//    this->player->setPosition(getPos(Config::getInstance()->handData.x,Config::getInstance()->handData.y));
}
void PlayerScene::clickCallback(cocos2d::EventCustom * event)
{
    SimpleAudioEngine::getInstance()->playEffect("res/1.mp3");
    float xx = (Config::getInstance()->handData.x-Config::getInstance()->LeftX);
    xx=xx/(Config::getInstance()->RightX-Config::getInstance()->LeftX);
    xx=xx*Director::getInstance()->getVisibleSize().width;
    float yy = (Config::getInstance()->handData.y-Config::getInstance()->downY);
    yy=yy/(Config::getInstance()->upY-Config::getInstance()->downY);
    yy=yy*Director::getInstance()->getVisibleSize().height;
    for (int i = 0; i < vecAnime.size(); ++i)
    {
        bool isKill = vecAnime.at(i)->getBoundingBox().intersectsRect(Rect(xx-0.5,yy-0.5, 1, 1));
        if (isKill)
        {
            vecAnime.at(i)->stopAllActions();
            vecAnime.at(i)->removeFromParentAndCleanup(true);
            vecAnime.erase(i);
        }
    }
}