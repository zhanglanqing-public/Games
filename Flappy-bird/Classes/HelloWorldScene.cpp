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
	// ����һ�ı�������
	auto background = Sprite::create("background.png");
	background->setPosition(Point(sz.width/2, sz.height/2));

	// ����һ��ͼ�껭��
	auto ico = Sprite::create("flappybird.png");
	ico->setPosition(Point(sz.width/2, sz.height * 0.78));

	//����һ�Ŀ�ʼ�˵�����
	auto start = Sprite::create("start.png");
	start->setPosition(Point(sz.width/2, 0.40 * sz.height));
	

	addChild(ico,2);
	addChild(start,1);
	addChild(background,0);



	//���һ����굥������¼�������ǲ��ǵ����ˣ�������Ϊ����start��λ�ò��ܿ�ʼ��Ϸ

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* t, Event* e) { //lambda��ֵ���ݾֲ�����
		Point p = Director::getInstance()->convertToGL(t->getLocationInView());

		auto target = e->getCurrentTarget();
		auto box = target->getBoundingBox();

		if (box.containsPoint(p)) {
			//������Ļ�Ϸ���������һ������
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
