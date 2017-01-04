#ifndef __BULLET__H__
#define __BULLET__H__

#include "cocos2d.h"
USING_NS_CC;
enum BMoveDir
{
	B_DIR_UP,
	B_DIR_DOWN,
	B_DIR_LEFT,
	B_DIR_RIGHT,
	B_DIR_STOP
};
class Bullet : public Sprite
{
public:
	virtual bool init(BMoveDir dir,bool good);
	static Bullet* create(BMoveDir dir,bool good);
	void setDir(BMoveDir dir);
	BMoveDir getDir();
	void setLocationX(double x);
	void setLocationY(double y);
	float getLocationX();
	float getLocationY();
	void setLive(bool live);
	bool isLive();
	Rect getRect();//��ȡ�ӵ�ͼƬ���ο�
private:
	double locationX, locationY;
	double tankX, tankY;
	bool live;//�ӵ�����
	BMoveDir dir;//�ӵ�����
};

#endif