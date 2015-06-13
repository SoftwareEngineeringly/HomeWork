#ifndef __ENEMY_H__
#define __ENEMY_H__
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include<iostream>
using namespace cocos2d;
using namespace std;
class Enemy:public Node
{
private:
	Sprite *m_sprite;
	int		  m_life;

public:
	Enemy();
	~Enemy();
	static Enemy* create();
	void bindSprite(Sprite *sprite,int life);
	Sprite* getSprite();
	int getLife();
	void lostLife(int lostValue=1);
	Rect getBoundingBox();
};

class EnemyLayer:public Layer
{
private:
	SpriteBatchNode * starBatchNode;
public:
	__Array *m_pAllEnemy1;
	__Array *m_pAllEnemy2;
	__Array *m_pAllEnemy3;
	__Array *m_pAllStar;
	Vec2  point;
	int m_bigSoundId;
public:
	EnemyLayer();
	~EnemyLayer();
	virtual bool init();
	CREATE_FUNC(EnemyLayer);


	void addEnemy1(float dt);
	void enemy1Blowup(Enemy* enemy1);
	void removeEnemy1(Node* pTarget,void* data);
	void removeAllEnemy1();
	void enemy1MoveFinished(Node *pEnemy1);
	

	void addEnemy2(float dt);
	void enemy2Blowup(Enemy* enemy1);
	void removeEnemy2(Node* pTarget,void* data);
	void removeAllEnemy2();
	void enemy2MoveFinished(Node *pEnemy2);

	void addEnemy3(float dt);
	void enemy3Blowup(Enemy* enemy1);
	void removeEnemy3(Node* pTarget,void* data);
	void removeAllEnemy3();
	void enemy3MoveFinished(Node *pEnemy3);

    void removeAllEnemyNow1();
    void removeAllEnemyNow2();
    void removeAllEnemyNow3();

	void createEnemy1BlowupAnimation();
	void createEnemy2BlowupAnimation();
	void createEnemy3BlowupAnimation();
	void removeAllEnemy();
	void starsJump(int num);
	void addStar(float dt);
	void starFinised(Node *star);
};
#endif