#pragma once
#include "global.h"

struct Point {
	int x, y;
	Point(int x, int y) :x(x), y(y) {}
	void movedown() { if(y == 20) return; y++; }
	void moveleft() { x--; }
	void moveright() { x++; }
	Point leftmove() { return Point(x-1, y);}
	Point rightmove() { return Point(x+1, y);}
	Point downmove() { return Point(x, y+1);}
	bool operator == (const Point& rhs) { return rhs.x == x && rhs.y == y; }
};
bool compare2(const Point&p1, const Point&p2);
bool compare(const Point&p1, const Point&p2);
bool HaveCommonElement(std::vector<Point>* vp1, std::vector<Point>* vp2); 
bool CollisionToWall(std::vector<Point>* vp);