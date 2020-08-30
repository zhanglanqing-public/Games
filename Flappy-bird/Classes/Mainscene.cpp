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

	speed = 1;			// ������ˮ���ٶ�
	py = sz.height / 2; //����ĳ�ʼλ��
	v0 = 1.5;			//����ĳ��ٶ�
	dead = false;		
	//���������ʼ��
	sc = new Score();
	sc->InitWith(this);

	//ˮ�ܶ����ʼ��
	pipes = new Pipes(this, 50);

	// ��������
	this->background = Sprite::create("background.png");
	if (!(this->background)) throw;
	this->background->setPosition(Point(sz.width/2, sz.height/2));
	this->addChild(this->background,0);
	 
	//�ײ��Ĺ�����
	backone = Sprite::create("ground1.png");
	backone->setPosition(Point(sz.width/2, 28));
	this->addChild(backone,7);

	backtwo = Sprite::create("ground1.png");
	backtwo->setPosition(Point(sz.width + sz.width/2, 28));
	backtwo->setFlippedX(true);
	this->addChild(backtwo,7);

	//��
	bird = Sprite::create("middleflap.png");
	bird->setPosition(Point(sz.width/4, sz.height/2));
	this->addChild(bird,8);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* t, Event* e) { //lambda��ֵ���ݾֲ�����sz
		if (py <= 245)
			v0 = 3;

		//�����������һ���������ת����
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

	//�ù����������������㷨

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


	//����ص�λ�ƺ��ٶȼ���

	v0 = v0 - 0.15;
	
	if (py <= 64)  DeadAndChangeScene(); 
	else py = py + v0;

	bird->setPosition(bird->getPositionX(), py);

	if (pipes->isCollisionWith(bird) == false) { 
		sc->SetNumber(pipes->getcur());
		if (pipes->getcur() == pipes->getmax() - 1) { //Խ�������е�ˮ��
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
	//����Ӧ��������Ϸ��������Ϣ
	dead = true;
	bird->stopAllActions();
	RotateTo* rot = RotateTo::create(0.2f,90);
	bird->runAction(rot);
	
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [=](Touch* t, Event* e) { //lambda��ֵ���ݾֲ�����
		
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

