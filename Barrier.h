#ifndef __BARRIER__H__
#define __BARRIER__H__

#include "cocos2d.h"
USING_NS_CC;
enum BarrierType	//�ϰ�������
{
	BARRIER_TILE,//��Ƭ����
	BARRIER_TREE,//��Ҷ����
	BARRIER_STEER_1, //�ְ�1����
	BARRIER_ROOM //����
};
//�ϰ�����
class Barrier : public Sprite
{
public:
	virtual bool init(BarrierType bType);//��д�ĳ�ʼ������,�������ͳ�ʼ���ϰ���
	static Barrier* create(BarrierType bType);

	void setLocation(float x, float y);
	void setGood(bool good);
	bool getGood();
	float getLocX();
	float getLocY();
	void setType(BarrierType Btype);//���ý�Ʒ����
	BarrierType getType();//�õ���Ʒ����
	Rect getRect();
private:
	float locX, locY;//�ϰ��������
	bool good;//�ж����ҷ����ѻ���һ���ϰ��� true:�ҷ�����
	BarrierType BType;
};
#endif