#ifndef __CONTROLLAYER_H__
#define __CONTROLLAYER_H__	
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;
static 	int	SCORE_LAYER_ITEM=5;
class ControlLayer:public Layer
{
private:
    MenuItemToggle *pPauseItem;
    MenuItem *m_btnPauseOpen;
    MenuItem *m_btnPauseClose;
	LabelAtlas   *lableScore;

public:
	virtual bool init();
	CREATE_FUNC(ControlLayer);
	void menuPauseCallback(Ref* pSender);
	void updateScore(int score); 
};
#endif