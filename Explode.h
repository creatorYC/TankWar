#ifndef __EXPLODE__H__
#define __EXPLODE__H__
#include "cocos2d.h"

USING_NS_CC;
class Explode : public Sprite
{
public:
	Explode() {}
	~Explode(){}
	void newExplode(Node *node,float x, float y);//产生一个爆炸
	void removeExplode(Node *node);//移除爆炸
};
#endif