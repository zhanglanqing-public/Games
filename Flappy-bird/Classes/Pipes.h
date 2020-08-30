#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include <vector>
class Pipes {

	public:
		bool isDone() { return cur == maxsize; }
		Pipes( Layer* layer, int maxsize_ = 50);
		~Pipes();
		bool isCollisionWith(Sprite* rhs);
		void UpdateWithSpeed(double speed);
		int getcur() { return cur; }
		int getmax() { return maxsize; }
private:
		int cur;
		int maxsize;
		std::vector<Sprite*> vp;
};