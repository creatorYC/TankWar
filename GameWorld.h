#ifndef __GAME__WORLD__
#define __GAME__WORLD__
#include "cocos2d.h"
#include "Tank.h"
#include "Bullet.h"
#include "Reward.h"
#include "Barrier.h"
USING_NS_CC;
enum TankType//������ҷ�̹�˻��ǵ���̹��
{
	MY_TANK,
	ENEMY_TANK
};
class BloodBar;

class GameWorld : Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(GameWorld);
	virtual bool init();
	void menuCallBack(Ref* obj);//�˵��ص�����
	//������Ӧ
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void buildMap();//������ͼ
	void newEnemy();//��������̹��
	void update(float t);
	void checkTouch();//��ײ���(�ҷ��ӵ��Ƿ���е���)����update�У���ϵͳʱ�Ӹ���ִ��
	void touchMyTank();//��ײ���(�����ӵ��Ƿ�����ҷ�)����update�У���ϵͳʱ�Ӹ���ִ��
	void touchEnemy();//��ײ��⣬(�ҷ�̹����������̹��)����update�У���ϵͳʱ�Ӹ���ִ��
	void touchBarrier1();//��ײ���(�����ӵ����ϰ���),��update�У���ϵͳʱ�Ӹ���ִ��
	void touchBarrier2();//��ײ��⣨�ҷ��ӵ����ϰ����update�У���ϵͳʱ�Ӹ���ִ��
	void getToBarrier1();//��ײ��⣨����̹���Ƿ������ϰ����update�У���ϵͳʱ�Ӹ���ִ��
	void getToBarrier2();//��ײ��⣨�ҷ�̹���Ƿ������ϰ����update�У���ϵͳʱ�Ӹ���ִ��
	void touchReward();//��ײ��⣨�ҷ�̹���Ƿ�������Ʒ����update�У���ϵͳʱ�Ӹ���ִ��
	void enemyMove(float t);//����̹�˵��ƶ���Ϊ�ƻ�����
	void enemyFire(float t);//����̹�˿���Ϊ�ƻ�����
	void jumpToMainMenu();//��ת�����˵�
	void gameOver(bool win);//��Ϸ����
	Vector<Tank*>enemyTanks;//����̹������
	static bool isRanked_C;//�ӵ��Ƿ�������C
	static bool isRanked_H;//�ӵ��Ƿ�������H
	static bool isSuperBullet;//�Ƿ��ǳ����ӵ�
	static bool isSuperShoot;//�������Ƿ���
private:
	Size size;
	Vector<Bullet*>enemyBullets;//�����ӵ�����
	Vector<Barrier*>barriers;//�ϰ�������
	Vector<Reward*>rewards;//��Ʒ����
	EventListenerKeyboard* listenerKeyboard;
	int score;
	int enemyNums;//����̹����
	BloodBar *bloodBar;
};
#endif