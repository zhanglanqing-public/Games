#pragma once

#include "cocos2d.h"

#include <vector>

#include "Score.h"
#include "Pipes.h"

using namespace cocos2d; //���������ռ䲻��©����IDE��Ȼ����ʾ


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
	
	Sprite* bird;				//С��
	Sprite* background;			//��Ļ����
	Sprite* backone;			//��Ļ�·�����������
	Sprite* backtwo;			//��Ļ�·�����������
	int speed;					//�������������ٶ�
	double px;					//����������������

	//�й��������Ϣ

	double v0;					//��������Ϊ��������Ϊ��
	double py;					//���������
	bool dead;					//��Ϸ�����ı�־
	

	Pipes* pipes;
	Score* sc;
	
};


