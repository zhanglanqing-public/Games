#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Score {
public:
	Score(){}
	~Score(){}
	void InitWith(Layer* layer);
	void SetNumber(int x);
	
private:
	Sprite* first;
	Sprite* second;
	int nowscore;
	void _seticon(Sprite* sp, int number);
};
