#include"GameScene.h"
#include "GameData.h"
GameScene::GameScene()
{
	m_pAllBg = __Array::create();
	m_pAllBg->retain();
	m_pAllStar = __Array::create();
	m_pAllStar->retain();
}
GameScene::~GameScene()
{
	m_pAllBg->release();
	m_pAllBg = NULL;
	m_pAllStar->release();
	m_pAllStar = NULL;
}
bool GameScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	start();
	return true;
}
Scene* GameScene::scene()
{
	Scene* scene = NULL;
		scene  = Scene::create();

		GameScene* layer = GameScene::create();
		scene->addChild(layer);
	return scene;
}
void GameScene::start()
{
	initBackground();

	this->schedule(schedule_selector(GameScene::update),0.01f);
}
void GameScene::initBackground()
{
	m_bg1 = Sprite::create("bg1.png");
	m_bg1->setAnchorPoint(Vec2(0,0));
	m_bg1->setPosition(Point(0,0));
	m_bg2 = Sprite::create("bg2.png");
	m_bg2->setAnchorPoint(Vec2(0,0));

	m_star1 = Sprite::create("star1.png");
	m_star1->setAnchorPoint(Vec2(0,0));
	m_star1->setPosition(Point(0,0));
	m_star2 = Sprite::create("star1.png");
	m_star2->setAnchorPoint(Vec2(0,0));


	this->addChild(m_bg1,0);
	this->addChild(m_bg2,0);
	this->addChild(m_star1,0);
	this->addChild(m_star2,0);
	this->m_pAllBg->addObject(m_bg1);
	this->m_pAllBg->addObject(m_bg2);
	this->m_pAllStar->addObject(m_star1);
	this->m_pAllStar->addObject(m_star2);
	m_BgHeight = m_bg1->getContentSize().height;
	m_bg2->setPosition(Point(0,m_BgHeight-2));
	m_star2->setPosition(Point(0,m_BgHeight-2));
	m_BgMoveValue = -1;
	m_StarMove = -2;

}
void GameScene::update(float)
{

	Ref *obj = NULL;
	CCARRAY_FOREACH(this->m_pAllBg,obj)
	{
        movingBackground(obj,GameData::Inst()->bgSpeed);
	}
	CCARRAY_FOREACH(this->m_pAllStar,obj)
	{
		movingBackgroundStar(obj,GameData::Inst()->bgSpeed);
	}
}
void GameScene::movingBackground(Ref *pObj,float dt)
{
	Node *bgNode = (Node*)pObj;
	bgNode->setPositionY(bgNode->getPositionY()+ m_BgMoveValue * dt);
	if(bgNode->getPositionY()< -m_BgHeight)
	{
		bgNode->setPositionY(bgNode->getPositionY()+ m_BgHeight * 2 - 2);
	}
}
void GameScene::movingBackgroundStar(Ref *pObj,float dt)
{
	Node *bgNode = (Node*)pObj;
	bgNode->setPositionY(bgNode->getPositionY()+ m_StarMove * dt);
	if(bgNode->getPositionY()< -m_BgHeight)
	{
		bgNode->setPositionY(bgNode->getPositionY()+ m_BgHeight * 2 - 2);
	}
}