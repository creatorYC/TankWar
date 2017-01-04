#ifndef __HELP__SCENE__
#define __HELP__SCENE__
#include "cocos2d.h"
USING_NS_CC;
class HelpScene : Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(HelpScene);
	virtual bool init();
	void menuCallBack(Ref* obj);
};
#endif