#include "Tank.h"
#include "GameWorld.h"
#include "Bullet.h"
int Tank::myLife = 100;
bool Tank::live = true;
bool Tank::init(MoveDir dir,bool good)
{
	if (!Sprite::init())
		return false;
	if (good)
	{
		createTank(dir);
	}
	else
	{
		createEnemyTank(dir);
	}
	return true;
}
 Tank* Tank::create(MoveDir dir,bool good)
{
	Tank *pRet = new Tank();
	if (pRet && pRet->init(dir,good))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
 void Tank::createTank(MoveDir dir)
 {
	 Sprite *tank;
	 switch (dir)
	 {
	 case DIR_UP:
		 tank = Sprite::create("up.png");
		 this->setDir(DIR_UP);
		 break;
	 case DIR_DOWN:
		 tank = Sprite::create("down.png");
		 this->setDir(DIR_DOWN);
		 break;
	 case DIR_LEFT:
		 tank = Sprite::create("left.png");
		 this->setDir(DIR_LEFT);
		 break;
	 case DIR_RIGHT:
		 tank = Sprite::create("right.png");
		 this->setDir(DIR_RIGHT);
		 break;
	 default:
		 break;
	 }
	 //auto tank = Sprite::create("down.png");
	 this->addChild(tank);
 }
 void Tank::createEnemyTank(MoveDir dir)
 {
	 Sprite *enemyTank;
	 switch (dir)
	 {
	 case DIR_UP:
		 enemyTank = Sprite::create("p6.png");
		 this->setDir(DIR_UP);
		 break;
	 case DIR_DOWN:
		 enemyTank = Sprite::create("p61.png");
		 this->setDir(DIR_DOWN);
		 break;
	 case DIR_LEFT:
		 enemyTank = Sprite::create("p62.png");
		 this->setDir(DIR_LEFT);
		 break;
	 case DIR_RIGHT:
		 enemyTank = Sprite::create("p63.png");
		 this->setDir(DIR_RIGHT);
		 break;
	 default:
		 break;
	 }
	 this->addChild(enemyTank);
 }

 void Tank::turnTo(MoveDir newDir) //坦克转换方向
{
	 int degree = (newDir - dir) * 90; //待旋转的方向-当前的方向
	//以最小角度转向
	if (degree < 0)
	{
		degree = abs(degree) <= (360 + degree) ? degree : (360 + degree);
	}
	else
	{
		degree = degree <= (360 - degree) ? degree : -(360 - degree);
	}
	runAction(RotateBy::create(0.2f, degree));
	dir = newDir;
}
void Tank::setLive(bool live)
{
	this->live = live;
}
bool Tank::isLive()
{
	return this->live;
}
void Tank::setLife(int life)
{
	this->life = life;
}
int Tank::getLife()
{
	return this->life;
}
void Tank::setDir(MoveDir dir)
{
	this->dir = dir;
}
MoveDir Tank::getDir()
{
	return this->dir;
}
void Tank::setLocationX(double x)
{
	this->tankX = x;
}
void Tank::setLocationY(double y)
{
	this->tankY = y;
}
float Tank::getLocationX()
{
	return this->tankX;
}
float Tank::getLocationY()
{
	return this->tankY;
}
void Tank::setGood(bool good)
{
	this->good = good;
}
bool Tank::isGood()
{
	return this->good;
}
Rect Tank::getRect()	//获取坦克所在图片的矩形框
{
	return Rect(this->getPositionX()-40, this->getPositionY()-40, //this->getContentSize().width, this->getContentSize().height);
		80,80);
}
void Tank::shoot(MoveDir dir)	//发射子弹
{
	for (int i = 0; i < bullets.size();i++)
	{
		Bullet *bullet = bullets.at(i);
		if (dir == DIR_UP)
		{
			bullet->runAction(MoveTo::create(3, Point(bullet->getPositionX(),
				Director::getInstance()->getWinSize().height + 50)));
			if (bullet->getPositionY() >= Director::getInstance()->getWinSize().height)
			{
				bullet->removeFromParent();
				bullets.eraseObject(bullet);
			}
		}
		else if (dir == DIR_DOWN)
		{
			bullet->runAction(MoveTo::create(3, Point(bullet->getPositionX(), -50)));
			if (bullet->getPositionY() == -50)
			{
				bullet->removeFromParent();
				bullets.eraseObject(bullet);
			}
		}

		else if (dir == DIR_LEFT)
		{
			bullet->runAction(MoveTo::create(3, Point(-50, bullet->getPositionY())));
			if (bullet->getPositionX() < 0)
			{
				bullet->removeFromParent();
				bullets.eraseObject(bullet);
			}
		}

		else if (dir == DIR_RIGHT)
		{
			bullet->runAction(MoveTo::create(3,
				Point(Director::getInstance()->getWinSize().width + 50, bullet->getPositionY())));
			if (bullet->getPositionX() > Director::getInstance()->getWinSize().width)
			{
				bullet->removeFromParent();
				bullets.eraseObject(bullet);
			}
		}
	}
}
void Tank::moveWithDir(MoveDir dir)	//敌人坦克移动
{
	auto x = this->getLocationX();
	auto y = this->getLocationY();
	preX = x;
	preY = y;
	switch (dir)
	{
	case DIR_UP:
		
		if (y <= Director::getInstance()->getWinSize().height-50)
		{
			this->setPosition(Point(x, y + 10));
			this->setDir(DIR_UP);
		}
		break;
	case DIR_DOWN:
		if (y >= 50)
		{
			this->setPosition(Point(x, y - 10));
			this->setDir(DIR_DOWN);
		}		
		break;
	case DIR_LEFT:
		if (x >= 50)
		{
			this->setPosition(Point(x - 10, y));
			this->setDir(DIR_LEFT);
		}
		break;
	case DIR_RIGHT:
		if (x <= Director::getInstance()->getWinSize().width-50)
		{
			this->setPosition(Point(x + 10, y));
			this->setDir(DIR_RIGHT);
		}
		break;
	default:
		break;	
	}
	this->setLocationX(this->getPosition().x);
	this->setLocationY(this->getPosition().y);
}
/*bool Tank::touchEachother(Vector<Tank*> enemyTanks)//处理敌人坦克相互穿越问题
{
	for (int i = 0; i < enemyTanks.size(); i++)
	{
		auto enemyTank = enemyTanks.at(i);
		if (this != enemyTank)
		{
			if (this->getRect().intersectsRect(enemyTank->getRect()))
			{
				MoveDir dirs[] = { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };
				MoveDir newDir = dirs[random() % 4];
				//enemyTank->turnTo(newDir);
				Tank *enemyTank = Tank::create(newDir, false);
				enemyTank->setLive(true);
				enemyTank->setLife(50);
				enemyTank->setTag(ENEMY_TANK);
				enemyTank->setGood(false);
				enemyTank->setDir(newDir);
				enemyTank->moveWithDir(newDir);
				return true;
			}
		}
	}
	return false;
}*/
