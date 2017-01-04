#ifndef __Tank__H__
#define __Tank__H__
#include "cocos2d.h"
USING_NS_CC;
enum MoveDir//移动方向
{
	DIR_UP,	
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_STOP1,
	DIR_STOP2
};
class Bullet;
class GameWorld;
class Tank : public Sprite
{
public:
	virtual bool init(MoveDir dir,bool good);
	static Tank* create(MoveDir dir,bool good);
	void turnTo(MoveDir newDir); //坦克转换方向
	void setDir(MoveDir dir);
	MoveDir getDir();
	void setLocationX(double x);
	void setLocationY(double y);
	float getLocationX();
	float getLocationY();
	void setLive(bool live);
	bool isLive();
	void setGood(bool good);
	bool isGood();
	void setLife(int life);
	int getLife();
	void shoot(MoveDir dir);//根据传入的方向发射子弹
	void createTank(MoveDir dir);//创建我方坦克
	void createEnemyTank(MoveDir dir);//创建敌人坦克
	void moveWithDir(MoveDir dir);//敌人坦克移动
	//bool touchEachother(Vector<Tank*> enemyTanks);//处理敌人坦克相互穿越问题
	Rect getRect();//获取坦克图片矩形框
	Vector<Bullet*> bullets;//子弹容器
	static bool live;//判断坦克是否活着
	static int myLife;//记录坦克生命值
private:
	double locationX, locationY;
	double tankX, tankY;
	double preX, preY;//记录坦克之前的位置
	int life;//敌人坦克生命值
	MoveDir dir;//坦克方向
	bool good;//判断是我方坦克，还是敌人坦克
};

#endif