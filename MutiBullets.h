#ifndef __MUTIBULLETS_H__
#define __MUTIBULLETS_H__	
#include"cocos2d.h"
using namespace cocos2d;
class MutiBullets:public Layer
{
private:
	SpriteBatchNode * bulletBatchNode;
public:
	__Array * m_pAllBullet;
private:
	float times=0.06f;
	unsigned int repeat = 100;
	int zidan = 2;
public:
	MutiBullets();
	~MutiBullets();

	virtual bool init();
	CREATE_FUNC(MutiBullets);

	void  AddBullet(float dt);

	void StartShoot(float delay=1.0);

	void StopShoot();

	void bulletMoveFinished(Node *pSender);

	void RemoveBullet(Sprite * bullet);
	void set_times(float t){ times = t; }
	void set_repeat(unsigned int r){ repeat = r; }
	void set_zidan(int zi){ zidan = zi; }

};
#endif