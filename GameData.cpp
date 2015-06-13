#include "GameData.h"
#include "DBUtil.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/jni/JniHelper.h"
    #include <jni.h>
#endif
GameData* GameData::s_pcIf = NULL;

GameData* GameData::Inst(){
    if(s_pcIf == NULL){
        s_pcIf = new GameData();
    }
    
    return s_pcIf;
}

GameData::GameData()
{
    minSpeed = 5;
    maxSpeed = 10;
    min3Speed = 15;
    max3Speed = 25;
    bgSpeed   =1;
    canRelive = 0;
    isRleiveSuc = false;
    relieveNum = 0;
}
void GameData::resetSpeed()
{
    minSpeed = 5;
    maxSpeed = 10;
    min3Speed = 15;
    max3Speed = 25;
    bgSpeed = 1;
}
int GameData::isRelive()
{
    
    return relieveNum;
}
int GameData::getJfNum()
{
    return jifenNum;
}
void GameData::setJfNum(int number)
{
    jifenNum = jifenNum+number;
    string fullDBPath = FileUtils::getInstance()->getWritablePath() + "userInfo.db";
    DBUtil::initDB(fullDBPath.c_str());
    if (DBUtil::tableIsExist("userInfo"))
    {
        stringstream strStream;
        strStream <<"update userInfo set jifen ="<<jifenNum<<";";
        string updateString = strStream.str();
        
        DBUtil::updateData(updateString);
    }
    DBUtil::closeDB();
}
void GameData::shwoWall()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jni_method_info;
    cocos2d::JniHelper::getStaticMethodInfo(jni_method_info,"org/cocos2dx/cpp/shareSupport","showWall","()Ljava/lang/String;");
    
    if (jni_method_info.methodID)
    {
         jstring jstr = (jstring)jni_method_info.env->CallStaticObjectMethod(jni_method_info.classID, jni_method_info.methodID);
         jni_method_info.env->DeleteLocalRef(jni_method_info.classID);
         string jifenStr = JniHelper::jstring2string(jstr);
         log("jifenstr = %s",jifenStr.c_str());

         setJfNum(atoi(jifenStr.c_str()));
    }
#endif
}
void GameData::Share()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jni_method_info;
    cocos2d::JniHelper::getStaticMethodInfo(jni_method_info,"org/cocos2dx/cpp/shareSupport","shareWeiXin","()V");
    
    if (jni_method_info.methodID)
    {
        jni_method_info.env->CallStaticVoidMethod(jni_method_info.classID, jni_method_info.methodID);
    }
#endif
}//shareWeiXinImage
void GameData::ShareImage()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jni_method_info;
    cocos2d::JniHelper::getStaticMethodInfo(jni_method_info,"org/cocos2dx/cpp/shareSupport","shareWeiXinImage","()V");
    
    if (jni_method_info.methodID)
    {
        jni_method_info.env->CallStaticVoidMethod(jni_method_info.classID, jni_method_info.methodID);
    }
#endif
}//shareWeiXinImage
void GameData::showBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jni_method_info;
    cocos2d::JniHelper::getStaticMethodInfo(jni_method_info,"org/cocos2dx/cpp/shareSupport","showBannerStatic","()V");
    
    if (jni_method_info.methodID)
    {
        jni_method_info.env->CallStaticVoidMethod(jni_method_info.classID, jni_method_info.methodID);
    }
#endif
}
void GameData::showInsert()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jni_method_info;
    cocos2d::JniHelper::getStaticMethodInfo(jni_method_info,"org/cocos2dx/cpp/shareSupport","showInsertStatic","()V");
    
    if (jni_method_info.methodID)
    {
        jni_method_info.env->CallStaticVoidMethod(jni_method_info.classID, jni_method_info.methodID);
    }
#endif
}
void GameData::playVideo(const char *url)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    log("c++ JniMethodInfo ini");
    cocos2d::JniMethodInfo jni_method_info;
    cocos2d::JniHelper::getStaticMethodInfo(jni_method_info,"org/cocos2dx/cpp/shareSupport",
                                            "playVideoStatic","(Ljava/lang/String;)V");
    
    if (jni_method_info.methodID)
    {
        // log("c++ showvideo");
        jstring jstr = jni_method_info.env->NewStringUTF(url);
        jni_method_info.env->CallStaticVoidMethod(jni_method_info.classID, jni_method_info.methodID,jstr);
        jni_method_info.env->DeleteLocalRef(jstr);
        jni_method_info.env->DeleteLocalRef(jni_method_info.classID);
    }
#endif
}
int GameData::sendRleiveInfo()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#endif
    return 0;
}