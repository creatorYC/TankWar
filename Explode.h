#ifndef __EXPLODE__H__
#define __EXPLODE__H__
#include "cocos2d.h"

USING_NS_CC;
class Explode : public Sprite
{
public:
	Explode() {}
	~Explode(){}
	void newExplode(Node *node,float x, float y);//����һ����ը
	void removeExplode(Node *node);//�Ƴ���ը
};
#endif