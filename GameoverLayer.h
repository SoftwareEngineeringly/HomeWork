#ifndef __GAMEOVERLAYER_H__
#define __GAMEOVERLAYER_H__	
#include"cocos2d.h"
#include "WelcomeLayer.h"
using namespace cocos2d;
class GameoverLayer:public LayerColor
{
private:
	int score;

    LabelAtlas *lableCurScore;

    LabelAtlas *labHighestScore;
	int starnum;
	int starlastnum;
public:
	GameoverLayer();
	~GameoverLayer();
	static GameoverLayer* create(int passScore);
    virtual bool initWithColor(const Color4B& color);
    
	static Scene* scene(int passScore);

	void backMainScene(Ref *obj);
	void beginChangeHighestScore(Node* pTarget,void* data);
	void getStarnum();
	void drawStarnum(int num,int lastnum);
    void shareWeixin(Ref *obj);
    void screenShoot();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
};
#endif