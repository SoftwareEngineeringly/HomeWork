#ifndef __BULLETLAYER_H__
#define __BULLETLAYER_H__	
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;
class BulletLayer:public Layer
{
private:
	SpriteBatchNode * bulletBatchNode;
	int m_bulletSoundId;
public:
	__Array * m_pAllBullet;
public:
	BulletLayer();
	~BulletLayer();

	virtual bool init();
	CREATE_FUNC(BulletLayer);

	void  AddBullet(float dt);

	void StartShoot(float delay=1.0);

	void StopShoot();
	//destroy bullet after it disappears
	void bulletMoveFinished(Node *pSender);
	//delete bullet
	void RemoveBullet(Sprite * bullet);

};
#endif