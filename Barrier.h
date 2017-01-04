#ifndef __BARRIER__H__
#define __BARRIER__H__

#include "cocos2d.h"
USING_NS_CC;
enum BarrierType	//障碍物类型
{
	BARRIER_TILE,//瓦片类型
	BARRIER_TREE,//树叶类型
	BARRIER_STEER_1, //钢板1类型
	BARRIER_ROOM //窝心
};
//障碍物类
class Barrier : public Sprite
{
public:
	virtual bool init(BarrierType bType);//复写的初始化方法,根据类型初始化障碍物
	static Barrier* create(BarrierType bType);

	void setLocation(float x, float y);
	void setGood(bool good);
	bool getGood();
	float getLocX();
	float getLocY();
	void setType(BarrierType Btype);//设置奖品类型
	BarrierType getType();//得到奖品类型
	Rect getRect();
private:
	float locX, locY;//障碍物的坐标
	bool good;//判断是我方老窝还是一般障碍物 true:我方老窝
	BarrierType BType;
};
#endif