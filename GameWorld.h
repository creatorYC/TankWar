#ifndef __GAME__WORLD__
#define __GAME__WORLD__
#include "cocos2d.h"
#include "Tank.h"
#include "Bullet.h"
#include "Reward.h"
#include "Barrier.h"
USING_NS_CC;
enum TankType//标记是我方坦克还是敌人坦克
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
	void menuCallBack(Ref* obj);//菜单回调函数
	//键盘响应
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void buildMap();//创建地图
	void newEnemy();//产生敌人坦克
	void update(float t);
	void checkTouch();//碰撞检测(我方子弹是否击中敌人)，在update中，随系统时钟更新执行
	void touchMyTank();//碰撞检测(敌人子弹是否击中我方)，在update中，随系统时钟更新执行
	void touchEnemy();//碰撞检测，(我方坦克碰到敌人坦克)，在update中，随系统时钟更新执行
	void touchBarrier1();//碰撞检测(敌人子弹打到障碍物),在update中，随系统时钟更新执行
	void touchBarrier2();//碰撞检测（我方子弹打到障碍物）在update中，随系统时钟更新执行
	void getToBarrier1();//碰撞检测（敌人坦克是否碰到障碍物）在update中，随系统时钟更新执行
	void getToBarrier2();//碰撞检测（我方坦克是否碰到障碍物）在update中，随系统时钟更新执行
	void touchReward();//碰撞检测（我方坦克是否碰到奖品）在update中，随系统时钟更新执行
	void enemyMove(float t);//敌人坦克的移动，为计划任务
	void enemyFire(float t);//敌人坦克开火，为计划任务
	void jumpToMainMenu();//跳转至主菜单
	void gameOver(bool win);//游戏结束
	Vector<Tank*>enemyTanks;//敌人坦克容器
	static bool isRanked_C;//子弹是否升级到C
	static bool isRanked_H;//子弹是否升级到H
	static bool isSuperBullet;//是否是超级子弹
	static bool isSuperShoot;//超级弹是否发射
private:
	Size size;
	Vector<Bullet*>enemyBullets;//敌人子弹容器
	Vector<Barrier*>barriers;//障碍物容器
	Vector<Reward*>rewards;//奖品容器
	EventListenerKeyboard* listenerKeyboard;
	int score;
	int enemyNums;//敌人坦克数
	BloodBar *bloodBar;
};
#endif