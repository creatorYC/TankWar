#include "HelpScene.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Scene* HelpScene::createScene()
{
	auto scene = Scene::create();
	auto layer = HelpScene::create();
	scene->addChild(layer);
	return scene;
}
bool HelpScene::init()
{
	if (!Layer::init())
		return false;

	auto size = Director::getInstance()->getWinSize();
	//Ìí¼Ó±³¾°Í¼Æ¬
	auto spHelpBk = Sprite::create("helpBK.png");
	spHelpBk->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(spHelpBk);

	auto menuItemBack =
		MenuItemImage::create("back_menu.png", "back_menu_select.png", CC_CALLBACK_1(HelpScene::menuCallBack, this));

	auto menu = Menu::create(menuItemBack, NULL);
	menu->setPosition(Point::ZERO);
	menuItemBack->setPosition(Point(size.width - menuItemBack->getContentSize().width - 20,
		menuItemBack->getContentSize().height + 30));
	this->addChild(menu);
	return true;
}
void HelpScene::menuCallBack(Ref* obj)
{
	SimpleAudioEngine::getInstance()->playEffect("select.wav");
	Scene* scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}