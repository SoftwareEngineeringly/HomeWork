#include"Enemy.h"
#include "GameData.h"

Enemy::Enemy()
{
	m_sprite=NULL;
	m_life = 0;
}
Enemy::~Enemy()
{
}
Enemy* Enemy::create()
{
	Enemy *pRet = new Enemy();
	pRet->autorelease();
	return pRet;
}
void Enemy::bindSprite(Sprite *sprite,int life)
{
	m_sprite = sprite;
	m_life = life;
	this->addChild(m_sprite);
}
Sprite* Enemy::getSprite()
{
	return m_sprite;
}
int Enemy::getLife()
{
	return m_life;
}
void Enemy::lostLife(int lifeValue)
{
	//lifeValue minus 1
	this->m_life -=lifeValue; 
}

Rect Enemy::getBoundingBox()
{
	Rect rect = m_sprite->boundingBox();

	Vec2 pos = this->convertToWorldSpace(rect.origin);
	Rect enemyRect(pos.x,pos.y,rect.size.width,rect.size.height);
	return enemyRect;
}


EnemyLayer::EnemyLayer()
{
	m_pAllEnemy1 = __Array::create();
	m_pAllEnemy1->retain();
	m_pAllEnemy2 = __Array::create();
	m_pAllEnemy2->retain();
	m_pAllEnemy3 = __Array::create();
	m_pAllEnemy3->retain();
	m_pAllStar = __Array::create();
	m_pAllStar->retain();
}
EnemyLayer::~EnemyLayer()
{
	m_pAllEnemy1->release();
	m_pAllEnemy1 = NULL;
	m_pAllEnemy2->release();
	m_pAllEnemy2 = NULL;
	m_pAllEnemy3->release();
	m_pAllEnemy3 = NULL;
	m_pAllStar->release();
	m_pAllStar = NULL;
}
bool EnemyLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Texture2D *texture = Director::getInstance()->getTextureCache()->getTextureForKey("shoot.png");
	starBatchNode = SpriteBatchNode::createWithTexture(texture);
	this->addChild(starBatchNode);
	point = Vec2::ZERO;
    
	return true;
}

