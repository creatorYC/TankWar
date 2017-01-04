#ifndef __REWARD__H__
#define __REWARD__H__
#include "cocos2d.h"
USING_NS_CC;

//��Ʒ����
enum RewardType
{
	BULLET_TYPE_C,	//c�����ӵ�
	BULLET_TYPE_H,	//H�����ӵ�
	BULLET_TYPE_SUPER,//�����ӵ�
	REDBOX			//�ָ�����ֵ
};
//��Ʒ��
class Reward : public Sprite
{
public:
	virtual bool init(RewardType RType);//��д�ĳ�ʼ������,�������ͳ�ʼ���ϰ���
	static Reward* create(RewardType RType);
	void setType(RewardType Rtype);//���ý�Ʒ����
	RewardType getType();//�õ���Ʒ����
	Rect getRect();
private:
	RewardType RType;
};
#endif