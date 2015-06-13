#include"UFOLayer.h"
UFOLayer::UFOLayer()
{
	m_pAllMutiBullets = __Array::create();
	m_pAllMutiBullets->retain();
	m_pAllBigBoomItem = __Array::create();
	m_pAllBigBoomItem->retain();
}
UFOLayer::~UFOLayer()
{
	m_pAllMutiBullets->release();
	m_pAllMutiBullets = NULL;
	m_pAllBigBoomItem->release();
	m_pAllBigBoomItem = NULL;
}
bool UFOLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void UFOLayer::AddMutiBullets(float dt)
{

	Sprite * mutibullets=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("san1.png"));

	Size mutibulletsSize = mutibullets->getContentSize();
	Size winSize = Director::getInstance()->getWinSize();
	int minX = mutibulletsSize.width/2;
	int maxX = winSize.width-mutibulletsSize.width/2;
	int rangeX = maxX-minX;
	int actualX=(rand()%rangeX)+minX;
    mutibullets->setPosition(Point(actualX,winSize.height+mutibulletsSize.height/2));

	this->addChild(mutibullets);
	this->m_pAllMutiBullets->addObject(mutibullets);

	createUFOZidanAnimation();
	Animation* animation = AnimationCache::getInstance()->getAnimation("ZidanAnimation");
	Animate* animate =Animate::create(animation);
	FiniteTimeAction* sequence2 = Sequence::create(animate,NULL);
	mutibullets->runAction(sequence2);

	MoveBy *move1 = MoveBy::create(0.5f,Vec2(0,-150));
	MoveBy *move2 = MoveBy::create(0.3f,Vec2(0,100));
	MoveBy *move3 = MoveBy::create(3.0f,Vec2(0,0-winSize.height-mutibulletsSize.height/2));
	CallFuncN *moveDone = CallFuncN::create(this,callfuncN_selector(UFOLayer::mutiBulletsMoveFinished));
	FiniteTimeAction *sequence = Sequence::create(move1,move2,move3,moveDone,NULL);
	mutibullets->runAction(sequence);
	
}
void UFOLayer::mutiBulletsMoveFinished(Node *pSender)
{
	Sprite * mutiBullets = (Sprite*)pSender;
	this->removeChild(mutiBullets);
	this->m_pAllMutiBullets->removeObject(mutiBullets);

}

void UFOLayer::RemoveMutiBullets(Sprite * mutiBullets)
{
	this->removeChild(mutiBullets);
	this->m_pAllMutiBullets->removeObject(mutiBullets);
}

void UFOLayer::AddBigBoomItem(float dt)
{
	Sprite * mutibullets=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("san2.png"));

	Size mutibulletsSize = mutibullets->getContentSize();
	Size winSize = Director::getInstance()->getWinSize();
	int minX = mutibulletsSize.width/2;
	int maxX = winSize.width-mutibulletsSize.width/2;
	int rangeX = maxX-minX;
	int actualX=(rand()%rangeX)+minX;
	mutibullets->setPosition(Point(actualX,winSize.height+mutibulletsSize.height/2));
	this->addChild(mutibullets);
	this->m_pAllBigBoomItem->addObject(mutibullets);

	createUFOAnheiAnimation();
	Animation* animation = AnimationCache::getInstance()->getAnimation("AnheiAnimation");
	Animate* animate =Animate::create(animation);
	Sequence* sequence2 = Sequence::create(animate,NULL);
	mutibullets->runAction(sequence2);

	MoveBy *move1 = MoveBy::create(0.5f,Vec2(0,-150));
	MoveBy *move2 = MoveBy::create(0.3f,Vec2(0,100));
	MoveBy *move3 = MoveBy::create(3.0f,Vec2(0,0-winSize.height-mutibulletsSize.height/2));
	CallFuncN *moveDone = CallFuncN::create(this,callfuncN_selector(UFOLayer::bigBoomItemMoveFinished));
	FiniteTimeAction *sequence = Sequence::create(move1,move2,move3,moveDone,NULL);
	mutibullets->runAction(sequence);
	

}
void UFOLayer::bigBoomItemMoveFinished(Node *pSender)
{
	Sprite * bigBoomItems = (Sprite*)pSender;
	this->removeChild(bigBoomItems);
	this->m_pAllBigBoomItem->removeObject(bigBoomItems);

}

void UFOLayer::RemoveBigBoomItem(Sprite * bigBoomItems)
{
	this->removeChild(bigBoomItems);
	this->m_pAllBigBoomItem->removeObject(bigBoomItems);
}

void UFOLayer::createUFOZidanAnimation()
{
	SpriteFrame* m_fream1 =SpriteFrameCache::getInstance()->getSpriteFrameByName("zd1.png");
	SpriteFrame* m_fream2 =SpriteFrameCache::getInstance()->getSpriteFrameByName("zd2.png");
	SpriteFrame* m_fream3 =SpriteFrameCache::getInstance()->getSpriteFrameByName("zd3.png");
    Vector<SpriteFrame *> animFreams ;
    animFreams.pushBack(m_fream1);
    animFreams.pushBack(m_fream2);
    animFreams.pushBack(m_fream3);
	Animation* animation = Animation::createWithSpriteFrames(animFreams,0.1f);
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(animation,"ZidanAnimation");
}
void UFOLayer::createUFOAnheiAnimation()
{
	SpriteFrame* m_fream1 =SpriteFrameCache::getInstance()->getSpriteFrameByName("an1.png");
	SpriteFrame* m_fream2 =SpriteFrameCache::getInstance()->getSpriteFrameByName("an2.png");
	SpriteFrame* m_fream3 =SpriteFrameCache::getInstance()->getSpriteFrameByName("an3.png");

    Vector<SpriteFrame *> animFreams ;
    animFreams.pushBack(m_fream1);
    animFreams.pushBack(m_fream2);
    animFreams.pushBack(m_fream3);
	Animation* animation = Animation::createWithSpriteFrames(animFreams,0.1f);
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(animation,"AnheiAnimation");
}
