#ifndef __starwar__logo__
#define __starwar__logo__

#include "cocos2d.h"
using namespace cocos2d;
class logo:public Layer
{
public:
    virtual bool init();
    static Scene* scene();
    void loading();
    void replace();
    CREATE_FUNC(logo);
};
#endif
