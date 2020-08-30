#include "Mainscene.h"
#include "Readyscene.h"
#include "DoneScene.h"
#include "Score.h"
#include "Pipes.h"
USING_NS_CC;

Scene* Mainscene::createScene() {
	auto scene = Scene::create();
	auto layer = Mainscene::create();
	scene->addChild(layer);
	return scene;
}

bool Mainscene::init()
{
	if (!Layer::init()) { return false; }
	auto sz = Director::getInstance()->getWinSize();

	speed = 1;			// 背景和水管速度
	py = sz.height / 2; //鸟儿的初始位置
	v0 = 1.5;			//鸟儿的初速度
	dead = false;		
	//分数对象初始化
	sc = new Score();
	sc->InitWith(this);

	//水管对象初始化
	pipes = new Pipes(this, 50);

	// 背景画面
	this->background = Sprite::create("background.png");
	if (!(this->background)) throw;
	this->background->setPosition(Point(sz.width/2, sz.height/2));
	this->addChild(this->background,0);
	 
	//底部的滚动条
	backone = Sprite::create("ground1.png");
	backone->setPosition(Point(sz.width/2, 28));
	this->addChild(backone,7);

	backtwo = Sprite::create("ground1.png");
	backtwo->setPosition(Point(sz.width + sz.width/2, 28));
	backtwo->setFlippedX(true);
	this->addChild(backtwo,7);

	//鸟
	bird = Sprite::create("middleflap.png");
	bird->setPosition(Point(sz.width/4, sz.height/2));
	this->addChild(bird,8);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* t, Event* e) { //lambda按值传递局部变量sz
		if (py <= 245)
			v0 = 3;

		//这里可以设置一个鸟儿的旋转动作
		auto uper = RotateTo::create(0.5f,-20);
		auto down = RotateTo::create(0.6f,90);
		auto actions = Sequence::create(uper,down,NULL);
		bird->runAction(actions);
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,bird);

	scheduleUpdate();
	return true;
}

void Mainscene::update(float delta) {

	if (dead) {
		if(py <= 64) {}
		else py = py - 3;
		bird->setPositionY(py);
		return;
	} 

	//让滚动条滚动起来的算法

	int x1 = backone->getPositionX();
	int x2 = backtwo->getPositionX();

	x1 = x1 - speed;
	x2 = x2 - speed;

	auto mapsize = backtwo->getContentSize();

	if (x1 < - mapsize.width/2) {
		x1 = mapsize.width + mapsize.width / 2 - 2; //
	}

	if (x2 < - mapsize.width/2) {
		x2 = mapsize.width + mapsize.width / 2 - 2;
	}

	backone->setPositionX(x1);
	backtwo->setPositionX(x2);


	//鸟相关的位移和速度计算

	v0 = v0 - 0.15;
	
	if (py <= 64)  DeadAndChangeScene(); 
	else py = py + v0;

	bird->setPosition(bird->getPositionX(), py);

	if (pipes->isCollisionWith(bird) == false) { 
		sc->SetNumber(pipes->getcur());
		if (pipes->getcur() == pipes->getmax() - 1) { //越过了所有的水管
			Director::getInstance()->stopAnimation();
			Director::getInstance()->replaceScene(DoneScence::createScene());
			Director::getInstance()->startAnimation();

		}
	}
	else {
		DeadAndChangeScene();
	}
	pipes->UpdateWithSpeed(1.0);

}
void Mainscene::DeadAndChangeScene()
{
	//这里应当给出游戏结束的信息
	dead = true;
	bird->stopAllActions();
	RotateTo* rot = RotateTo::create(0.2f,90);
	bird->runAction(rot);
	
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [=](Touch* t, Event* e) { //lambda按值传递局部变量
		
		Director::getInstance()->replaceScene(ReayScene::createScene());
		Director::getInstance()->startAnimation();
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}


void Mainscene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

bool Mainscene::Iscollision(Sprite* bird, Sprite* pipe)
{
	return false;
}

