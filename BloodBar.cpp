#include "BloodBar.h"  

void BloodBar::setBackgroundTexture(const char *pName)
{
	progressBackground = Sprite::create(pName);
	this->addChild(progressBackground);
}

void BloodBar::setForegroundTexture(const char *pName)
{
	progressForeground = Sprite::create(pName);
	progressForeground->setAnchorPoint(Point(0.02f, 0.5f));
	progressForeground->setPosition(Point(-progressForeground->getContentSize().width * 0.5f, 0));
	this->addChild(progressForeground);
}

void BloodBar::setTotalProgress(float total)
{
	if (progressForeground == NULL) { return; }
	scale = progressForeground->getContentSize().width / total;
	totalProgress = total;
}

void BloodBar::setCurrentProgress(float progress)
{
	if (progressForeground == NULL) { return; }
	if (progress < 0.0f) { progress = 0.0f; }
	if (progress > totalProgress) { progress = totalProgress; }
	currentProgress = progress;
	float rectWidth = progress * scale;
	const Point from = progressForeground->getTextureRect().origin;
	const Rect rect = CCRectMake(from.x, from.y, rectWidth, progressForeground->getContentSize().height);
	setForegroundTextureRect(rect);
}

void BloodBar::setForegroundTextureRect(const Rect &rect)
{
	progressForeground->setTextureRect(rect);
}

BloodBar::BloodBar(): progressBackground(NULL), progressForeground(NULL)
					, totalProgress(0.0f), currentProgress(0.0f), scale(1.0f){}

float BloodBar::getCurrentProgress() const
{
	return currentProgress;
}

float BloodBar::getTotalProgress() const
{
	return totalProgress;
}