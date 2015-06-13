#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include"cocos2d.h"
#include"PlaneLayer.h"
using namespace cocos2d;
class GameScene:public Layer
{
private:
	Sprite *m_bg1;
	Sprite *m_bg2;
	Sprite *m_star1;
	Sprite *m_star2;
	float m_BgMoveValue;
	float m_StarMove;
	float m_BgHeight;
	__Array *m_pAllBg;
	__Array *m_pAllStar;
public:
	GameScene();
	~GameScene();
	virtual bool init();
	static Scene* scene();
	CREATE_FUNC(GameScene);
	void start();
	void initBackground();
	void update(float);
	void movingBackground(Ref *pObj,float dt);
	void movingBackgroundStar(Ref *pObj,float dt);
};
#endif