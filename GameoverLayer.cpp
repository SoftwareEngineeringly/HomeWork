#include "GameoverLayer.h"
#include "GameData.h"

GameoverLayer::GameoverLayer()
{

}
GameoverLayer::~GameoverLayer()
{

}
bool GameoverLayer::initWithColor(const Color4B& color)
{
    if (!LayerColor::initWithColor(color)) {
        return false;
    }
    
    SimpleAudioEngine::getInstance()->pauseAllEffects();
	SimpleAudioEngine::getInstance()->unloadEffect("sound/enemy1_down.mp3");
	SimpleAudioEngine::getInstance()->unloadEffect("sound/enemy3_down.mp3");
	SimpleAudioEngine::getInstance()->unloadEffect("sound/big_spaceship_flying.mp3");
	SimpleAudioEngine::getInstance()->unloadEffect("sound/game_over.mp3");
	SimpleAudioEngine::getInstance()->unloadEffect("sound/get_bomb.mp3");
    
	Size winSize = Director::getInstance()->getWinSize();
    
    Sprite *storyScoreWin = Sprite::create("gamestore.png");
    storyScoreWin->setScale(1.0);
    storyScoreWin->setPosition(Point(winSize.width/2,winSize.height/2));
    this->addChild(storyScoreWin);

    
    
	string fullDBPath = FileUtils::getInstance()->getWritablePath() + "userInfo.db";
	DBUtil::initDB(fullDBPath.c_str());  

    if (GameData::Inst()->gameMode == NORMAL) {
        if (score > GameData::Inst()->highestScore)
        {
            GameData::Inst()->highestScore = score;
            
            if (DBUtil::tableIsExist("userInfo"))
            {
                stringstream strStream;
                strStream <<"update userInfo set bestscore ="<<score<<",lastscore="<<score<<";";
                string updateString = strStream.str();
                
                DBUtil::updateData(updateString);
            }
            
        }
        else
        {
            stringstream strStream;
            strStream <<"update userInfo set lastscore ="<<score<<";";  
            string updateString = strStream.str();
            DBUtil::updateData(updateString);  
        }
    }else
    {
        if (score > GameData::Inst()->hightestkm)
        {
            GameData::Inst()->hightestkm = score;
            
            if (DBUtil::tableIsExist("userInfo"))
            {
                stringstream strStream;
                strStream <<"update userInfo set bestkm ="<<score<<",lastkm="<<score<<";";
                string updateString = strStream.str();
                DBUtil::updateData(updateString);
            }
            
        }
        else
        {
            stringstream strStream;
            strStream <<"update userInfo set lastkm ="<<score<<";";
            string updateString = strStream.str();
            DBUtil::updateData(updateString);  
        }
    }
    

    char buf[100];
    Sprite* spTmp = Sprite::create("number2.png");
    
    if (spTmp) {
        Size sz = spTmp->getContentSize();
        snprintf(buf, 99, "%d", score);
        lableCurScore = LabelAtlas::create(buf, "number2.png", sz.width/10+0.5, sz.height, '0');
        lableCurScore->setAnchorPoint(Point(0, 1));
       
    }
     Sprite* spTmp2 = Sprite::create("number_green.png");
    if (spTmp2) {
        Size sz = spTmp2->getContentSize();
        snprintf(buf, 99, "%d", score);
        if (GameData::Inst()->gameMode==NORMAL) {
            sprintf(buf, "%d", GameData::Inst()->highestScore);
        }else
        {
            sprintf(buf, "%d", GameData::Inst()->hightestkm);
        }
        
        labHighestScore = LabelAtlas::create(buf, "number_green.png", sz.width/10+0.5, sz.height, '0');
        labHighestScore->setAnchorPoint(Point(0, 1));
    }
    
    
    Size labHighest = labHighestScore->getContentSize();
    labHighestScore->setPosition(Point(winSize.width/2+32,winSize.height/2-70));
    labHighestScore->setScale(1.0);
    this->addChild(labHighestScore);
    lableCurScore->setPosition(Point(winSize.width/2+32,winSize.height/2+60));
    lableCurScore->setScale(1.0);
    DelayTime *delay = DelayTime::create(1.0f);
    ScaleTo *scaleBig = ScaleTo::create(1.0f,3.0f);
    ScaleTo *scaleLittle = ScaleTo::create(0.3f,1.3f);
    FiniteTimeAction *sequence = Sequence::create(delay,scaleBig,scaleLittle,NULL);
    lableCurScore->runAction(sequence);
    this->addChild(lableCurScore);

    if (GameData::Inst()->gameMode==NORMAL) {

		auto spcurScore = Label::createWithSystemFont("current score:", "", 28);

		auto spHightestScore = Label::createWithSystemFont("highest score:", "", 28);
        spHightestScore->setPosition(Point(winSize.width/2+80,winSize.height/2-35));
        spcurScore->setPosition(Point(winSize.width/2+80,winSize.height/2+90));
        
        spcurScore->setColor(Color3B(54,179,175));
        spHightestScore->setColor(Color3B(54,179,175));
        addChild(spcurScore);
        addChild(spHightestScore);
    }else
    {
        auto lb_curkm = Label::createWithSystemFont("current miles(km):","", 28);
        auto lb_hightkm = Label::createWithSystemFont("highest miles(km):","", 28);
        lb_hightkm->setPosition(Point(winSize.width/2+130,winSize.height/2-35));
        lb_curkm->setPosition(Point(winSize.width/2+130,winSize.height/2+90));
        
        lb_curkm->setColor(Color3B(54,179,175));
        lb_hightkm->setColor(Color3B(54,179,175));
        addChild(lb_curkm);
        addChild(lb_hightkm);
    }
    

	Sprite *normalBack=Sprite::create("btnback1.png");
	Sprite *pressBack=Sprite::create("btnback2.png");
    
    auto btnback = MenuItemSprite::create(normalBack, pressBack,CC_CALLBACK_1(GameoverLayer::backMainScene,this));
    
	btnback->setPosition(Point(winSize.width/2-btnback->getContentSize().width/2-60,
                                                winSize.height/2-btnback->getContentSize().height/2-10));

    btnback->setScale(1.0);
    auto btnshare = MenuItemImage::create("showshare1.png", "showshare2.png",CC_CALLBACK_1(GameoverLayer::shareWeixin,this));
    btnshare->setScale(1.0);
    btnshare->setPosition(Point(winSize.width/2-btnback->getContentSize().width/2-60,winSize.height/2-btnback->getContentSize().height*2-19));
    
	Menu *menu=Menu::create(btnback,btnshare,NULL);
    menu->setPosition(Point::ZERO);
	this->addChild(menu);

	this->getStarnum();
	this->drawStarnum(starnum,starlastnum);
    
	DBUtil::closeDB();

    GameData::Inst()->showInsert();
    

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameoverLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameoverLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    touchListener->setSwallowTouches(true); 
    
	return true;
}
bool GameoverLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void GameoverLayer::onTouchEnded(Touch* touch, Event* event)
{
    
}
GameoverLayer* GameoverLayer::create(int passScore)
{
	GameoverLayer *pRet=new GameoverLayer();
	pRet->score = passScore;
    if(pRet && pRet->initWithColor(Color4B(0, 0, 0, 0)))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
Scene* GameoverLayer::scene(int passScore)
{
	Scene *scene=Scene::create();
	GameoverLayer *layer = GameoverLayer::create(passScore);
	scene->addChild(layer);
	return scene;
}
void GameoverLayer::backMainScene(Ref *obj)
{
    if (GameData::Inst()->isEffectOpen) {
        SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3",false);
    }
	Scene *welcome = WelcomeLayer::scene();
	Scene *newscene =TransitionFade::create(1,welcome);
	Director::getInstance()->replaceScene(newscene);
}
void GameoverLayer::shareWeixin(Ref *obj)
{
}
void GameoverLayer::screenShoot()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    

    RenderTexture* renderTexture = RenderTexture::create(visibleSize.width * 0.5, visibleSize.height * 0.5, Texture2D::PixelFormat::RGBA8888);
    
    Scene* curScene = Director::getInstance()->getRunningScene();
    Point ancPos = curScene->getAnchorPoint();
    

    renderTexture->begin();
    

    curScene->setScale(0.5);
    curScene->setAnchorPoint(cocos2d::Point(0, 0));
    

    curScene->visit();
    

    renderTexture->end();
    

    renderTexture->saveToFile("share.png", Image::Format::PNG);

    curScene->setScale(1);
    curScene->setAnchorPoint(ancPos);

    curScene->release();
}