//Random initialize enemy1 position and velocity
void EnemyLayer::addEnemy1(float dt)
{

	Enemy *enemy1 = Enemy::create();

	enemy1->bindSprite(Sprite::create("diji1_1.png"),3);


	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("diji1_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("diji1_2.png"));//Ö¡¶¯»­
	Animate *animate = Animate::create(animation);
	enemy1->getSprite()->runAction(animate);



	Size enemy1Size = enemy1->getSprite()->getContentSize();
	Size winSize = Director::getInstance()->getWinSize();
	int minX = enemy1Size.width/2;
	int maxX = winSize.width-enemy1Size.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX)+minX;
	enemy1->setPosition(Vec2(actualX,winSize.height+enemy1Size.height/2));

	this->addChild(enemy1);
	this->m_pAllEnemy1->addObject(enemy1);

    float minDuration = GameData::Inst()->minSpeed;
    float maxDuration = GameData::Inst()->maxSpeed;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand()%rangeDuration)+minDuration;
	FiniteTimeAction *actionMove = MoveTo::create(actualDuration,Vec2(actualX,0-enemy1->getSprite()->getContentSize().height/2));
	FiniteTimeAction *actionDone =CallFuncN::create(this,callfuncN_selector(EnemyLayer::enemy1MoveFinished));
	Sequence *sequence = Sequence::create(actionMove,actionDone,NULL);
	enemy1->runAction(sequence);
}
//Random initialize enemy2 position and velocity
void EnemyLayer::addEnemy2(float dt)
{

	Enemy *enemy2 = Enemy::create();
	enemy2->bindSprite(Sprite::create("diji2_1.png"),10);

	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("diji2_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("diji2_2.png"));//Ö¡¶¯»­
	Animate *animate = Animate::create(animation);
	enemy2->getSprite()->runAction(animate);


	Size enemy2Size = enemy2->getSprite()->getContentSize();
	Size winSize = Director::getInstance()->getWinSize();
	int minX = enemy2Size.width/2;
	int maxX = winSize.width-enemy2Size.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX)+minX;
	enemy2->setPosition(Vec2(actualX,winSize.height+enemy2Size.height/2));
	this->addChild(enemy2);
	this->m_pAllEnemy2->addObject(enemy2);


    float minDuration = GameData::Inst()->minSpeed;
    float maxDuration = GameData::Inst()->maxSpeed;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand()%rangeDuration)+minDuration;
	FiniteTimeAction *actionMove = MoveTo::create(actualDuration,Vec2(actualX,0-enemy2->getSprite()->getContentSize().height/2));
	FiniteTimeAction *actionDone = CallFuncN::create(this,callfuncN_selector(EnemyLayer::enemy2MoveFinished));
	Sequence *sequence = Sequence::create(actionMove,actionDone,NULL);
	enemy2->runAction(sequence);
}
//Random initialize1 enemy3 position and velocity
void EnemyLayer::addEnemy3(float dt)
{

	Enemy *enemy3 = Enemy::create();

	enemy3->bindSprite(Sprite::create("diji3_1.png"),50);

	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("diji3_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("diji3_2.png"));//Ö¡¶¯»­
	Animate *animate = Animate::create(animation);
	enemy3->getSprite()->runAction(animate);


	Size enemy3Size = enemy3->getSprite()->getContentSize();
	Size winSize = Director::getInstance()->getWinSize();
	int minX = enemy3Size.width/2;
	int maxX = winSize.width-enemy3Size.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX)+minX;
	enemy3->setPosition(Vec2(actualX,winSize.height+enemy3Size.height/2));
	this->addChild(enemy3);
	this->m_pAllEnemy3->addObject(enemy3);

    float minDuration = GameData::Inst()->min3Speed;
    float maxDuration = GameData::Inst()->max3Speed;

	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand()%rangeDuration)+minDuration;
	FiniteTimeAction *actionMove = MoveTo::create(actualDuration,Vec2(actualX,(0-enemy3->getSprite()->getContentSize().height/2)));
	FiniteTimeAction *actionDone = CallFuncN::create(this,callfuncN_selector(EnemyLayer::enemy3MoveFinished));
	Sequence *sequence = Sequence::create(actionMove,actionDone,NULL);
	enemy3->runAction(sequence);

}
void EnemyLayer::enemy1MoveFinished(Node *pEnemy1)
{
	Enemy *enmey1 =(Enemy*)pEnemy1;
	this->m_pAllEnemy1->removeObject(enmey1);

	this->removeChild(enmey1,true);
	
}
void EnemyLayer::enemy2MoveFinished(Node *pEnemy2)
{
	Enemy *enmey2 =(Enemy*)pEnemy2;
	this->m_pAllEnemy2->removeObject(enmey2);
	this->removeChild(enmey2,true);
}
void EnemyLayer::enemy3MoveFinished(Node *pEnemy3)
{
	Enemy *enmey3 =(Enemy*)pEnemy3;
	this->m_pAllEnemy3->removeObject(enmey3);

	this->removeChild(enmey3,true);
}
void EnemyLayer::enemy1Blowup(Enemy* enemy1)
{
	
	enemy1->getSprite()->stopAllActions();

	point = enemy1->getPosition();

	createEnemy1BlowupAnimation();
	Animation* animation = AnimationCache::getInstance()->getAnimation("Enemy1Blowup");
	Animate* animate =Animate::create(animation);
	__CCCallFuncND* removeEnemy1=__CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeEnemy1),(void*)enemy1);
	Sequence* sequence = Sequence::create(animate,removeEnemy1,NULL);
	enemy1->getSprite()->runAction(sequence);
    if (GameData::Inst()->gameMode == GameMode::NORMAL) {
        starsJump(2);
    }
	

	
}

