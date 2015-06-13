#include"MutiBullets.h"
#include"PlaneLayer.h"

MutiBullets::MutiBullets()
{
	m_pAllBullet = __Array::create();
	m_pAllBullet->retain();

}
MutiBullets::~MutiBullets()
{
	m_pAllBullet->release();
	m_pAllBullet = NULL;
}
bool MutiBullets::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Texture2D *texture = Director::getInstance()->getTextureCache()->getTextureForKey("shoot.png");
	bulletBatchNode = SpriteBatchNode::createWithTexture(texture);
	this->addChild(bulletBatchNode);

	return true;
}
void MutiBullets::AddBullet(float dt)
{
	Sprite *bullet, *bullet2;
	if (zidan == 1){
		bullet = Sprite::createWithSpriteFrameName("zidan1.png");
		bullet2 = Sprite::createWithSpriteFrameName("zidan1.png");
	}
	else{
		bullet = Sprite::createWithSpriteFrameName("zidan2.png");
		bullet2 = Sprite::createWithSpriteFrameName("zidan2.png");
	}

	bulletBatchNode->addChild(bullet);
	bulletBatchNode->addChild(bullet2);


	Vec2 planePosition = PlaneLayer::sharedPlane->getChildByTag(1)->getPosition();

	Vec2 bulletPositon = Vec2(planePosition.x-46,planePosition.y+PlaneLayer::sharedPlane->getChildByTag(1)->getContentSize().height/2-14);
	Vec2 bulletPositon2 = Vec2(planePosition.x+46,planePosition.y+PlaneLayer::sharedPlane->getChildByTag(1)->getContentSize().height/2-14);
	Vec2 bulletPositon3 = Vec2(planePosition.x, planePosition.y + PlaneLayer::sharedPlane->getChildByTag(1)->getContentSize().height / 2);
	bullet->setPosition(bulletPositon);
	bullet2->setPosition(bulletPositon2);


	float length = Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2-bulletPositon.y;
	float velocity = 2200/1;
	float realMoveDuration = length/velocity;

	FiniteTimeAction * actionMove = MoveTo::create(realMoveDuration,Vec2(bulletPositon.x,Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2));
	FiniteTimeAction * actionDone = CallFuncN::create(this,callfuncN_selector(MutiBullets::bulletMoveFinished));
	Sequence *sequence = Sequence::create(actionMove,actionDone,NULL);

	FiniteTimeAction * actionMove2 = MoveTo::create(realMoveDuration,Vec2(bulletPositon2.x,Director::getInstance()->getWinSize().height+bullet2->getContentSize().height/2));
	FiniteTimeAction * actionDone2 = CallFuncN::create(this,callfuncN_selector(MutiBullets::bulletMoveFinished));
	Sequence *sequence2 = Sequence::create(actionMove2,actionDone2,NULL);


	bullet->runAction(sequence);
	bullet2->runAction(sequence2);
	this->m_pAllBullet->addObject(bullet);
	this->m_pAllBullet->addObject(bullet2);

}
void MutiBullets::bulletMoveFinished(Node *pSender)
{
	Sprite *bullet = (Sprite*)pSender;
	this->m_pAllBullet->removeObject(bullet);
	this->bulletBatchNode->removeChild(bullet,true);
}
void MutiBullets::StartShoot(float delay)
{
	
	this->schedule(schedule_selector(MutiBullets::AddBullet),times,repeat,delay);
}
void MutiBullets::StopShoot()
{
	
	this->unschedule(schedule_selector(MutiBullets::AddBullet));
}

void MutiBullets::RemoveBullet(Sprite *bullet)
{
	if(bullet != NULL)
	{
		this->m_pAllBullet->removeObject(bullet);
		this->bulletBatchNode->removeChild(bullet,true);
	}
}