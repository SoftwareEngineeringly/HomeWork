#include "AppDelegate.h"
#include "logo.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"
#include "WelcomeLayer.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("star war");
        director->setOpenGLView(glview);
    }

    auto screenSize=glview->getFrameSize();
    auto designSize = Size(540,960);//Size(640,960);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
#else
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_WIDTH);
#endif

    // create a scene. it's an autorelease object
	auto scene = logo::scene();
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    //GameData::Inst()->showInsert();
    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    // if you use SimpleAudioEngine, it must resume here
    if (GameData::Inst()->isMusicBgOpen) {
        SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
    }
    if (GameData::Inst()->isMusicBgOpen) {
        SimpleAudioEngine::getInstance()->resumeAllEffects();
    }
}