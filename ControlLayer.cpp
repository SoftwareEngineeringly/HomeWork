#include"ControlLayer.h"
#include "GameData.h"
bool ControlLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
    
	Sprite *normalPause=Sprite::create("normalpause.png");

	
	Sprite *scorebg = Sprite::create("scorebg.png");
    scorebg->setAnchorPoint(Point::ZERO);
	scorebg->setPosition(Point(6,winSize.height-normalPause->getContentSize().height/2-50));
	this->addChild(scorebg);
	
    //暂停开关
    m_btnPauseOpen = MenuItemImage::create("normalpause.png", "presspause.png");
    m_btnPauseClose = MenuItemImage::create("presspause.png", "normalpause.png");
    
    
    if (Director::getInstance()->isPaused()) {
        pPauseItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ControlLayer::menuPauseCallback,this),
                                                        m_btnPauseOpen,m_btnPauseClose, NULL);
    }else
    {
        pPauseItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ControlLayer::menuPauseCallback,this),
                                                        m_btnPauseClose,m_btnPauseOpen, NULL);
    }
    
    pPauseItem->setPosition(Point(normalPause->getContentSize().width/2+10,winSize.height-normalPause->getContentSize().height/2-10));
    Menu *menupause=Menu::create(pPauseItem,NULL);
    menupause->setPosition(Point::ZERO);
    this->addChild(menupause);
    
    
    
    return true;
}
void ControlLayer::menuPauseCallback(Ref* pSender)
{
    
    
	if (!Director::getInstance()->isPaused())
	{
        GameData::Inst()->showInsert();
        Director::getInstance()->pause();
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->pauseAllEffects();

	}
	else
	{
		Director::getInstance()->resume();//
		SimpleAudioEngine::getInstance()->rewindBackgroundMusic();//
		SimpleAudioEngine::getInstance()->resumeAllEffects();
	}
}
void ControlLayer::updateScore(int score)
{
	if(this->getChildByTag(SCORE_LAYER_ITEM))
	{
		this->removeChildByTag(SCORE_LAYER_ITEM,true);
		this->removeChildByTag(SCORE_LAYER_ITEM+1,true);
	}
	if (score >0 && score <9999999)
	{
		
		
		Size winSize = Director::getInstance()->getWinSize();
        
        char buf[100];
        sprintf(buf, "%d",score);
        Sprite* spTmp = Sprite::create("number.png");
        if (spTmp) {
            Size sz = spTmp->getContentSize();
            lableScore = LabelAtlas::create(buf, "number.png",sz.width/10, sz.height, '0');
            lableScore->setAnchorPoint(Point(0 , 0.5));
            lableScore->setScale(1.4);
        }

        Sprite *star =Sprite::create("km.png");
		star->setAnchorPoint(Point(0,0.5));
		star->setPosition(Point(pPauseItem->getContentSize().width+lableScore->getContentSize().width+40,winSize.height-lableScore->getContentSize().height/2-35));
        if (GameData::Inst()->gameMode==GameMode::SPEED) {
            this->addChild(star,0,SCORE_LAYER_ITEM+1);
        }
		//this->addChild(star,0,SCORE_LAYER_ITEM+1);
        lableScore->setPosition(Point(pPauseItem->getContentSize().width+15,winSize.height-lableScore->getContentSize().height/2-35));
		this->addChild(lableScore,0,SCORE_LAYER_ITEM);
		ScaleTo *scaleBig = ScaleTo::create(0.6f,2.5f);
		ScaleTo *scaleLittle = ScaleTo::create(0.2f,1.4f);
		FiniteTimeAction *sequence = Sequence::create(scaleBig,scaleLittle,NULL);
		lableScore->runAction(sequence);


	}
}