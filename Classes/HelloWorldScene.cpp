#include "HelloWorldScene.h"
#include "ODSocket.h"
#include <pthread.h>
#include "cocostudio/CocoStudio.h"
#include "HandData.h"
#include "Config.h"
#include "PlayerScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

////创建Socket
//ODSocket s_client;
//void * getMessage(void *ptr)
//{//接收消息
//    //    ODSocket *nowScoket=(ODSocket *)ptr;//接收线程传递过来的参数
//    std::cout<<"线程启动成功"<<endl;
//    char buf[1024*64];
//    while (s_client.Recv(buf, sizeof(buf)))
//    {
//        //接收服务器消息
//        std::cout << "recv --> "<<buf<<std::endl;
////        s_client.Clean();
//    }
//    //断开链接了
//    s_client.Close();
//    return nullptr;
//}


Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
//    menu->setScale(20);
    
    auto lis = EventListenerTouchOneByOne::create();
    lis->onTouchBegan = CC_CALLBACK_2(HelloWorld::touchbenganCall, this);
    lis->onTouchEnded = CC_CALLBACK_2(HelloWorld::touchendedCall, this);
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, this);
    auto sh = SocketHelper::getInstance();
    std::string jsonStr ="{\"methodId\":100,\"argId\":1007,\"argName\":\"CloestHandData\"}";
    sh->send(jsonStr);
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("SocketMessage",CC_CALLBACK_1(HelloWorld::callback, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("handData",CC_CALLBACK_1(HelloWorld::handDataCallback, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("click",CC_CALLBACK_1(HelloWorld::clickCallback, this));
    
    auto label = Label::createWithSystemFont("下面，将确定体感控制位置，请将您的手指向屏幕上显示的文字的位置\n并点击控制器。", "Arial", 26);
    label->setTag(1000);
    label->setPosition(this->getContentSize().width/2,this->getContentSize().height/2);
    label->setLocalZOrder(100);
    this->addChild(label);
    
    auto label1 = Label::createWithSystemFont("请将手指向本文字所在位置，以确定屏幕上边体感控制位置", "Arial", 26);
    label1->setPosition(this->getContentSize().width/2,this->getContentSize().height-label1->getContentSize().height/2);
    label1->setLocalZOrder(100);
    label1->setTag(1001);
    this->addChild(label1);
    
    auto label2 = Label::createWithSystemFont("请将手指向本文字所在位置，以确定屏幕下边体感控制位置", "Arial", 26);
    label2->setPosition(this->getContentSize().width/2,label2->getContentSize().height/2);
    label2->setLocalZOrder(100);
    label2->setTag(1002);
    this->addChild(label2);
    
    auto label3 = Label::createWithSystemFont("请\n确\n定\n屏\n幕\n左\n边\n控\n制\n位\n置", "Arial", 26);
    label3->setPosition(label3->getContentSize().width/2,this->getContentSize().height/2);
    label3->setLocalZOrder(100);
    label3->setTag(1003);
    this->addChild(label3);
    
    auto label4 = Label::createWithSystemFont("请\n确\n定\n屏\n幕\n右\n边\n控\n制\n位\n置", "Arial", 26);
    label4->setPosition(this->getContentSize().width-label4->getContentSize().width/2,this->getContentSize().height/2);
    label4->setLocalZOrder(100);
    label4->setTag(1004);
    this->addChild(label4);
    
//    label->setVisible(false);
    label1->setVisible(false);
    label2->setVisible(false);
    label3->setVisible(false);
    label4->setVisible(false);
    
    
    
    
    return true;
}
bool HelloWorld::touchbenganCall(cocos2d::Touch*, cocos2d::Event*)
{
    return true;
}
void HelloWorld::touchendedCall(cocos2d::Touch*, cocos2d::Event*)
{
    std::string jsonStr ="{\"methodId\":102}";
    SocketHelper::getInstance()->send(jsonStr);
    
}
void HelloWorld::callback(EventCustom * event)
{
    do
    {
//        return;
        auto c =(char*)event->getUserData();
        CC_BREAK_IF(!c);
        std::string str=c;
        jiexi(str);
//        do {
//            int res = -1;
//            int res1 = 0;
//            do {
//                
//                res1 = str.find_first_of("}{",res1+1);
//                CCLOG("res %d",res1);
//                if (res1==-1) {
//                    res = -1;
//                    break;
//                }
//                if (str[res1+1]!='}'||str[res1+2]!='{')
//                {
//                    res=-1;
//                }
//                else
//                {
//                    res = res1;
//                    break;
//                }
//            } while (true);
//            
//            CCLOG("res %d",res);
//            if(res == -1)
//            {
//                jiexi(str);
//                break;
//            }
//            else
//            {
//                std::string st = str.substr(0,res+1);
//                CCLOG("st  %s",st.c_str());
//                jiexi(st);
//                str = str.substr(res+1,str.size());
//                
//            }
//        } while (true);
        
        
    } while (false);
    
    
    
}
void HelloWorld::jiexi (std::string str)
{
    do
    {
        //        return;
        
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
            cocos2d::EventCustom event("handData");
            HandData*hd = new HandData();
            const rapidjson::Value &jx = jsonData["x"];
            hd->x = jx.GetInt();
            const rapidjson::Value &jy = jsonData["y"];
            hd->y = jy.GetInt();
            const rapidjson::Value &jz = jsonData["z"];
            hd->z = jz.GetInt();
            event.setUserData((void *) hd);
            Config::getInstance()->handData.x = hd->x;
            Config::getInstance()->handData.y = hd->y;
            Config::getInstance()->handData.z = hd->z;
            cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
            delete hd;
        }
        else if(methodId == 9000)
        {
            cocos2d::EventCustom event("click");
            cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
            
        }
        
        
        
        
    } while (false);
}
void HelloWorld::clickCallback(cocos2d::EventCustom * event)
{
    CCLOG("Click");
    SimpleAudioEngine::getInstance()->playEffect("res/1.mp3");
    //手机屏幕被点击
    switch (step) {
        case 0:
            getChildByTag(1000)->setVisible(false);
            getChildByTag(1001)->setVisible(true);
            break;
        case 1:
            getChildByTag(1001)->setVisible(false);
            getChildByTag(1002)->setVisible(true);
            Config::getInstance()->upY = Config::getInstance()->handData.y;
            break;
        case 2:
            getChildByTag(1002)->setVisible(false);
            getChildByTag(1003)->setVisible(true);
            Config::getInstance()->downY = Config::getInstance()->handData.y;
            break;
        case 3:
            getChildByTag(1003)->setVisible(false);
            getChildByTag(1004)->setVisible(true);
            Config::getInstance()->LeftX = Config::getInstance()->handData.x;
            break;
        case 4:
            getChildByTag(1004)->setVisible(false);
            getChildByTag(1000)->setVisible(true);
            static_cast<Label*>(getChildByTag(1000))->setString("再点击一下遥控器开始游戏！");
            Config::getInstance()->RightX = Config::getInstance()->handData.x;
            break;
        case 5:
        {
            Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("SocketMessage");
            Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("handData");
            Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("click");
            auto gameScene = PlayerScene::createScene();
            Director::getInstance()->replaceScene(gameScene);
            //else
            break;
        }
        default:
            break;
    }
    ++step;
}

void HelloWorld::handDataCallback(cocos2d::EventCustom * event)
{
    auto * handData = (HandData*)event->getUserData();
////    handData->x
//    Config::getInstance()->handData.x = handData->x;
//    Config::getInstance()->handData.y = handData->y;
//    Config::getInstance()->handData.z = handData->z;
    
//    CCLOG("X %d  Y %d  Z %d",handData->x,handData->y,handData->z);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    std::string jsonStr ="{\"methodId\":102}";
    SocketHelper::getInstance()->send(jsonStr);

}
