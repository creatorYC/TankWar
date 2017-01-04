#ifndef __BLOOD__BAR__H__
#define __BLOOD__BAR__H__

#include "cocos2d.h"  
using namespace cocos2d;

class BloodBar : public Node
{
public:
	BloodBar();

public:
	void setBackgroundTexture(const char *pName);
	void setForegroundTexture(const char *pName);
	void setTotalProgress(float total);
	void setCurrentProgress(float progress);
	float getCurrentProgress() const;
	float getTotalProgress() const;

private:
	void setForegroundTextureRect(const Rect &rect);

private:
	Sprite *progressBackground;
	Sprite *progressForeground;
	float totalProgress;
	float currentProgress;
	float scale;
};

#endif  