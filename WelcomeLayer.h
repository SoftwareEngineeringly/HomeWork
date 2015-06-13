#ifndef __WELCOMELAYER_H__
#define __WELCOMELAYER_H__	
#include"cocos2d.h"
#include "GameoverLayer.h"
#include "MainScene.h"
#include "HardScene.h"
#include "DBUtil.h"
#include "setLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;
class WelcomeLayer:public Layer
{
private:
	Sprite *plane;
	Sprite *plane1;
	Sprite *plane2;

	UserVO *userVo;
public:
	virtual bool init();
	static Scene *scene();
	CREATE_FUNC(WelcomeLayer);
	bool isHaveSaveFile();
	void  getHighestHistorySorce();
	void copyLoading();
	void playGame(Ref *obj);
    void playGame2(Ref *obj);
	void changeScene(Node *pSender);
	void menuSetCallback(Ref* pSender);
	void menuExitCallback(Ref* pSender);
    void menuShareCallback(Ref* pSender);
};
#endif