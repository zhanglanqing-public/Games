#pragma once

#include "cocos2d.h"

#include <vector>

#include "Score.h"
#include "Pipes.h"

using namespace cocos2d; //这里命名空间不能漏！！IDE居然不提示


class Mainscene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void changeScene(cocos2d::Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Mainscene);

	void update(float delta);

	void DeadAndChangeScene();

	bool Iscollision(Sprite* bird, Sprite* pipe);

	

private:
	
	Sprite* bird;				//小鸟
	Sprite* background;			//屏幕背景
	Sprite* backone;			//屏幕下方两个滚动条
	Sprite* backtwo;			//屏幕下方两个滚动条
	int speed;					//滚动条滚动的速度
	double px;					//滚动条背景的坐标

	//有关鸟儿的信息

	double v0;					//方向向上为正，向下为负
	double py;					//鸟儿的坐标
	bool dead;					//游戏结束的标志
	

	Pipes* pipes;
	Score* sc;
	
};


