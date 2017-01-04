#ifndef __REWARD__H__
#define __REWARD__H__
#include "cocos2d.h"
USING_NS_CC;

//奖品类型
enum RewardType
{
	BULLET_TYPE_C,	//c类型子弹
	BULLET_TYPE_H,	//H类型子弹
	BULLET_TYPE_SUPER,//超级子弹
	REDBOX			//恢复生命值
};
//奖品类
class Reward : public Sprite
{
public:
	virtual bool init(RewardType RType);//复写的初始化方法,根据类型初始化障碍物
	static Reward* create(RewardType RType);
	void setType(RewardType Rtype);//设置奖品类型
	RewardType getType();//得到奖品类型
	Rect getRect();
private:
	RewardType RType;
};
#endif