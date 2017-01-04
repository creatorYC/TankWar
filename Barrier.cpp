#include "Barrier.h"

bool Barrier::init(BarrierType bType)
{
	if (!Sprite::init())
		return false;
	Sprite *sprite;
	switch (bType)
	{
	case BARRIER_TILE://��Ƭ����
		sprite = Sprite::create("barrier.png");
		break;
	case BARRIER_TREE://��Ҷ����
		sprite = Sprite::create("tree.png");
		break;
	case BARRIER_STEER_1://�ְ�1����
		sprite = Sprite::create("barrier2.png");
		break;
	case BARRIER_ROOM://����
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
void Barrier::setType(BarrierType Btype)//�����ϰ�������
{
	this->BType = Btype;
}
BarrierType Barrier::getType()//�õ��ϰ�������
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
Rect Barrier::getRect()//������ײ���
{
	return Rect(this->getPositionX()-15, this->getPositionY()-16,
		30, 32);
}