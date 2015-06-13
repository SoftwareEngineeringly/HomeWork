#include"PlaneLayer.h"
#include "MainScene.h"
#include "GameData.h"
PlaneLayer* PlaneLayer::sharedPlane = NULL;
PlaneLayer::PlaneLayer()
{

}
PlaneLayer::~PlaneLayer()
{

}
PlaneLayer* PlaneLayer::create()
{
	PlaneLayer *pRet = new PlaneLayer();
	if(pRet&&pRet->init())
	{
		pRet->autorelease();
		sharedPlane = pRet;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet =NULL;
		return NULL;
	}
}
bool PlaneLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	isAlive = true;
	
	Size winSize = Director::getInstance()->getWinSize();

	plane = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane1.png"));

	plane->setPosition(Vec2(winSize.width/2,plane->getContentSize().height/2));
	this->addChild(plane,1,1);

	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane2.png"));//÷°∂Øª≠
	Blink *blink = Blink::create(1,3);
	Animate *animate = Animate::create(animation);


    auto move1 = MoveTo::create(1.0f,Vec2(winSize.width/2,winSize.height/2));
	MoveBy *move3 = MoveBy::create(0.8f,Vec2(0,-300));
	FiniteTimeAction *sequence = Sequence::create(move1,move3,NULL);
	plane->runAction(sequence);
	plane->runAction(blink);
	plane->runAction(animate);

	return true;
	
}
Sprite* PlaneLayer::getPlayerPlane()
{
	return this->plane;
}
void PlaneLayer::MoveTo(Vec2 location)
{

	if(this->isAlive&&!Director::getInstance()->isPaused())
	{

		Size winSize = Director::getInstance()->getWinSize();
		Size planeSize = this->getChildByTag(1)->getContentSize();
		if(location.x<planeSize.width/2)
		{
			location.x = planeSize.width/2;
		}
		if(location.x>winSize.width-planeSize.width/2)
		{
			location.x=winSize.width-planeSize.width/2;
		}
		if(location.y<planeSize.height/2)
		{
			location.y = planeSize.height/2;
		}
		if(location.y>winSize.height-planeSize.height/2)
		{
			location.y=winSize.height-planeSize.height/2;
		}

		this->getChildByTag(1)->setPosition(location);
	}
}
void PlaneLayer::PlayerBlowup(Sprite *plane)
{

	PlayerAnimation();
	Animation* animation = AnimationCache::getInstance()->getAnimation("PlaneBlowup");
	Animate* animate =Animate::create(animation);
	__CCCallFuncND* removePlane=__CCCallFuncND::create(this,callfuncND_selector(PlaneLayer::removePlane),(void*)plane);
	Sequence* sequence = Sequence::create(animate,NULL);
	plane->runAction(sequence);
}
void PlaneLayer::removePlane(Node* pTarget,void* data)
{
    Sprite *plane = (Sprite*)data;
    if (plane!=NULL)
    {
        this->removeChild(plane,true);
    }
    this->getParent()->removeChild(this);
}
void PlaneLayer::PlayerAnimation()
{
	SpriteFrame* m_fream1 =SpriteFrameCache::getInstance()->getSpriteFrameByName("pb1.png");
	SpriteFrame* m_fream2 =SpriteFrameCache::getInstance()->getSpriteFrameByName("pb2.png");
	SpriteFrame* m_fream3 =SpriteFrameCache::getInstance()->getSpriteFrameByName("pb3.png");
	SpriteFrame* m_fream4 =SpriteFrameCache::getInstance()->getSpriteFrameByName("pb4.png");

    Vector<SpriteFrame *> animFreams ;
    animFreams.pushBack(m_fream1);
    animFreams.pushBack(m_fream2);
    animFreams.pushBack(m_fream3);
    animFreams.pushBack(m_fream4);
	Animation* animation = Animation::createWithSpriteFrames(animFreams,0.2f);
	AnimationCache::getInstance()->addAnimation(animation,"PlaneBlowup");
}

Rect PlaneLayer::getBoundingBox()
{
	Rect rect = plane->boundingBox();
	Vec2 pos = this->convertToWorldSpace(rect.origin);
	Rect planeRect(pos.x+30,pos.y+70,rect.size.width-60,rect.size.height-70);
	return planeRect;
}
void PlaneLayer::addJumpWord1(Vec2 point)
{
	Sprite *word1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("word_wuqi.png"));

	word1->setPosition(point);
	FiniteTimeAction *tanout = CCFadeOut::create(0.5f); 
	FiniteTimeAction *moveup = MoveBy::create(0.5f,Vec2(0,66));
	FiniteTimeAction *moveDown =CallFuncN::create(this,callfuncN_selector(PlaneLayer::word1Finished));
	Sequence *sequence = Sequence::create(moveup,tanout,moveDown,NULL);
	word1->runAction(sequence);

	this->addChild(word1);
}
void PlaneLayer::word1Finished(Node *pSender)
{
	Sprite *word = (Sprite*)pSender;
	this->removeChild(word,true);
}
void PlaneLayer::addJumpWord2(Vec2 point)
{
	Sprite *word1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("word_anhei.png"));

	word1->setPosition(point);
	FiniteTimeAction *moveup = MoveBy::create(0.5f,Vec2(0,100));
	FiniteTimeAction *moveDown =CallFuncN::create(this,callfuncN_selector(PlaneLayer::word1Finished));
	Sequence *sequence = Sequence::create(moveup,moveDown,NULL);
	word1->runAction(sequence);

	this->addChild(word1);
}
void PlaneLayer::word2Finished(Node *pSender)
{
	Sprite *word = (Sprite*)pSender;
	this->removeChild(word,true);
}