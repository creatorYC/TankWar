#include "GameWorld.h"
#include "MainMenu.h"
#include "Tank.h"
#include "Bullet.h"
#include "Explode.h"
#include "Barrier.h"
#include "BloodBar.h"
#include "Reward.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool GameWorld::isRanked_C = true;
bool GameWorld::isRanked_H = false;
bool GameWorld::isSuperBullet = false;
bool GameWorld::isSuperShoot = false;
Scene* GameWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = GameWorld::create();
	scene->addChild(layer);
	return scene;
}
bool GameWorld::init()
{
	if (!Layer::init())
		return false;
	Tank::myLife = 100;
	//��ӱ�������
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);//true ѭ��
	size = Director::getInstance()->getWinSize();
	//��ӱ���ͼƬ
	auto spHelpBk = Sprite::create("gameBackground.png");
	spHelpBk->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(spHelpBk);

	//��ӷ�����ʾ
	score = 0;
	enemyNums = 0;
	isRanked_C = true;
	isRanked_H = false;
	isSuperBullet = false;
	isSuperShoot = false;
	auto scoreBar = Sprite::create("score.png");
	scoreBar->setPosition(Point(780,600));
	this->addChild(scoreBar);
	auto label = LabelTTF::create("0", "Marker Felt", 40);
	label->setColor(Color3B::MAGENTA);
	label->setPosition(Point(880, 600));
	label->setTag(110);//���ñ�ǣ����ڲ���
	this->addChild(label);
	//���̹��Ѫ��
	//��ʼ��BloodBar  
	bloodBar = new BloodBar();
	bloodBar->setPosition(Point(150, 620));
	bloodBar->setScale(2.2f);
	bloodBar->setBackgroundTexture("box.png");
	bloodBar->setForegroundTexture("hp.png");
	bloodBar->setTotalProgress(100.0f);
	bloodBar->setCurrentProgress(100.0f);
	this->addChild(bloodBar, 2);


	//����ϰ���
	buildMap();

	//����ҷ�̹��
	Tank *tank = Tank::create(DIR_UP,true);
	tank->setTag(MY_TANK);//
	//����̹�˷���
	tank->setGood(true);
	tank->setDir(DIR_UP);
	tank->setLife(100);
	tank->setLive(true);
	tank->setLocationX(size.width/2-140);
	tank->setLocationY(30);
	tank->setPosition(Point(size.width/2-140,30));
	//tank->setAnchorPoint(Point::ZERO);
	this->addChild(tank);

	/*auto label2 = LabelTTF::create("life:100", "Marker Felt", 30);
	label2->setColor(Color3B::RED);
	label2->setPosition(Point(60, 620));
	label2->setTag(100);//���ñ�ǣ����ڲ���
	this->addChild(label2);*/
	
	//��ӵ���̹��
	for (int i = 0; i < 5; i++)
	{
		newEnemy();
		enemyNums++;
	}
	
	auto menuItemBack =
		MenuItemImage::create("back_menu.png", "back_menu_select.png", CC_CALLBACK_1(GameWorld::menuCallBack, this));

	auto menu = Menu::create(menuItemBack, NULL);
	menu->setPosition(Point::ZERO);
	menuItemBack->setPosition(Point(size.width - menuItemBack->getContentSize().width - 20,
		menuItemBack->getContentSize().height + 30));
	this->addChild(menu);

	//������Ӧ
		listenerKeyboard = EventListenerKeyboard::create();
		listenerKeyboard->onKeyPressed = CC_CALLBACK_2(GameWorld::onKeyPressed, this);
		listenerKeyboard->onKeyReleased = CC_CALLBACK_2(GameWorld::onKeyReleased, this);
		listenerKeyboard->setEnabled(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
		
	//�ƻ�����
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameWorld::enemyMove),0.4);//����̹���ƶ�
	this->schedule(schedule_selector(GameWorld::enemyFire), 2);//����̹�˿���
	return true;
}
void GameWorld::menuCallBack(Ref* obj)
{
	Scene* scene = MainMenu::createScene();
	SimpleAudioEngine::getInstance()->playEffect("select.wav");
	Director::getInstance()->replaceScene(scene);
}
void GameWorld::buildMap()
{
	for (int j = 1; j <= 3; j++)
	{
		Barrier *barrier;
		for (int i = 27; i >3; i--)
		{
			if (i > 19)
			{
				barrier = Barrier::create(BARRIER_TILE);//��Ƭ����
				barrier->setType(BARRIER_TILE);
			}
			else if (i > 11)
			{
				barrier = Barrier::create(BARRIER_STEER_1);//�ְ�1����
				barrier->setType(BARRIER_STEER_1);
			}
			else
			{
				barrier = Barrier::create(BARRIER_TILE);//��Ƭ����
				barrier->setType(BARRIER_TILE);
			}
			barrier->setLocation(i * 30, size.height - 120 * j);
			barrier->setPosition(Point(i * 30, size.height - 120 * j));
			//	barrier->setAnchorPoint(Point::ZERO);
			barrier->setGood(false);//һ���ϰ���
			barriers.pushBack(barrier);//��ӵ��ϰ�������
			this->addChild(barrier);
		}
	}
	for (int j = 0; j <= 3; j++)
	{
		Barrier *barrier;
		for (int i = 0; i < 13; i++)
		{
			if (i == 5 || i == 6 || i == 7)
			{
				barrier = Barrier::create(BARRIER_TREE);//�����ϰ���
				barrier->setType(BARRIER_TREE);
			}
			else
			{
				barrier = Barrier::create(BARRIER_TILE);
				barrier->setType(BARRIER_TILE);
			}
			barrier->setLocation(120 + j * 240, size.height - 120 - i * 30);
			barrier->setPosition(Point(120 + j * 240, size.height - 120 - i * 30));
			//	barrier->setAnchorPoint(Point::ZERO);
			barrier->setGood(false);//һ���ϰ���
			this->addChild(barrier);
			barriers.pushBack(barrier);//��ӵ��ϰ�������
		}
	}
	//����ҷ�����
	for (int i = 0; i < 4; i++)
	{
		Barrier *barrier = Barrier::create(BARRIER_TILE);
		barrier->setType(BARRIER_TILE);
		barrier->setLocation(size.width / 2 - 80 + 30 * i, 120);
		barrier->setPosition(Point(size.width / 2 - 80 + 30 * i, 120));
		//barrier->setAnchorPoint(Point::ZERO);
		barrier->setGood(true);//�ҷ�����
		this->addChild(barrier);
		barriers.pushBack(barrier);
	}
	for (int j = 0; j <= 1; j++)
	{
		Barrier *barrier;
		for (int i = 0; i <= 4; i++)
		{
			barrier = Barrier::create(BARRIER_TILE);
			barrier->setType(BARRIER_TILE);
			barrier->setLocation(size.width / 2 - 80 + 120 * j, 120 - 30 * i);
			barrier->setPosition(Point(size.width / 2 - 80 + 120 * j, 120 - 30 * i));
			//	barrier->setAnchorPoint(Point::ZERO);
			barrier->setGood(true);//�ҷ�����
			this->addChild(barrier);
			barriers.pushBack(barrier);
		}
	}
	Barrier *barrier = Barrier::create(BARRIER_ROOM);
	barrier->setType(BARRIER_ROOM);
	barrier->setLocation(450,40);
	barrier->setPosition(Point(450, 40));
	this->addChild(barrier);
	barriers.pushBack(barrier);
}
void GameWorld::newEnemy()
{
	MoveDir dirs[] = { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };
	MoveDir dir = dirs[random() % 4];
	Tank *enemyTank = Tank::create(dir, false);
	enemyTank->setLive(true);
	enemyTank->setLife(50);
	enemyTank->setTag(ENEMY_TANK);
	enemyTank->setGood(false);
	enemyTank->setDir(dir);
	float locX = rand() % 850 + 60;
	enemyTank->setLocationX(locX);
	enemyTank->setLocationY(size.height - 50);
	enemyTank->setPosition(Point(locX, size.height - 50));
	this->addChild(enemyTank);
	enemyTanks.pushBack(enemyTank);
}
void GameWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto tank = (Tank*)this->getChildByTag(MY_TANK);
	auto x = tank->getLocationX();
	auto y = tank->getLocationY();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		if (tank->getDir() != DIR_UP)
		{
			//tank->turnTo(DIR_UP, tank->getDir());
			tank->removeFromParentAndCleanup(true);
			tank = Tank::create(DIR_UP,true);	
			tank->setTag(MY_TANK);
			//tank->setTag(DIR_UP);
			tank->setAnchorPoint(Point::ZERO);
			tank->setDir(DIR_UP);
			this->addChild(tank);
		}
		
		if (y <= Director::getInstance()->getWinSize().height - 30)
			tank->setPosition(Point(x, y + 15));
		else
			tank->setPosition(Point(x, Director::getInstance()->getWinSize().height-40));
		break;
	case EventKeyboard::KeyCode::KEY_A:
		if (tank->getDir() != DIR_LEFT)
		{
			//tank->turnTo(DIR_LEFT, tank->getDir());
			tank->removeFromParentAndCleanup(true);
			tank = Tank::create(DIR_LEFT,true);
			tank->setTag(MY_TANK);
			//tank->setTag(DIR_LEFT);
			tank->setAnchorPoint(Point::ZERO);
			this->addChild(tank);
			tank->setDir(DIR_LEFT);
		}		
		
		if (x >= 30)
		{
			tank->setPosition(Point(x - 15, y));
		}
		else
			tank->setPosition(Point(40, y));
		break;
	case EventKeyboard::KeyCode::KEY_S:
		if (tank->getDir() != DIR_DOWN)
		{
			//tank->turnTo(DIR_DOWN, tank->getDir());
			tank->removeFromParentAndCleanup(true);
			tank = Tank::create(DIR_DOWN,true);
			tank->setTag(MY_TANK);
			//tank->setTag(DIR_DOWN);
			tank->setAnchorPoint(Point::ZERO);
			this->addChild(tank);
			tank->setDir(DIR_DOWN);
		}
		
		if (y >= 30)
			tank->setPosition(Point(x, y - 15));
		else
			tank->setPosition(Point(x, 40));
		break;
	case EventKeyboard::KeyCode::KEY_D:
		if (tank->getDir() != DIR_RIGHT)
		{
			//tank->turnTo(DIR_RIGHT, tank->getDir());
			tank->removeFromParentAndCleanup(true);
			tank = Tank::create(DIR_RIGHT,true);
			tank->setTag(MY_TANK);
			//tank->setTag(DIR_RIGHT);
			tank->setAnchorPoint(Point::ZERO);
			this->addChild(tank);
			tank->setDir(DIR_RIGHT);
		}
		
		if (x <= Director::getInstance()->getWinSize().width - 30)
			tank->setPosition(Point(x + 15, y));
		else
			tank->setPosition(Point(Director::getInstance()->getWinSize().width - 40, y));
		break;
	case EventKeyboard::KeyCode::KEY_J:
		if (isSuperBullet)
			isSuperShoot = false;//�����J���������������䣬����ԭ�ȵ��ӵ�
		if (tank->getDir() == DIR_UP)
		{
			Bullet *bullet = Bullet::create(B_DIR_UP,true);
			bullet->setPosition(tank->getPosition());
			this->addChild(bullet);		
			tank->bullets.pushBack(bullet);
			if (tank->bullets.size() > 0)
				tank->shoot(DIR_UP);
		}		
		else if (tank->getDir() == DIR_DOWN)
		{
			Bullet *bullet = Bullet::create(B_DIR_DOWN,true);
			bullet->setPosition(tank->getPosition());
			this->addChild(bullet);
			tank->bullets.pushBack(bullet);
			if (tank->bullets.size() > 0)
				tank->shoot(DIR_DOWN);
		}
			
		else if (tank->getDir() == DIR_LEFT)
		{
			Bullet *bullet = Bullet::create(B_DIR_LEFT,true);
			bullet->setPosition(tank->getPosition());
			this->addChild(bullet);
			tank->bullets.pushBack(bullet);
			if (tank->bullets.size() > 0)
				tank->shoot(DIR_LEFT);
		}
			
		else if (tank->getDir() == DIR_RIGHT)
		{
			Bullet *bullet = Bullet::create(B_DIR_RIGHT,true);
			bullet->setPosition(tank->getPosition());
			this->addChild(bullet);
			tank->bullets.pushBack(bullet);
			if (tank->bullets.size() > 0)
				tank->shoot(DIR_RIGHT);
		}
		break;
	case EventKeyboard::KeyCode::KEY_K:
		if (isSuperBullet)
			isSuperShoot = true;//�����K��������������
		if (GameWorld::isSuperBullet)
		{
			if (isSuperShoot)	//����������
			{
				Bullet *bullet1 = Bullet::create(B_DIR_RIGHT, true);
				bullet1->setPosition(tank->getPosition());
				this->addChild(bullet1);
				tank->bullets.pushBack(bullet1);
				if (tank->bullets.size() > 0)
				{
					tank->shoot(DIR_RIGHT);
				}
				Bullet *bullet2 = Bullet::create(B_DIR_LEFT, true);
				bullet2->setPosition(tank->getPosition());
				this->addChild(bullet2);
				tank->bullets.pushBack(bullet2);
				if (tank->bullets.size() > 0)
				{
					tank->shoot(DIR_LEFT);
				}
				Bullet *bullet3 = Bullet::create(B_DIR_UP, true);
				bullet3->setPosition(tank->getPosition());
				this->addChild(bullet3);
				tank->bullets.pushBack(bullet3);
				if (tank->bullets.size() > 0)
				{
					tank->shoot(DIR_UP);
				}
				Bullet *bullet4 = Bullet::create(B_DIR_DOWN, true);
				bullet4->setPosition(tank->getPosition());
				this->addChild(bullet4);
				tank->bullets.pushBack(bullet4);
				if (tank->bullets.size() > 0)
				{
					tank->shoot(DIR_DOWN);
				}
				isSuperBullet = false;
				isSuperShoot = false;
			}
		}
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
		break;
	case EventKeyboard::KeyCode::KEY_SHIFT:
		break;
	
	default:
		break;
	}
}
void GameWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto tank = (Tank*)this->getChildByTag(MY_TANK);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		tank->setDir(DIR_UP);
		tank->setLocationX(tank->getPosition().x);
		tank->setLocationY(tank->getPosition().y);
		break;
	case EventKeyboard::KeyCode::KEY_A:
		tank->setDir(DIR_LEFT);
		tank->setLocationX(tank->getPosition().x);
		tank->setLocationY(tank->getPosition().y);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		tank->setDir(DIR_DOWN);
		tank->setLocationX(tank->getPosition().x);
		tank->setLocationY(tank->getPosition().y);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		tank->setDir(DIR_RIGHT);
		tank->setLocationX(tank->getPosition().x);
		tank->setLocationY(tank->getPosition().y);
		break;
	case EventKeyboard::KeyCode::KEY_J:
		tank->setDir(tank->getDir());
		tank->setLocationX(tank->getPosition().x);
		tank->setLocationY(tank->getPosition().y);
		
		break;
	case EventKeyboard::KeyCode::KEY_K:
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
		break;
	case EventKeyboard::KeyCode::KEY_SHIFT:
		break;

	default:
		break;
	}
}
void GameWorld::enemyFire(float t)
{
	for (int i = 0; i < enemyTanks.size(); i++)
	{
		auto enemyTank = enemyTanks.at(i);
		Bullet *bullet = Bullet::create(B_DIR_UP, false);
		enemyBullets.pushBack(bullet);
		bullet->setPosition(enemyTank->getPosition());
		this->addChild(bullet);
		if (enemyTank->getDir() == DIR_UP)
		{
			bullet->runAction(MoveTo::create(5, Point(bullet->getPositionX(),
				Director::getInstance()->getWinSize().height + 50)));
			if (bullet->getPositionY() >= Director::getInstance()->getWinSize().height)
			{
				bullet->setLive(false);
				enemyBullets.eraseObject(bullet);
				bullet->removeFromParent();
			}
		}
		else if (enemyTank->getDir() == DIR_DOWN)
		{
			bullet->runAction(MoveTo::create(5, Point(bullet->getPositionX(), -50)));
			if (bullet->getPositionY() == -50)
			{
				bullet->setLive(false);
				enemyBullets.eraseObject(bullet);
				bullet->removeFromParent();
			}
		}

		else if (enemyTank->getDir() == DIR_LEFT)
		{
			bullet->runAction(MoveTo::create(5, Point(-50, bullet->getPositionY())));
			if (bullet->getPositionX() < 0)
			{
				bullet->setLive(false);
				enemyBullets.eraseObject(bullet);
				bullet->removeFromParent();
			}
		}

		else if (enemyTank->getDir() == DIR_RIGHT)
		{
			bullet->runAction(MoveTo::create(5,
				Point(Director::getInstance()->getWinSize().width + 50, bullet->getPositionY())));
			if (bullet->getPositionX() > Director::getInstance()->getWinSize().width)
			{
				bullet->setLive(false);
				enemyBullets.eraseObject(bullet);
				bullet->removeFromParent();
			}
		}
	}
}
void GameWorld::enemyMove(float t)		//����̹���ƶ�,�ƻ�����
{
	for (int i= 0; i<enemyTanks.size();i++)
	{
		auto enemyTank = enemyTanks.at(i);
		int enemyLife = enemyTank->getLife();//�õ�ԭ̹�˵�����ֵ
		
		if (enemyTank->getPositionX() >= 50 && enemyTank->getPositionX() <= size.width-50
			&& enemyTank->getPositionY() >= 50 && enemyTank->getPositionY() <= size.height-50)
		{
			MoveDir dir = enemyTank->getDir();//�õ�ԭ̹�˵ķ���
			
			enemyTank->moveWithDir(dir);
			if (random() % 500 >497) //�ı��˶����������
			{
				auto x = enemyTank->getLocationX();
				auto y = enemyTank->getLocationY();
				enemyTank->removeFromParentAndCleanup(true);
				MoveDir dirs[] = { DIR_UP,DIR_DOWN, DIR_LEFT, DIR_RIGHT };
				MoveDir newDir = dirs[rand() % 4];
				//enemyTank->turnTo(newDir);
				Tank *enemyTank = Tank::create(dir, false);
				enemyTank->setLife(enemyLife);
				enemyTank->setTag(ENEMY_TANK);
				enemyTank->setGood(false);
				enemyTank->setDir(dir);
				enemyTank->setPosition(Point(x-10, y-10));
				enemyTank->setLocationX(x-10);
				enemyTank->setLocationY(y-10);
				enemyTank->setAnchorPoint(Point::ZERO);
				enemyTanks.replace(i, enemyTank);
				this->addChild(enemyTank);
				enemyTank->moveWithDir(dir);
			}
			
		}
		else
		{
			if (enemyTank->getDir() == DIR_UP)
			{
				auto x = enemyTank->getLocationX();
				auto y = enemyTank->getLocationY();
				enemyTank->removeFromParentAndCleanup(true);
				MoveDir dirs[] = { DIR_DOWN, DIR_LEFT, DIR_RIGHT };
				MoveDir dir = dirs[random() % 3];
				//enemyTank->turnTo(dir);
				Tank *enemyTank = Tank::create(dir, false);
				enemyTank->setLife(enemyLife);
				enemyTank->setTag(ENEMY_TANK);
				enemyTank->setGood(false);
				enemyTank->setDir(dir);
				enemyTank->setPosition(Point(x, y-10));
				enemyTank->setLocationX(x);
				enemyTank->setLocationY(y-10);
				//enemyTank->setAnchorPoint(Point::ZERO);
				enemyTanks.replace(i, enemyTank);
				this->addChild(enemyTank);
				enemyTank->moveWithDir(dir);
			}
			else if (enemyTank->getDir() == DIR_DOWN)
			{
				auto x = enemyTank->getLocationX();
				auto y = enemyTank->getLocationY();
				enemyTank->removeFromParentAndCleanup(true);
				MoveDir dirs[] = { DIR_UP, DIR_LEFT, DIR_RIGHT };
				MoveDir dir = dirs[random() % 3];
				//enemyTank->turnTo(dir);
				Tank *enemyTank = Tank::create(dir, false);
				enemyTank->setLife(enemyLife);
				enemyTank->setTag(ENEMY_TANK);
				enemyTank->setGood(false);
				
				enemyTank->setDir(dir);
				enemyTank->setPosition(Point(x, y+10));
				enemyTank->setLocationX(x);
				enemyTank->setLocationY(y+10);
				//enemyTank->setAnchorPoint(Point::ZERO);
				enemyTanks.replace(i, enemyTank);
				this->addChild(enemyTank);
				enemyTank->moveWithDir(dir);
			}
			else if (enemyTank->getDir() == DIR_LEFT)
			{
				auto x = enemyTank->getLocationX();
				auto y = enemyTank->getLocationY();
				enemyTank->removeFromParentAndCleanup(true);
				MoveDir dirs[] = { DIR_UP, DIR_DOWN, DIR_RIGHT };
				MoveDir dir = dirs[random() % 3];
				//enemyTank->turnTo(dir);
				Tank *enemyTank = Tank::create(dir, false);
				enemyTank->setLife(enemyLife);
				enemyTank->setTag(ENEMY_TANK);
				enemyTank->setGood(false);
				enemyTank->setDir(dir);
				enemyTank->setPosition(Point(x+10, y));
				enemyTank->setLocationX(x+10);
				enemyTank->setLocationY(y);
			//	enemyTank->setAnchorPoint(Point::ZERO);
				enemyTanks.replace(i, enemyTank);
				this->addChild(enemyTank);
				enemyTank->moveWithDir(dir);
			}
			else if (enemyTank->getDir() == DIR_RIGHT)
			{
				auto x = enemyTank->getLocationX();
				auto y = enemyTank->getLocationY();
				enemyTank->removeFromParentAndCleanup(true);
				MoveDir dirs[] = { DIR_UP, DIR_LEFT, DIR_DOWN };
				MoveDir dir = dirs[random() % 3];
				//enemyTank->turnTo(dir);
				Tank *enemyTank = Tank::create(dir, false);
				enemyTank->setLife(enemyLife);
				enemyTank->setTag(ENEMY_TANK);
				enemyTank->setGood(false);
				enemyTank->setDir(dir);
				enemyTank->setPosition(Point(x-10, y));
				enemyTank->setLocationX(x-10);
				enemyTank->setLocationY(y);
				//enemyTank->setAnchorPoint(Point::ZERO);
				enemyTanks.replace(i, enemyTank);
				this->addChild(enemyTank);
				enemyTank->moveWithDir(dir);
			}
		}
		//enemyTank->touchEachother(enemyTanks);
	}
}
void GameWorld::checkTouch()	//��ײ���
{
	auto myTank = (Tank*)this->getChildByTag(MY_TANK);
	
	for (int i = 0; i < myTank->bullets.size(); i++)
	{
		auto nowBbullet = myTank->bullets.at(i);
		for (int j = 0; j < enemyTanks.size(); j++)
		{
			auto nowEnemy = enemyTanks.at(j);
			if (nowBbullet->getRect().intersectsRect(nowEnemy->getRect()))
			{
				nowEnemy->setLife(nowEnemy->getLife() - 10);
				if (nowEnemy->getLife() <= 0)
				{
					if (rand() % 100 >70)//������ɽ�Ʒ
					{
						float rewardX = rand() % 900 + 20;
						float rewardY = rand() % 600 + 20;
						RewardType rewardType[] = { BULLET_TYPE_C,	//c�����ӵ�
							BULLET_TYPE_H,	//H�����ӵ�
							BULLET_TYPE_SUPER,//�����ӵ�
							REDBOX			//�ָ�����ֵ
						};
						RewardType type = rewardType[rand() % 4];
						Reward *reward = Reward::create(type);
						reward->setType(type);
						reward->setPosition(Point(rewardX, rewardY));
						rewards.pushBack(reward);
						this->addChild(reward);
					}
					//��ӱ�ըЧ��
					Explode *explode = new Explode();
					explode->newExplode(this, nowBbullet->getPosition().x, nowBbullet->getPosition().y);

					nowBbullet->removeFromParent();//�Ƴ��ӵ�ͼƬ
					myTank->bullets.eraseObject(nowBbullet);//�������Ƴ��ӵ�
					nowEnemy->removeFromParent();//�Ƴ�����̹��ͼƬ
					enemyTanks.eraseObject(nowEnemy);//�������Ƴ�����̹��
					i--;
					//���ű�ը��Ч
					SimpleAudioEngine::getInstance()->playEffect("explode.mp3");
					//��ӷ���
					score += 100;
					LabelTTF *label = (LabelTTF*)this->getChildByTag(110);
					label->setString(String::createWithFormat("%d", score)->_string);
					if (enemyNums < 15)
					{
						newEnemy();//����һ����̹��
						enemyNums++;
					}
					else if (enemyTanks.size() == 0)
					{
						//��Ϸʤ��
						gameOver(true);
					}
					
				}
				else
				{
					nowBbullet->removeFromParent();//�Ƴ��ӵ�ͼƬ
					myTank->bullets.eraseObject(nowBbullet);//�������Ƴ��ӵ�
				}
				break;
			}
		}
	}
}
void GameWorld::touchEnemy()//�ҷ�̹����������̹��
{
	auto myTank = (Tank*)this->getChildByTag(MY_TANK);
	for (int i = 0; i < enemyTanks.size(); i++)
	{
		auto nowEnemy = enemyTanks.at(i);
		if (myTank->getRect().intersectsRect(nowEnemy->getRect()))//�ҷ�̹����������̹��
		{
			//��ӱ�ըЧ��
			Explode *explode = new Explode();
			explode->newExplode(this, myTank->getPosition().x, myTank->getPosition().y);
			myTank->setLive(false);
			myTank->removeFromParent();//�Ƴ�����̹��ͼƬ
			this->unscheduleUpdate();//��ֹ�ƻ�����
			listenerKeyboard->setEnabled(false);//��ֹ������Ӧ
			i--;
			//���ű�ը��Ч
			SimpleAudioEngine::getInstance()->playEffect("explode.mp3");
			//LabelTTF *label2 = (LabelTTF*)this->getChildByTag(100);
			//label2->setString(String::createWithFormat("life:%d", 0)->_string);
			gameOver(false);
			break;
		}
	}
}
void GameWorld::touchMyTank()//�ҷ�̹�˱�ը
{
	auto myTank = (Tank*)this->getChildByTag(MY_TANK);
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		auto bullet = enemyBullets.at(i);
		if (Tank::live)
		{
			if (bullet->getRect().intersectsRect(myTank->getRect()))
			{
				float progress = bloodBar->getCurrentProgress() - 10.0f;
				bloodBar->setCurrentProgress(progress);
				Tank::myLife -= 10;
				bullet->removeFromParent();//�Ƴ��ӵ�ͼƬ
				enemyBullets.eraseObject(bullet);
				//����ֵ��ʾ����
				//LabelTTF *label2 = (LabelTTF*)this->getChildByTag(100);
				//label2->setString(String::createWithFormat("life:%d", Tank::myLife)->_string);
				if (Tank::myLife <= 0)
					Tank::live = false;
			}
		}
		else    //�ҷ�ʧ�ܣ���Ϸ����
		{
			//��ӱ�ըЧ��
			Explode *explode = new Explode();
			explode->newExplode(this, bullet->getPosition().x, bullet->getPosition().y);
			bullet->removeFromParent();//�Ƴ��ӵ�ͼƬ
			enemyBullets.eraseObject(bullet);
			//myTank->setLive(false);
			Tank::live = false;
			myTank->removeFromParent();//�Ƴ�̹��ͼƬ
			this->unscheduleUpdate();//��ֹ�ƻ�����		
			listenerKeyboard->setEnabled(false);//��ֹ������Ӧ
			i--;
			//���ű�ը��Ч
			SimpleAudioEngine::getInstance()->playEffect("explode.mp3");
			gameOver(false);
			break;
		}
	}
}
void GameWorld::gameOver(bool win)//��Ϸ����
{
	
	//��ת��GAMEOVER����
	this->pauseSchedulerAndActions();//ֹͣ�ƻ�����
	Sprite *overScene;
	if (!win)
	{
		overScene = Sprite::create("lose.png");
		SimpleAudioEngine::getInstance()->playBackgroundMusic("lose.mp3", true);
	}
	else
	{
		overScene = Sprite::create("win.png");
		SimpleAudioEngine::getInstance()->playBackgroundMusic("win.mp3", true);
	}
	overScene->setPosition(Point(size.width / 2-100, size.height / 2));
	overScene->setAnchorPoint(Point::ZERO);
	this->addChild(overScene);
	auto act = Sequence::create(
		DelayTime::create(5),	//��ʱ5��
		CallFunc::create(this, callfunc_selector(GameWorld::jumpToMainMenu)),//��ת�����˵�
		NULL
		);
	this->runAction(act);//ִ�ж���
}
void GameWorld::jumpToMainMenu()
{
	Scene* scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}
