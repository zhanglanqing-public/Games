
#include "Score.h"

void Score::InitWith(Layer* layer)
{
	first = Sprite::create("0.png");
	second = Sprite::create("0.png");
	layer->addChild(first,6);
	layer->addChild(second,6);
	first->setPosition(Point(62,230));
	second->setPosition(Point(68,230));
	nowscore = 0;
}

void Score::_seticon(Sprite* sp, int number)
{
	switch (number)
	{
		case 0:{ sp->setTexture("0.png");break; }
		case 1:{ sp->setTexture("1.png");break; }
		case 2:{ sp->setTexture("2.png");break; }
		case 3:{ sp->setTexture("3.png");break; }
		case 4:{ sp->setTexture("4.png");break; }
		case 5:{ sp->setTexture("5.png");break; }
		case 6:{ sp->setTexture("6.png");break; }
		case 7:{ sp->setTexture("7.png");break; }
		case 8:{ sp->setTexture("8.png");break; }
		case 9:{ sp->setTexture("9.png");break; }

	}
}

void Score::SetNumber(int x)
{
	nowscore = x;
	//取十位数字,个位数字
	int high = nowscore / 10;
	int low = nowscore % 10;
	_seticon(first, high);
	_seticon(second, low);
}

