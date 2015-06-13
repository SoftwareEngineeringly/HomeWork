#ifndef GameData_h
#define GameData_h
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace CocosDenshion;
enum GameMode
{
    NORMAL,
    SPEED
};
class GameData {
    static GameData* s_pcIf;
public:
    static GameData* Inst();
    float    minSpeed;
    float    maxSpeed;
    float    min3Speed;
    float    max3Speed;
    int      bgSpeed;
    int      gameMode;
    bool     isSpeedOpen;
    int      canRelive;
    int      jifenNum;
private:
	GameData();
public:
    void resetSpeed();
    int  getJfNum();
    void setJfNum(int number);
    int  isRelive();
    int  activityMode();
    int  highestScore;
    int  hightestkm;
    bool isEffectOpen;
    bool isMusicBgOpen;
    bool isRleiveSuc;
    void playVideo(const char *url);
    int sendRleiveInfo();
    void Share();
    void showBanner();
    void showInsert();
    void ShareImage();
    int  relieveNum;
    void shwoWall();
};

#endif
