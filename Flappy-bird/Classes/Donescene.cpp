
#include "DoneScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;
Scene* DoneScence::createScene()
{
	auto scene = Scene::create();
	auto layer = DoneScence::create();
	scene->addChild(layer);
	return scene;
}

bool DoneScence::init()
{
	if (!Layer::init()) {return false; }

	auto sz = Director::getInstance()->getWinSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Sprite* bk = Sprite::create("background.png");
	bk->setPosition(Point(sz.width/2, sz.height/2));
	addChild(bk,0);

	auto sprite = Sprite::create("flappybird.png");
	sprite->setPosition(Point(sz.width/2, sz.height * 0.75));
	this->addChild(sprite, 1);

	auto label0 = LabelTTF::create("YOU WIN!", "Arial", 14);
	label0->setPosition(Point(sz.width/2, sz.height* 0.6));
	this->addChild(label0, 2);

	auto label = LabelTTF::create("github.com/zhanglanqing", "Arial", 10);
	label->setPosition(Point(sz.width/2, sz.height* 0.45));
	this->addChild(label, 2);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* t, Event* e) { //lambda按值传递局部变量
		Director::getInstance()->stopAnimation();
		Director::getInstance()->replaceScene(HelloWorld::createScene());
		Director::getInstance()->startAnimation();
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}


void DoneScence::menuCloseCallback(Ref* pSender)
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
