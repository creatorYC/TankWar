#include "Bullet.h"
#include "GameWorld.h"
bool Bullet::init(BMoveDir dir,bool good)
{
	if (!Sprite::init())
		return false;
	Sprite* bullet;
	if (good)	//我方子弹
	{
		switch (dir)
		{
		case B_DIR_UP:
			if (GameWorld::isRanked_C && !GameWorld::isSuperShoot)
				bullet = Sprite::create("b11.png");
			else if (GameWorld::isRanked_H && !GameWorld::isSuperShoot)
				bullet = Sprite::create("b21.png");
			else if (GameWorld::isSuperBullet)
				bullet = Sprite::create("p21.png");
			dir = B_DIR_UP;
			break;
		case B_DIR_DOWN:
			if (GameWorld::isRanked_C && !GameWorld::isSuperShoot)
				bullet = Sprite::create("b12.png");
			else if (GameWorld::isRanked_H && !GameWorld::isSuperShoot)
				bullet = Sprite::create("b22.png");
			else if (GameWorld::isSuperBullet)
				bullet = Sprite::create("p22.png");
			dir = B_DIR_DOWN;
			break;
		case B_DIR_LEFT:
			if (GameWorld::isRanked_C && !GameWorld::isSuperShoot)
				bullet = Sprite::create("b13.png");
			else if (GameWorld::isRanked_H && !GameWorld::isSuperShoot)
				bullet = Sprite::create("b23.png");
			else if (GameWorld::isSuperBullet)
				bullet = Sprite::create("p23.png");
			dir = B_DIR_LEFT;
			break;
		case B_DIR_RIGHT:
			if (GameWorld::isRanked_C && !GameWorld::isSuperShoot)
				bullet = Sprite::create("b14.png");
			else if (GameWorld::isRanked_H && !GameWorld::isSuperShoot)
				bullet = Sprite::create("b24.png");
			else if (GameWorld::isSuperBullet)
				bullet = Sprite::create("p24.png");
			dir = B_DIR_RIGHT;
			break;
		default:
			break;
		}
	}
	else      //敌人子弹
	{
		if (dir == B_DIR_UP || dir == B_DIR_DOWN || dir == B_DIR_LEFT || dir == B_DIR_RIGHT)
			bullet = Sprite::create("b3.png");
	}
	this->addChild(bullet);
	return true;
}
Bullet* Bullet::create(BMoveDir dir,bool good)
{
	Bullet *pRet = new Bullet();
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
void Bullet::setLive(bool live)
{
	this->live = live;
}
bool Bullet::isLive()
{
	return this->live;
}
void Bullet::setDir(BMoveDir dir)
{
	this->dir = dir;
}
BMoveDir Bullet::getDir()
{
	return this->dir;
}
void Bullet::setLocationX(double x)
{
	this->tankX = x;
}
void Bullet::setLocationY(double y)
{
	this->tankY = y;
}
float Bullet::getLocationX()
{
	return this->tankX;
}
float Bullet::getLocationY()
{
	return this->tankY;
}
Rect Bullet::getRect() //获取子弹所在图片的矩形框
{
	return Rect(this->getPositionX()-8, this->getPositionY()-32,
		17,64);
}