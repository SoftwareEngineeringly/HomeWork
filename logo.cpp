#include "logo.h"

#include "GameData.h"
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool logo::init()
{
    bool flag=false;
    if(!Layer::init())
    {
        return false;
    }
    flag=true;
	Size winSize=Director::getInstance()->getWinSize();
    Sprite *sprite=Sprite::create("firstload.jpg");
    sprite->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(sprite);

    if(!CCUserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml"))
    {
        CCUserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml", true);
        CCUserDefault::getInstance()->flush();

        CCUserDefault::getInstance()->setBoolForKey("isBgMusic", true);
        CCUserDefault::getInstance()->flush();
        CCUserDefault::getInstance()->setBoolForKey("isEffectMusic", true);
        CCUserDefault::getInstance()->flush();
    }else{

        bool isBgmusicOpen = CCUserDefault::getInstance()->getBoolForKey("isBgMusic");
        GameData::Inst()->isMusicBgOpen=isBgmusicOpen;
        bool isEffectOpen = CCUserDefault::getInstance()->getBoolForKey("isEffectMusic");
        GameData::Inst()->isEffectOpen=isEffectOpen;
    }
   

    CallFunc *callLoad=CallFunc::create(this, SEL_CallFunc(&logo::loading));
    
    FadeOut *out=FadeOut::create(4.0f);
    CallFunc *call=CallFunc::create(this, SEL_CallFunc(&logo::replace));
    FiniteTimeAction *finite=Sequence::create(callLoad,out,call,NULL);
    sprite->runAction(finite);
      
    return flag;
}
Scene* logo::scene()
{
    Scene *scene=Scene::create();
    logo *layer = logo::create();
    scene->addChild(layer);
    return scene;
}
void logo::loading()
{

}
void logo::replace()
{
	Scene *scene = WelcomeLayer::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f,scene));
}