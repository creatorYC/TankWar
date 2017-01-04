#include "Explode.h"
void Explode::newExplode(Node *node,float x, float y)
{
	Vector<SpriteFrame *> explodeFrames;
	for (int i = 0; i < 5; i++)		//循环播放帧动画
	{
		for (int j = 0; j < 5; j++)
		{
			SpriteFrame *sFrame = SpriteFrame::create("explosion.png", Rect(j*64,i*64,64,64));
			explodeFrames.pushBack(sFrame);
		}
	}
	Animation *animation = Animation::createWithSpriteFrames(explodeFrames, 0.05);//0.05秒播放一帧
	auto sprite = Sprite::create();
	//执行动作
	Action *action = Sequence::create(
		Animate::create(animation),//动画
		CCCallFuncN::create(sprite,callfuncN_selector(Explode::removeExplode))//删除自己
		 ,NULL);
	node->addChild(sprite);
	sprite->setPosition(Point(x, y));
	sprite->runAction(action);
}
void Explode::removeExplode(Node *node)//移除爆炸
{
	node->removeFromParentAndCleanup(true);
}