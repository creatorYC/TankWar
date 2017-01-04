#include "Reward.h"
bool Reward::init(RewardType RType)
{
	if (!Sprite::init())
		return false;
	Sprite *sprite;
	switch (RType)
	{
	case BULLET_TYPE_C://C�����ӵ�
		sprite = Sprite::create("propsC.png");
		break;
	case BULLET_TYPE_H://H�����ӵ���
		sprite = Sprite::create("propsH.png");
		break;
	case REDBOX://�ָ�����ֵ
		sprite = Sprite::create("redbox.png");
		break;
	case BULLET_TYPE_SUPER://�����ӵ�
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
void Reward::setType(RewardType Rtype)//���ý�Ʒ����
{
	this->RType = Rtype;
}
RewardType Reward::getType()//�õ���Ʒ����
{
	return RType;
}
Rect Reward::getRect()//������ײ���
{
	return Rect(this->getPositionX() - 15, this->getPositionY() - 16,
		40, 33);
}