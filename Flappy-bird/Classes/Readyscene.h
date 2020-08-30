#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class ReayScene: public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	void menuCloseCallback(cocos2d::Ref* pSender);
	void update(float delta);
	CREATE_FUNC(ReayScene);
	Sprite* backone;
	Sprite* backtwo;
};

