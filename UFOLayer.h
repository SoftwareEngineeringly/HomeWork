#ifndef __UFOLAYER_H__
#define __UFOLAYER_H__	
#include"cocos2d.h"
using namespace cocos2d;
class UFOLayer:public Layer
{
public:
	__Array * m_pAllMutiBullets;
	__Array * m_pAllBigBoomItem;
public:
	UFOLayer();
	~UFOLayer();
	virtual bool init();
	CREATE_FUNC(UFOLayer);

	void AddMutiBullets(float dt);

	void AddBigBoomItem(float dt);

	void mutiBulletsMoveFinished(Node *pSender);
	void bigBoomItemMoveFinished(Node *pSender);

	void RemoveMutiBullets(Sprite * mutiBullets);
	void RemoveBigBoomItem(Sprite * bigBoomItems);
	void createUFOZidanAnimation();
	void createUFOAnheiAnimation();
};
#endif