void EnemyLayer::enemy2Blowup(Enemy* enemy2)
{
	enemy2->getSprite()->stopAllActions();

	createEnemy2BlowupAnimation();
	this->point = enemy2->getPosition();
	Animation* animation = AnimationCache::getInstance()->getAnimation("Enemy2Blowup");
	Animate* animate =Animate::create(animation);
	__CCCallFuncND* removeEnemy2=__CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeEnemy1),(void*)enemy2);
	Sequence* sequence = Sequence::create(animate,removeEnemy2,NULL);
	enemy2->getSprite()->runAction(sequence);
    if (GameData::Inst()->gameMode == GameMode::NORMAL) {
        starsJump(3);
    }
}
void EnemyLayer::enemy3Blowup(Enemy* enemy3)
{

	enemy3->getSprite()->stopAllActions();
	point = enemy3->getPosition();
	createEnemy3BlowupAnimation();
	Animation* animation = AnimationCache::getInstance()->getAnimation("Enemy3Blowup");
	Animate* animate =Animate::create(animation);
	__CCCallFuncND* removeEnemy3=__CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeEnemy3),(void*)enemy3);
	Sequence* sequence = Sequence::create(animate,removeEnemy3,NULL);
	enemy3->getSprite()->runAction(sequence);
    if (GameData::Inst()->gameMode == GameMode::NORMAL) {
        starsJump(5);
    }
}
void EnemyLayer::removeEnemy1(Node* pTarget,void* data)
{
	Enemy* enemy1 = (Enemy*)data;
	if (enemy1!=NULL)
	{
		m_pAllEnemy1->removeObject(enemy1);
		this->removeChild(enemy1,true);
	}
}
void EnemyLayer::removeEnemy2(Node* pTarget,void* data)
{
	Enemy* enemy2 = (Enemy*)data;
	if (enemy2!=NULL)
	{
		m_pAllEnemy2->removeObject(enemy2);
		this->removeChild(enemy2,true);
	}
}
void EnemyLayer::removeEnemy3(Node* pTarget,void* data)
{
	Enemy* enemy3 = (Enemy*)data;
	if (enemy3!=NULL)
	{
		m_pAllEnemy3->removeObject(enemy3);
		this->removeChild(enemy3,true);
	}
}
void EnemyLayer::removeAllEnemy1()
{
	Ref* obj;
	CCARRAY_FOREACH(m_pAllEnemy1,obj)
	{
		Enemy* enemy1= (Enemy*)obj;
		if (enemy1->getLife()>0)
		{
			enemy1Blowup(enemy1);
		}
	}
}
void EnemyLayer::removeAllEnemyNow1()
{
    Ref* obj;
    CCARRAY_FOREACH(m_pAllEnemy1,obj)
    {
        Enemy* enemy1= (Enemy*)obj;
        if (enemy1->getLife()>0)
        {
           m_pAllEnemy1->removeObject(enemy1);
           this->removeChild(enemy1,true);
        }
    }
}
void EnemyLayer::removeAllEnemyNow2()
{
    Ref* obj;
    CCARRAY_FOREACH(m_pAllEnemy2,obj)
    {
        Enemy* enemy1= (Enemy*)obj;
        if (enemy1->getLife()>0)
        {
             m_pAllEnemy2->removeObject(enemy1);
            this->removeChild(enemy1,true);
        }
    }
}
void EnemyLayer::removeAllEnemyNow3()
{
    Ref* obj;
    CCARRAY_FOREACH(m_pAllEnemy2,obj)
    {
        Enemy* enemy1= (Enemy*)obj;
        if (enemy1->getLife()>0)
        {
            m_pAllEnemy3->removeObject(enemy1);
            this->removeChild(enemy1,true);
        }
    }
}
void EnemyLayer::removeAllEnemy2()
{
	Ref* obj;
	CCARRAY_FOREACH(m_pAllEnemy2,obj)
	{
		Enemy* enemy2= (Enemy*)obj;
		if (enemy2->getLife()>0)
		{
			enemy2Blowup(enemy2);
		}
	}
}
//Remove all enemy when using the bomb in the full screen 
void EnemyLayer::removeAllEnemy3()
{
	Ref* obj;
	CCARRAY_FOREACH(m_pAllEnemy3,obj)
	{
		Enemy* enemy3= (Enemy*)obj;
		if (enemy3->getLife()>0)
		{
			enemy3Blowup(enemy3);
		}
	}
}
//add Enemy1 explosion animations to the pool
void EnemyLayer::createEnemy1BlowupAnimation()
{
	SpriteFrame* m_fream2 =SpriteFrameCache::getInstance()->getSpriteFrameByName("b2.png");
	SpriteFrame* m_fream3 =SpriteFrameCache::getInstance()->getSpriteFrameByName("b3.png");
	SpriteFrame* m_fream4 =SpriteFrameCache::getInstance()->getSpriteFrameByName("b4.png");
	SpriteFrame* m_fream5 =SpriteFrameCache::getInstance()->getSpriteFrameByName("b5.png");
    
    auto m_fream1 =SpriteFrameCache::getInstance()->getSpriteFrameByName("b1.png");
    
    Vector<SpriteFrame *> animFreams ;
    animFreams.pushBack(m_fream1);
    animFreams.pushBack(m_fream2);
    animFreams.pushBack(m_fream3);
    animFreams.pushBack(m_fream4);
    animFreams.pushBack(m_fream5);
    
	Animation* animation = Animation::createWithSpriteFrames(animFreams,0.1f);
	AnimationCache::getInstance()->addAnimation(animation,"Enemy1Blowup");
}
//add Enemy2 explosion animations to the pool
void EnemyLayer::createEnemy2BlowupAnimation()
{
	SpriteFrame* m_fream1 =SpriteFrameCache::getInstance()->getSpriteFrameByName("d2b1.png");
	SpriteFrame* m_fream2 =SpriteFrameCache::getInstance()->getSpriteFrameByName("d2b2.png");
	SpriteFrame* m_fream3 =SpriteFrameCache::getInstance()->getSpriteFrameByName("d2b3.png");
	SpriteFrame* m_fream4 =SpriteFrameCache::getInstance()->getSpriteFrameByName("d2b4.png");
	SpriteFrame* m_fream5 =SpriteFrameCache::getInstance()->getSpriteFrameByName("d2b5.png");

    Vector<SpriteFrame *> animFreams ;
    animFreams.pushBack(m_fream1);
    animFreams.pushBack(m_fream2);
    animFreams.pushBack(m_fream3);
    animFreams.pushBack(m_fream4);
    animFreams.pushBack(m_fream5);
    
	auto animation = Animation::createWithSpriteFrames(animFreams,0.2f);
	AnimationCache::getInstance()->addAnimation(animation,"Enemy2Blowup");
}
//add Enemy3 explosion animations to the pool
void EnemyLayer::createEnemy3BlowupAnimation()
{
	SpriteFrame* m_fream1 =SpriteFrameCache::getInstance()->getSpriteFrameByName("d3b1.png");
	SpriteFrame* m_fream2 =SpriteFrameCache::getInstance()->getSpriteFrameByName("d3b2.png");
	SpriteFrame* m_fream3 =SpriteFrameCache::getInstance()->getSpriteFrameByName("d3b3.png");
	SpriteFrame* m_fream4 =SpriteFrameCache::getInstance()->getSpriteFrameByName("d3b4.png");
	SpriteFrame* m_fream5 =SpriteFrameCache::getInstance()->getSpriteFrameByName("d3b5.png");

    Vector<SpriteFrame *> animFreams ;
    animFreams.pushBack(m_fream1);
    animFreams.pushBack(m_fream2);
    animFreams.pushBack(m_fream3);
    animFreams.pushBack(m_fream4);
    animFreams.pushBack(m_fream5);
	Animation* animation = Animation::createWithSpriteFrames(animFreams,0.1f);
    
	AnimationCache::getInstance()->addAnimation(animation,"Enemy3Blowup");
}

