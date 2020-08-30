
#include "Readyscene.h"
#include "Mainscene.h"
USING_NS_CC;

Scene* ReayScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ReayScene::create();
	scene->addChild(layer);

	return scene;
}


bool ReayScene::init()
{
	if (!Layer::init()) { return false; }

	auto sz = Director::getInstance()->getWinSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("instructions.png");
	background->setPosition(Point(sz.width/2, sz.height/2));
	Sprite* bird = Sprite::create("middleflap.png");
	bird->setPosition(Point(sz.width/4, sz.height/2));
	
	addChild(background,0);
	addChild(bird,1);


	backone = Sprite::create("ground1.png");
	backone->setPosition(Point(sz.width/2, 28));
	this->addChild(backone,7);

	backtwo = Sprite::create("ground1.png");
	backtwo->setPosition(Point(sz.width + sz.width/2, 28));
	backtwo->setFlippedX(true);
	this->addChild(backtwo,7);


	auto jump = MoveBy::create(0.75f,Point(0,10));
	auto down = MoveBy::create(0.75f,Point(0,-10));
	auto rep = Sequence::create(jump, down, NULL);
	auto repeat = RepeatForever::create(rep);

	bird->runAction(repeat);


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* t, Event* e) { //lambda按值传递局部变量
		Director::getInstance()->stopAnimation();
		Director::getInstance()->replaceScene(Mainscene::createScene());
		Director::getInstance()->startAnimation();
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	scheduleUpdate();
	return true;
}

void ReayScene::update(float delta)
{
	double speed = 1;
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
}
