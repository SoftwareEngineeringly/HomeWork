#include "WelcomeLayer.h"
#include "GameData.h"
bool WelcomeLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	
	Sprite *story1 = Sprite::create("welcomebg.jpg");
	story1->setAnchorPoint(Point(0,0));
    story1->setPosition(Point::ZERO);
	this->addChild(story1,-99);
    
    if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() && GameData::Inst()->isMusicBgOpen)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.mp3",true);
	}

	SimpleAudioEngine::getInstance()->preloadEffect("sound/button.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy1_down.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy3_down.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/big_spaceship_flying.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/game_over.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/get_bomb.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/bullet.wav");


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
	Size winSize = Director::getInstance()->getWinSize();

	userVo = new UserVO();
	string fullDBPath = FileUtils::getInstance()->getWritablePath() + "userInfo.db";

	DBUtil::initDB(fullDBPath.c_str());  
	if (!DBUtil::tableIsExist("userInfo"))
	{
		
		string sql = "create table userInfo(mId integer primary key autoincrement,name text,lastscore integer,bestscore integer,lastkm integer,bestkm integer,jifen integer)";
		DBUtil::createTable(sql.c_str(),"userInfo");
		
		string sqlss = "insert into userInfo (name,lastscore,bestscore,lastkm,bestkm,jifen) values ('admin',0,0,0,0,0)";
		
		DBUtil::insertData(sqlss);  
	}

	getHighestHistorySorce();

    auto logowords = Sprite::create("logoWord.png");
    
    logowords->setPosition(Point(winSize.width/2,winSize.height/2+300));
    
    this->addChild(logowords,10);

    Sprite *normalFight=Sprite::create("fight1.png");
	Sprite *pressFight=Sprite::create("fight2.png");
    
    auto btnFight = MenuItemSprite::create(normalFight, pressFight, CC_CALLBACK_1(WelcomeLayer::playGame, this));
    btnFight->setPosition(Point(winSize.width/2,btnFight->getContentSize().height+180));


    Sprite *normalFight2=Sprite::create("fight2_1.png");
    Sprite *pressFight2=Sprite::create("fight2_2.png");
    
    auto btnFight2 = MenuItemSprite::create(normalFight2, pressFight2, CC_CALLBACK_1(WelcomeLayer::playGame2, this));
    btnFight2->setPosition(Point(winSize.width/2,btnFight->getContentSize().height/2+125));
    
    
    Sprite *normalSet=Sprite::create("set1.png");
	Sprite *pressSet=Sprite::create("set2.png");

    auto btnSet = MenuItemSprite::create(normalSet, pressSet, CC_CALLBACK_1(WelcomeLayer::menuSetCallback, this));
	btnSet->setPosition(Point(btnSet->getContentSize().width/2+100,btnSet->getContentSize().height/2));
	

    Sprite *normalExit=Sprite::create("exit1.png");
	Sprite *pressExit=Sprite::create("exit2.png");
    auto btnExit = MenuItemSprite::create(normalExit, pressExit, CC_CALLBACK_1(WelcomeLayer::menuExitCallback, this));
    
	btnExit->setPosition(Point(winSize.width-btnExit->getContentSize().width/2-100,btnExit->getContentSize().height/2));

    Sprite *normalShare=Sprite::create("share1.png");
    Sprite *pressShare=Sprite::create("share2.png");
    auto btnShare = MenuItemSprite::create(normalShare, pressShare, CC_CALLBACK_1(WelcomeLayer::menuShareCallback, this));
    btnShare->setPosition(Point(winSize.width/2,btnExit->getContentSize().height/2));
    
	Menu *menu=Menu::create(btnFight2,btnFight,btnSet,btnExit,btnShare,NULL);
    menu->setPosition(Point::ZERO);
	this->addChild(menu);


    plane = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane1.png"));

	plane->setPosition(Point(winSize.width/2,winSize.height/2));
   
	this->addChild(plane,1,1);
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane2.png"));
	Blink *blink = Blink::create(1,3);
	Animate *animate = Animate::create(animation);
	plane->runAction(blink);
	plane->runAction(animate);

    plane1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane1.png"));
	plane1->setPosition(Point(winSize.width/2-70,winSize.height/2-100));
	this->addChild(plane1,1,1);
	Animation *animation1 = Animation::create();
	animation1->setDelayPerUnit(0.1f);
	animation1->setLoops(-1);
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane1.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane2.png"));
	Blink *blink1 = Blink::create(1,3);
	Animate *animate1 = Animate::create(animation1);
	plane1->runAction(blink1);
	plane1->runAction(animate1);


	plane2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane1.png"));
	plane2->setPosition(Point(winSize.width/2+70,winSize.height/2-100));
	this->addChild(plane2,1,1);
	Animation *animation2 = Animation::create();
	animation2->setDelayPerUnit(0.1f);
	animation2->setLoops(-1);
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane1.png"));
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane2.png"));
    Blink *blink2 = Blink::create(1,3);
	Animate *animate2 = Animate::create(animation2);
	plane2->runAction(blink2);
	plane2->runAction(animate2);

	DBUtil::closeDB();  
	return true;
}
void WelcomeLayer::playGame(Ref *obj)
{
    GameData::Inst()->gameMode=GameMode::NORMAL;
    
    if (GameData::Inst()->isEffectOpen) {
        SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3",false);
    }
	Size winSize = Director::getInstance()->getWinSize();
	MoveTo *move= MoveTo::create(1.0f,Point(winSize.width/2,winSize.height+plane->getContentSize().height/2));
	CallFuncN *moveDone = CallFuncN::create(this,callfuncN_selector(WelcomeLayer::changeScene));
	FiniteTimeAction *sequence = Sequence::create(move,moveDone,NULL);
	plane->runAction(sequence);


	plane1->setRotation(-40.0f);
	MoveTo *moveTo= MoveTo::create(1.0f,Point(0,winSize.height-20));
	FiniteTimeAction *sequence1To = Sequence::create(moveTo,NULL);
	plane1->runAction(sequence1To);

	plane2->setRotation(40.0f);
	MoveTo *move2To= MoveTo::create(1.0f,Point(winSize.width,winSize.height-20));
	FiniteTimeAction *sequence2To = Sequence::create(move2To,NULL);
	plane2->runAction(sequence2To);

}
void WelcomeLayer::playGame2(Ref *obj)
{
     GameData::Inst()->gameMode=GameMode::SPEED;
    if (GameData::Inst()->isEffectOpen) {
        SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3",false);
    }
    Size winSize = Director::getInstance()->getWinSize();
    MoveTo *move= MoveTo::create(1.0f,Point(winSize.width/2,winSize.height+plane->getContentSize().height/2));
    CallFuncN *moveDone = CallFuncN::create(this,callfuncN_selector(WelcomeLayer::changeScene));
    FiniteTimeAction *sequence = Sequence::create(move,moveDone,NULL);
    plane->runAction(sequence);
    
    
    plane1->setRotation(-40.0f);
    MoveTo *moveTo= MoveTo::create(1.0f,Point(0,winSize.height-20));
    FiniteTimeAction *sequence1To = Sequence::create(moveTo,NULL);
    plane1->runAction(sequence1To);
    
    plane2->setRotation(40.0f);
    MoveTo *move2To= MoveTo::create(1.0f,Point(winSize.width,winSize.height-20));
    FiniteTimeAction *sequence2To = Sequence::create(move2To,NULL);
    plane2->runAction(sequence2To);
    
}
void WelcomeLayer::menuExitCallback(Ref* pSender)
{
    if (GameData::Inst()->isEffectOpen) {
        SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3",false);
    }
    GameData::Inst()->showInsert();
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void WelcomeLayer::menuShareCallback(Ref* pSender)
{
    if (GameData::Inst()->isEffectOpen) {
        SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3",false);
    }

    GameData::Inst()->Share();
}
void WelcomeLayer::menuSetCallback(Ref* pSender)
{
    if (GameData::Inst()->isEffectOpen) {
        SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3",false);
    }
    setLayer* m_setlayer=setLayer::create();
    m_setlayer->setScale(0.1);
    auto scaleOne=ScaleTo::create(0.1f, 0.3f);
    auto scaleTwo=ScaleTo::create(0.1f, 0.6f);
    auto scaleThr=ScaleTo::create(0.1f, 0.8f);
    auto scaleFor=ScaleTo::create(0.1f, 1.0f);
    m_setlayer->runAction(Sequence::create(scaleOne,scaleTwo,scaleThr,scaleFor, NULL));
    addChild(m_setlayer,100);
}

void WelcomeLayer::changeScene(Node *pSender)
{
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	Sprite *pl = (Sprite*)pSender;
	this->removeChild(pl,true);
    Scene *mainScene;

    if (GameData::Inst()->gameMode == GameMode::NORMAL) {
        mainScene= MainScene::scene();
    }else if (GameData::Inst()->gameMode == GameMode::SPEED)
    {
        mainScene = HardScene::scene();
    }
   
	Scene *newscene = CCTransitionSlideInT ::create(1,mainScene);
	Director::getInstance()->replaceScene(newscene);

}
Scene* WelcomeLayer::scene()
{

	Scene* scene  = Scene::create();

	WelcomeLayer* layer = WelcomeLayer::create();
	scene->addChild(layer);
	return scene;
}
bool WelcomeLayer::isHaveSaveFile()
{
	if (!CCUserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml"))
	{
		
		CCUserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml",true);
		CCUserDefault::getInstance()->setIntegerForKey("HighestScore",0);
		CCUserDefault::getInstance()->flush();
		return false;
	}
	else
	{
		return true;
	}
}

void WelcomeLayer::getHighestHistorySorce()
{ 
	string selectStr = "select * from userInfo";  
	userVo->mId = 1;  
	DBUtil::getDataInfo(selectStr,userVo);
    GameData::Inst()->highestScore = userVo->bestscore;
    GameData::Inst()->hightestkm = userVo->bestkm;
    GameData::Inst()->setJfNum(userVo->jifen);

}