void EnemyLayer::removeAllEnemy()
{
	removeAllEnemy1();
	removeAllEnemy2();
	removeAllEnemy3();
}
//star jump
void EnemyLayer::starsJump(int num)
{
	for (int i=0;i<num;i++)
	{
		addStar(0.3f);
	}

}
void EnemyLayer::addStar(float dt)
{
	Sprite *star = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("star.png"));
	Size winSize = Director::getInstance()->getWinSize();
	int minY = 80;
	int maxY = 120;
	int rangeY = maxY-minY;
	float actualY=(rand()%rangeY)+minY;
	int minX = 30;
	int maxX = 70;
	int rangeX = maxX-minX;
	float actualX=(rand()%rangeX)+minX;
	star->setPosition(Vec2(point.x+actualX,point.y+actualY));
	this->starBatchNode->addChild(star);
	this->m_pAllStar->addObject(star);

	MoveBy *move1 = MoveBy::create(0.5f,Vec2(0,-150));
	MoveBy *move2 = MoveBy::create(0.3f,Vec2(0,100));
	MoveTo *move3 = MoveTo::create(0.3f,Vec2(100,winSize.height-60));
	CallFuncN *moveDone = CallFuncN::create(this,callfuncN_selector(EnemyLayer::starFinised));
	FiniteTimeAction *sequence = Sequence::create(move1,move2,move3,moveDone,NULL);
	star->runAction(sequence);
}
void EnemyLayer::starFinised(Node *star)
{
	Sprite *starFini = (Sprite*)star;
	this->starBatchNode->removeChild(starFini,true);
	this->m_pAllStar->removeObject(starFini);
}