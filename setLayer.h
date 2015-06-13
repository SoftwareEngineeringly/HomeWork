#ifndef __SETLAYER_H__
#define __SETLAYER_H__	
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;
class setLayer:public LayerColor
{
    Sprite          *m_spchose;
    Sprite          *m_spchose2;
    MenuItem          *m_btnBgOpen;
    MenuItem          *m_btnBgClose;
    MenuItem          *m_btnEffectOpen;
    MenuItem          *m_btnEffectClose;
public:
    virtual bool initWithColor(const Color4B& color);
    static setLayer* create();
    setLayer();
    ~setLayer();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    virtual void onExit();
    void quitLayer(float dt);
    void cbChosePopDialog();
    void menuOpenBgCallback(Ref* pSender);
    void menuCloseBgCallback(Ref* pSender);
    void menuOpenEffectCallback(Ref* pSender);
    void menuCloseEffectCallback(Ref* pSender);
};
#endif