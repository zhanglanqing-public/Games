#include "Pipes.h"
using namespace cocos2d;

Pipes::Pipes(Layer* layer, int maxsize_)
{
	maxsize = maxsize_;
	for (int i=0; i<maxsize; i++) {
		auto pipe = Sprite::create("pipe.png");
		layer->addChild(pipe,5);
		pipe->setPosition(Point(300 + i * 120, 100 + CCRANDOM_0_1() * 100));
		vp.push_back(pipe);
	}
	cur = 0;
}

void Pipes::UpdateWithSpeed(double speed)
{
	for (auto m: vp) {
		m->setPositionX(m->getPositionX() - speed);
	}
}

bool Pipes::isCollisionWith(Sprite* rhs)
{
	
	auto birdx = rhs->getPositionX();
	auto birdy = rhs->getPositionY();
	auto pipex = vp[cur]->getPositionX();
	auto pipey = vp[cur]->getPositionY();

	//实际上这里可以修改游戏的难度
	auto hardlevel = 25;
	if (pipex - birdx > 20) {
		return false;
	} else if (birdx - pipex > 20) {
		if (cur < maxsize - 1) { cur += 1;  return false; }
		else return false;
	} else {
		if (abs(birdy - pipey) < hardlevel) { return false; }
		else { log("DEBUG：collison with % d ", cur); return true; }
	}
}


