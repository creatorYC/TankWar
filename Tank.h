#ifndef __Tank__H__
#define __Tank__H__
#include "cocos2d.h"
USING_NS_CC;
enum MoveDir//�ƶ�����
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
	void turnTo(MoveDir newDir); //̹��ת������
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
	void shoot(MoveDir dir);//���ݴ���ķ������ӵ�
	void createTank(MoveDir dir);//�����ҷ�̹��
	void createEnemyTank(MoveDir dir);//��������̹��
	void moveWithDir(MoveDir dir);//����̹���ƶ�
	//bool touchEachother(Vector<Tank*> enemyTanks);//�������̹���໥��Խ����
	Rect getRect();//��ȡ̹��ͼƬ���ο�
	Vector<Bullet*> bullets;//�ӵ�����
	static bool live;//�ж�̹���Ƿ����
	static int myLife;//��¼̹������ֵ
private:
	double locationX, locationY;
	double tankX, tankY;
	double preX, preY;//��¼̹��֮ǰ��λ��
	int life;//����̹������ֵ
	MoveDir dir;//̹�˷���
	bool good;//�ж����ҷ�̹�ˣ����ǵ���̹��
};

#endif