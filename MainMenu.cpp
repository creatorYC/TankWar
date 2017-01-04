#include "MainMenu.h"
#include "GameWorld.h"
#include "HelpScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}
bool MainMenu::init()
{
	if (!Layer::init())
		return false;
	//添加背景图片
	auto spBkGround = Sprite::create("mainBK.png");
	spBkGround->setPosition(Point(size.width/2,size.height/2));
	this->addChild(spBkGround);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("tankwar.mp3",true);//播放背景音乐
	//添加四个菜单条目（开始、帮助、退出、音效）
	auto menuItemStart = 
		MenuItemImage::create("start_game.png", 
		"start_game_select.png", CC_CALLBACK_1(MainMenu::menuCallBack, this));
	menuItemStart->setTag(MyTag::TAGSTART);
	auto menuItemHelp =
		MenuItemImage::create("help.png",
		"help_select.png", CC_CALLBACK_1(MainMenu::menuCallBack, this));
	menuItemHelp->setTag(MyTag::TAGHELP);
	auto menuItemSound =
		MenuItemImage::create("open_effect.png",
		"open_effect_select.png", CC_CALLBACK_1(MainMenu::menuCallBack, this));
	menuItemSound->setTag(MyTag::TAGSOUND);
	auto menuItemExit =
		MenuItemImage::create("exit_game.png",
		"exit_game_select.png", CC_CALLBACK_1(MainMenu::menuCallBack, this));
	menuItemExit->setTag(MyTag::TAGEXIT);
	auto menu = Menu::create(menuItemStart, menuItemHelp, menuItemExit, menuItemSound, NULL);
	menu->setPosition(Point::ZERO);
	menuItemStart->setPosition(Point(size.width-menuItemStart->getContentSize().width-20,
		menuItemStart->getContentSize().height+150));
	menuItemHelp->setPosition(Point(size.width - menuItemHelp->getContentSize().width - 20,
		menuItemHelp->getContentSize().height + 105));
	menuItemSound->setPosition(Point(size.width - menuItemSound->getContentSize().width - 20,
		menuItemSound->getContentSize().height + 60));
	menuItemExit->setPosition(Point(size.width - menuItemExit->getContentSize().width - 20,
		menuItemExit->getContentSize().height + 15));
	this->addChild(menu);
	return true;
}
void MainMenu::menuCallBack(Ref* obj)
{
	auto menuItemTarget = (Node*)obj;
	Scene* scene;

	switch (menuItemTarget->getTag())
	{
	case MyTag::TAGSTART:
		scene = GameWorld::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	case MyTag::TAGHELP:
		scene = HelpScene::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	case MyTag::TAGSOUND:
		
		break;
	case MyTag::TAGEXIT:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
	SimpleAudioEngine::getInstance()->playEffect("select.wav");//播放音效
}