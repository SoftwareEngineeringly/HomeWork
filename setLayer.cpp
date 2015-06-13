#include "setLayer.h"
#include "GameData.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
setLayer::setLayer()
{
    
}
setLayer::~setLayer()
{
    
}
setLayer* setLayer::create()
{
    setLayer * pRet = new setLayer();
    if(pRet && pRet->initWithColor(Color4B(0, 0, 0, 0)))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
bool setLayer::initWithColor(const cocos2d::Color4B &color)
{
    if (!LayerColor::initWithColor(color)) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();

    auto spbg=Sprite::create("setLayerBg.png");
    spbg->setScale(1.f);

    spbg->setPosition(Point(winSize.width/2, winSize.height/2));
    addChild(spbg);

    m_btnBgOpen = MenuItemImage::create("fr_set.png", "fr_set.png", CC_CALLBACK_1(setLayer::menuOpenBgCallback, this));
    m_btnBgClose = MenuItemImage::create("fr_set.png", "fr_set.png", CC_CALLBACK_1(setLayer::menuCloseBgCallback, this));
    m_btnEffectOpen = MenuItemImage::create("fr_set.png", "fr_set.png", CC_CALLBACK_1(setLayer::menuOpenEffectCallback, this));
    m_btnEffectClose = MenuItemImage::create("fr_set.png", "fr_set.png", CC_CALLBACK_1(setLayer::menuCloseEffectCallback, this));
    m_btnBgOpen->setPosition(Point(335,130));
    m_btnBgClose->setPosition(Point(415,130));
    m_btnEffectOpen->setPosition(Point(335,90));
    m_btnEffectClose->setPosition(Point(415,90));
    auto menu=Menu::create(m_btnBgOpen,m_btnBgClose,m_btnEffectOpen,m_btnEffectClose, NULL);
    menu->setAnchorPoint(Point::ZERO);
    menu->setPosition(Point(0,0));

    spbg->addChild(menu);
    m_spchose = Sprite::create("chose_set.png");
    m_spchose2 = Sprite::create("chose_set.png");
    if (GameData::Inst()->isMusicBgOpen) {
        m_spchose->setPosition(Point(335,130));
    }else
    {
        m_spchose->setPosition(Point(415,130));
    }
    if (GameData::Inst()->isEffectOpen) {
        m_spchose2->setPosition(Point(335,90));
    }else
    {
        m_spchose2->setPosition(Point(415,90));
    }
    
    spbg->addChild(m_spchose);
    spbg->addChild(m_spchose2);
    

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(setLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(setLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(setLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    touchListener->setSwallowTouches(true); 
    return true;
}
bool setLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void setLayer::onTouchMoved(Touch* touch, Event* event)
{
    
}
void setLayer::onTouchEnded(Touch* touch, Event* event)
{
    Point touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    
    Point pos = convertToNodeSpace( touchLocation );
    
    bool bRet = false;
    
    Point pt = m_btnBgOpen->getPosition();
    Size s= m_btnBgOpen->getContentSize();
	//获取精灵的矩形框
    Rect rect = Rect(pt.x - s.width * 0.5,  pt.y - s.height * 0.5, s.width, s.height);
    if (GameData::Inst()->isEffectOpen) {
        SimpleAudioEngine::getInstance()->playEffect("sound/get_bomb.mp3");
    }
    bRet = rect.containsPoint(pos);
    if(bRet){ 
        
        return;
    }
    auto scaleOne=ScaleTo::create(0.1f, 0.8f);
    auto scaleTwo=ScaleTo::create(0.1f, 0.6f);
    auto scaleThr=ScaleTo::create(0.1f, 0.3f);
    auto scaleFor=ScaleTo::create(0.1f, 0.1f);
    this->runAction(Sequence::create(scaleOne,scaleTwo,scaleThr,scaleFor, NULL));
    scheduleOnce(SEL_SCHEDULE(&setLayer::quitLayer), 0.4f); 
    
}
void setLayer::menuOpenBgCallback(Ref* pSender)
{
    m_spchose->setPosition(Point(335,130));
    GameData::Inst()->isMusicBgOpen=true;
    CCUserDefault::getInstance()->setBoolForKey("isBgMusic",true);
    CCUserDefault::getInstance()->flush();
    if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.mp3",true);//
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    }else
    {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
    
}
void setLayer::menuCloseBgCallback(Ref* pSender)
{
    m_spchose->setPosition(Point(415,130));
    GameData::Inst()->isMusicBgOpen=false;
    CCUserDefault::getInstance()->setBoolForKey("isBgMusic",false);
    CCUserDefault::getInstance()->flush();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void setLayer::menuOpenEffectCallback(Ref* pSender)
{
    m_spchose2->setPosition(Point(335,90));
    GameData::Inst()->isEffectOpen=true;
    CCUserDefault::getInstance()->setBoolForKey("isEffectMusic",true);
    CCUserDefault::getInstance()->flush();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
void setLayer::menuCloseEffectCallback(Ref* pSender)
{
    m_spchose2->setPosition(Point(415,90));
    GameData::Inst()->isEffectOpen=false;
    CCUserDefault::getInstance()->setBoolForKey("isEffectMusic",false);
    CCUserDefault::getInstance()->flush();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}
void setLayer::quitLayer(float dt)
{
    unschedule(SEL_SCHEDULE(&setLayer::quitLayer));
    this->removeFromParentAndCleanup(true);
    
}
void setLayer::onExit()
{
    removeAllChildrenWithCleanup(true);
    Layer::onExit();
}