void GameoverLayer::getStarnum()
{
    if (GameData::Inst()->gameMode==NORMAL) {
        if (score >= GameData::Inst()->highestScore)
        {
            this->starnum=5;
            this->starlastnum=0;
        }
        else if (score<GameData::Inst()->highestScore && score>GameData::Inst()->highestScore*0.8)
        {
            this->starnum=4;
            this->starlastnum=1;
        }
        else if (score<GameData::Inst()->highestScore*0.8 && score>GameData::Inst()->highestScore*0.6)
        {
            this->starnum=3;
            this->starlastnum=2;
        }
        else if (score<GameData::Inst()->highestScore*0.6 && score>GameData::Inst()->highestScore*0.4)
        {
            this->starnum=2;
            this->starlastnum=3;
        }
        else if (score<GameData::Inst()->highestScore*0.4 && score>GameData::Inst()->highestScore*0.2)
        {
            this->starnum=1;
            this->starlastnum=4;
        }
        else
        {
            this->starnum=0;
            this->starlastnum=5;
        }
    }else
    {
        if (score >= GameData::Inst()->hightestkm)
        {
            this->starnum=5;
            this->starlastnum=0;
        }
        else if (score<GameData::Inst()->hightestkm && score>GameData::Inst()->hightestkm*0.8)
        {
            this->starnum=4;
            this->starlastnum=1;
        }
        else if (score<GameData::Inst()->hightestkm*0.8 && score>GameData::Inst()->hightestkm*0.6)
        {
            this->starnum=3;
            this->starlastnum=2;
        }
        else if (score<GameData::Inst()->hightestkm*0.6 && score>GameData::Inst()->hightestkm*0.4)
        {
            this->starnum=2;
            this->starlastnum=3;
        }
        else if (score<GameData::Inst()->hightestkm*0.4 && score>GameData::Inst()->hightestkm*0.2)
        {
            this->starnum=1;
            this->starlastnum=4;
        }
        else
        {
            this->starnum=0;
            this->starlastnum=5;
        }
    }
        
	
    
}
void GameoverLayer::drawStarnum(int num,int lastnum)
{
	int jiange = 50;
	Size winSize = Director::getInstance()->getWinSize();
	for (int i=0;i<num;i++)
	{
		Sprite *star = Sprite::create("starPf.png");
        star->setScale(0.8f);
		star->setPosition(Point(i*jiange+105,winSize.height/2+45));
		this->addChild(star);
	}
	for (int i=0;i<lastnum;i++)
	{
		Sprite *star = Sprite::create("starPf_an.png");
        star->setScale(0.8f);
		star->setPosition(Point(num*jiange+i*jiange+105,winSize.height/2+45));
		this->addChild(star);
	}
}
