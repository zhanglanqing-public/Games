#include "HelloWorldScene.h"
#include "Readyscene.h"
USING_NS_CC;
Scene* HelloWorld::createScene(){ 
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init()) { return false; }
	auto sz = Director::getInstance()->getWinSize();
	// 场景一的背景画面
	auto background = Sprite::create("background.png");
	background->setPosition(Point(sz.width/2, sz.height/2));

	// 场景一的图标画面
	auto ico = Sprite::create("flappybird.png");
	ico->setPosition(Point(sz.width/2, sz.height * 0.78));

	//场景一的开始菜单画面
	auto start = Sprite::create("start.png");
	start->setPosition(Point(sz.width/2, 0.40 * sz.height));
	

	addChild(ico,2);
	addChild(start,1);
	addChild(background,0);



	//添加一个鼠标单击检测事件，检测是不是单击了，我们认为单击start的位置才能开始游戏

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* t, Event* e) { //lambda按值传递局部变量
		Point p = Director::getInstance()->convertToGL(t->getLocationInView());

		auto target = e->getCurrentTarget();
		auto box = target->getBoundingBox();

		if (box.containsPoint(p)) {
			//单击屏幕上方，进入下一个场景
			Director::getInstance()->replaceScene(ReayScene::createScene());
			Director::getInstance()->startAnimation();
		}
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,start);
	return true;

}


void HelloWorld::menuCloseCallback(Ref* pSender)
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
