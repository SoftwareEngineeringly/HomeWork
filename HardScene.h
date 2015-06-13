#ifndef __HARDSCENE_H__
#define __HARDSCENE_H__
#include"cocos2d.h"
#include"GameScene.h"
#include"PlaneLayer.h"
#include"BulletLayer.h"
#include"MutiBullets.h"
#include"Enemy.h"
#include"UFOLayer.h"
#include"ControlLayer.h"
#include "GameoverLayer.h"


using namespace cocos2d;


class HardScene :public Layer
{
private:
	PlaneLayer  *planeLayer;
	MutiBullets *multibulletLayer;
	BulletLayer *bulletLayer;
	EnemyLayer  *enemyLayer;
	UFOLayer    *ufoLayer;
	MutiBullets *mutibullets;

	int			bigBoomCount;
	Menu      *menuBigBoom;

	Label *bigBoomCountItem;
	ControlLayer *controlLayer;
	int			playerScore;

public:
	virtual bool init();
	static Scene* scene();
	CREATE_FUNC(HardScene);

	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);

	virtual void update(float dt);

	void isBulletAndEnemy();
	void isBullet2AndEnemy();
	void isBullet3AndEnemy();
	void MutibulletAndEnemy();
	void Mutibullet2AndEnemy();
	void Mutibullet3AndEnemy();
	void playerAndEnemy();
	void playerAndEnemy3();
	void SingleBulletCrash();
	void MutiBulletCrash();
	void planeAndUFOCrash();
	void planeAndUFOBoomCrash();
	void GameStart();
	void GameStop();
	void produceGameItem(float dt);
	void produceGameItem2(float dt);
	void isGameOver(float dt);
	void updateBigBoomItem(int bigBoomCount);
	void menuBigBoomCallback(Ref* pSender);
	void GameOver();

public:
	bool buttetFlag;
public:
	static bool playEffect;
	static bool playbgtmusic;

};
#endif