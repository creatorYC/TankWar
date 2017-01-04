#include "Reward.h"
bool Reward::init(RewardType RType)
{
	if (!Sprite::init())
		return false;
	Sprite *sprite;
	switch (RType)
	{
	case BULLET_TYPE_C://C类型子弹
		sprite = Sprite::create("propsC.png");
		break;
	case BULLET_TYPE_H://H类型子弹·
		sprite = Sprite::create("propsH.png");
		break;
	case REDBOX://恢复生命值
		sprite = Sprite::create("redbox.png");
		break;
	case BULLET_TYPE_SUPER://超级子弹
		sprite = Sprite::create("propsP.png");
		break;
	default:
		break;
	}
	this->addChild(sprite);
	return true;
}
Reward* Reward::create(RewardType RType)
{
	Reward *pRet = new Reward();
	if (pRet && pRet->init(RType))
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
void Reward::setType(RewardType Rtype)//设置奖品类型
{
	this->RType = Rtype;
}
RewardType Reward::getType()//得到奖品类型
{
	return RType;
}
Rect Reward::getRect()//用于碰撞检测
{
	return Rect(this->getPositionX() - 15, this->getPositionY() - 16,
		40, 33);
}