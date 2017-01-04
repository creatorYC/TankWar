#include "Explode.h"
void Explode::newExplode(Node *node,float x, float y)
{
	Vector<SpriteFrame *> explodeFrames;
	for (int i = 0; i < 5; i++)		//ѭ������֡����
	{
		for (int j = 0; j < 5; j++)
		{
			SpriteFrame *sFrame = SpriteFrame::create("explosion.png", Rect(j*64,i*64,64,64));
			explodeFrames.pushBack(sFrame);
		}
	}
	Animation *animation = Animation::createWithSpriteFrames(explodeFrames, 0.05);//0.05�벥��һ֡
	auto sprite = Sprite::create();
	//ִ�ж���
	Action *action = Sequence::create(
		Animate::create(animation),//����
		CCCallFuncN::create(sprite,callfuncN_selector(Explode::removeExplode))//ɾ���Լ�
		 ,NULL);
	node->addChild(sprite);
	sprite->setPosition(Point(x, y));
	sprite->runAction(action);
}
void Explode::removeExplode(Node *node)//�Ƴ���ը
{
	node->removeFromParentAndCleanup(true);
}