void GameWorld::touchBarrier1()//��ײ���(�����ӵ����ϰ���),��update�У���ϵͳʱ�Ӹ���ִ��
{
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		auto nowBullet = enemyBullets.at(i);
		for (int j = 0; j < barriers.size(); j++)
		{
			auto nowBarrier = barriers.at(j);
			if (nowBullet->getRect().intersectsRect(nowBarrier->getRect()))
			{
				if (nowBarrier->getType() != BARRIER_STEER_1 && nowBarrier->getType() != BARRIER_ROOM)
				{
					nowBullet->removeFromParent();//�Ƴ��ӵ�ͼƬ
					enemyBullets.eraseObject(nowBullet);//�������Ƴ��ӵ�
					i--;
					nowBarrier->removeFromParent();//�Ƴ��ϰ���ͼƬ
					barriers.eraseObject(nowBarrier);//�������Ƴ��ϰ���
					j--;
					break;
				}
				
				else if (nowBarrier->getType() == BARRIER_ROOM)//�������ģ��ҷ�ʧ��
				{
					nowBullet->removeFromParent();//�Ƴ��ӵ�ͼƬ
					enemyBullets.eraseObject(nowBullet);//�������Ƴ��ӵ�
					i--;
					nowBarrier->removeFromParent();//�Ƴ��ϰ���ͼƬ
					barriers.eraseObject(nowBarrier);//�������Ƴ��ϰ���
					auto room = Sprite::create("mark.png");
					room->setPosition(450, 40);
					this->addChild(room);
					gameOver(false);
					j--;
					break;
				}
				else
				{
					nowBullet->removeFromParent();//�Ƴ��ӵ�ͼƬ
					enemyBullets.eraseObject(nowBullet);//�������Ƴ��ӵ�
					i--;
					break;
				}
			}
		}
	}
}
void GameWorld::touchBarrier2()//��ײ���(�ҷ��ӵ����ϰ���),��update�У���ϵͳʱ�Ӹ���ִ��
{
	auto tank = (Tank*)this->getChildByTag(MY_TANK);
	for (int i = 0; i < tank->bullets.size(); i++)
	{
		auto nowBullet = tank->bullets.at(i);
		for (int j = 0; j < barriers.size(); j++)
		{
			auto nowBarrier = barriers.at(j);
			if (nowBullet->getRect().intersectsRect(nowBarrier->getRect()))
			{
				if (isRanked_C)	//C��
				{
					if (nowBarrier->getType() != BARRIER_STEER_1 && nowBarrier->getType() != BARRIER_ROOM)//C����͸�ְ��ϰ���
					{
						nowBullet->removeFromParent();//�Ƴ��ӵ�ͼƬ
						tank->bullets.eraseObject(nowBullet);//�������Ƴ��ӵ�
						i--;
						nowBarrier->removeFromParent();//�Ƴ��ϰ���ͼƬ
						barriers.eraseObject(nowBarrier);//�������Ƴ��ϰ���
						j--;
						break;
					}
					else
					{
						nowBullet->removeFromParent();//�Ƴ��ӵ�ͼƬ
						tank->bullets.eraseObject(nowBullet);//�������Ƴ��ӵ�
						i--;
						break;
					}
				}
				else if (isRanked_H) //H��
				{
					if (nowBarrier->getType() != BARRIER_ROOM)
					{
						nowBullet->removeFromParent();//�Ƴ��ӵ�ͼƬ
						tank->bullets.eraseObject(nowBullet);//�������Ƴ��ӵ�
						i--;
						nowBarrier->removeFromParent();//�Ƴ��ϰ���ͼƬ
						barriers.eraseObject(nowBarrier);//�������Ƴ��ϰ���
						j--;
						break;
					}
					else   //�ҷ�H�����Ի������ģ���ɱ����Ϸ����
					{
						nowBullet->removeFromParent();//�Ƴ��ӵ�ͼƬ
						enemyBullets.eraseObject(nowBullet);//�������Ƴ��ӵ�
						i--;
						nowBarrier->removeFromParent();//�Ƴ��ϰ���ͼƬ
						barriers.eraseObject(nowBarrier);//�������Ƴ��ϰ���
						auto room = Sprite::create("mark.png");
						room->setPosition(450, 40);
						this->addChild(room);
						gameOver(false);
						j--;
						break;
					}
				}
				else//�����ӵ�������ϰ���Լ�������
				{
					nowBarrier->removeFromParent();//�Ƴ��ϰ���ͼƬ
					barriers.eraseObject(nowBarrier);//�������Ƴ��ϰ���
					j--;
					break;
				}
			}
		}
	}
}
void GameWorld::getToBarrier1()//��ײ��⣨����̹���Ƿ������ϰ����update�У���ϵͳʱ�Ӹ���ִ��
{
	for (int i = 0; i < enemyTanks.size(); i++)
	{
		auto enemyTank = enemyTanks.at(i);
		for (int j = 0; j < barriers.size(); j++)
		{
			auto nowBarrier = barriers.at(j);
			if (enemyTank->getRect().intersectsRect(nowBarrier->getRect()))
			{
				auto x = enemyTank->getLocationX();
				auto y = enemyTank->getLocationY();
				enemyTank->removeFromParentAndCleanup(true);
			//	MoveDir dirs[] = { DIR_UP,DIR_DOWN, DIR_LEFT, DIR_RIGHT };
				MoveDir dir = enemyTank->getDir();
				Tank *enemyTank = nullptr;
				if ( dir== DIR_UP)
				{
					dir = DIR_DOWN;
					enemyTank = Tank::create(dir, false);
					enemyTank->setPosition(Point(x, y - 10));
					enemyTank->setLocationX(x);
					enemyTank->setLocationY(y - 10);
				}
				else if (dir == DIR_DOWN)
				{
					dir = DIR_UP;
					enemyTank = Tank::create(dir, false);
					enemyTank->setPosition(Point(x, y + 10));
					enemyTank->setLocationX(x);
					enemyTank->setLocationY(y + 10);
				}
				else if (dir == DIR_LEFT)
				{
				    dir = DIR_RIGHT;
					enemyTank = Tank::create(dir, false);
					enemyTank->setPosition(Point(x + 10, y+10));
					enemyTank->setLocationX(x + 10);
					enemyTank->setLocationY(y+10);
				}
				else if (dir == DIR_RIGHT)
				{
					dir = DIR_LEFT;
					enemyTank = Tank::create(dir, false);
					enemyTank->setPosition(Point(x - 10, y+10));
					enemyTank->setLocationX(x - 10);
					enemyTank->setLocationY(y+10);
				}
				enemyTank->setDir(dir);
				enemyTank->setTag(ENEMY_TANK);
				enemyTank->setGood(false);
				//enemyTank->setAnchorPoint(Point::ZERO);
				enemyTanks.replace(i, enemyTank);
				this->addChild(enemyTank);
				break;
			}
		}
	}
}
void GameWorld::getToBarrier2()//��ײ��⣨�ҷ�̹���Ƿ������ϰ����update�У���ϵͳʱ�Ӹ���ִ��
{
	auto myTank = (Tank*)this->getChildByTag(MY_TANK);
	auto x = myTank->getPositionX();
	auto y = myTank->getPositionY();
	for (int j = 0; j < barriers.size(); j++)
	{
		auto nowBarrier = barriers.at(j);
		if (myTank->getRect().intersectsRect(nowBarrier->getRect()))
		{
			if (myTank->getDir() == DIR_UP)
				myTank->setPosition(x, y - 10);
			else if (myTank->getDir() == DIR_DOWN)
				myTank->setPosition(x, y + 10);
			else if (myTank->getDir() == DIR_LEFT)
				myTank->setPosition(x+10, y);
			else if (myTank->getDir() == DIR_RIGHT)
				myTank->setPosition(x-10, y);
		}
	}
}
void GameWorld::touchReward()//��ײ��⣨�ҷ�̹���Ƿ�������Ʒ����update�У���ϵͳʱ�Ӹ���ִ��
{
	auto myTank = (Tank*)this->getChildByTag(MY_TANK);
	for (int i = 0; i < rewards.size(); i++)
	{
		auto nowReward = rewards.at(i);
		if (nowReward->getRect().intersectsRect(myTank->getRect()))
		{
			switch (nowReward->getType())
			{
			case BULLET_TYPE_C:
				isRanked_C = true;
				isRanked_H = false;
				break;
			case BULLET_TYPE_H:
				isRanked_C = false;
				isRanked_H = true;
				break;
			case BULLET_TYPE_SUPER:
				isSuperBullet = true;
				break;
			case REDBOX:
				Tank::myLife = 100;//�ָ��ҷ�����ֵ
				//LabelTTF *label2 = (LabelTTF*)this->getChildByTag(100);
				//label2->setString(String::createWithFormat("life:%d", Tank::myLife)->_string);
				//bloodBar->setTotalProgress(100.0f);
				bloodBar->setCurrentProgress(100.0f);
				break;		
			//default:
				//break;
			}
			nowReward->removeFromParent();
			rewards.eraseObject(nowReward);
			//������Ч
			SimpleAudioEngine::getInstance()->playEffect("eatprops.wav");
		}
	}
}
void GameWorld::update(float t)	//��ϵͳʱ�Ӹ���ִ��
{
	auto myTank = (Tank*)this->getChildByTag(MY_TANK);
	checkTouch();
	touchBarrier1();
	touchBarrier2();
	getToBarrier1();
	getToBarrier2();
	touchReward();
	if (myTank->isLive())
		touchEnemy();
	if (myTank->isLive())
		touchMyTank();
}
