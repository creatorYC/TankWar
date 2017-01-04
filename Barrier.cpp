#include "Barrier.h"

bool Barrier::init(BarrierType bType)
{
	if (!Sprite::init())
		return false;
	Sprite *sprite;
	switch (bType)
	{
	case BARRIER_TILE://瓦片类型
		sprite = Sprite::create("barrier.png");
		break;
	case BARRIER_TREE://树叶类型
		sprite = Sprite::create("tree.png");
		break;
	case BARRIER_STEER_1://钢板1类型
		sprite = Sprite::create("barrier2.png");
		break;
	case BARRIER_ROOM://窝心
		sprite = Sprite::create("room.png");
		break;
	default:
		break;
	}
	this->addChild(sprite);
	return true;
}
Barrier* Barrier::create(BarrierType bType)
{
	Barrier *pRet = new Barrier();
	if (pRet && pRet->init(bType))
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
void Barrier::setType(BarrierType Btype)//设置障碍物类型
{
	this->BType = Btype;
}
BarrierType Barrier::getType()//得到障碍物类型
{
	return BType;
}
void Barrier::setGood(bool bgood)
{
	good = bgood;
}
bool Barrier::getGood()
{
	return good;
}
void Barrier::setLocation(float x, float y)
{
	locX = x;
	locY = y;
}
float Barrier::getLocX()
{
	return locX;
}
float Barrier::getLocY()
{
	return locY;
}
Rect Barrier::getRect()//用于碰撞检测
{
	return Rect(this->getPositionX()-15, this->getPositionY()-16,
		30, 32);
}