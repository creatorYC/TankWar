#ifndef __MAIN__MENU__
#define __MAIN__MENU__

#include "cocos2d.h"
USING_NS_CC;

enum MyTag
{
	TAGSTART,
	TAGHELP,
	TAGSOUND,
	TAGEXIT
};
class MainMenu : Layer
{
public:
	Size size = Director::getInstance()->getWinSize();
	static Scene* createScene();
	CREATE_FUNC(MainMenu);
	virtual bool init();
	void menuCallBack(Ref* obj);
};



#endif