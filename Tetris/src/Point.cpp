#include "Point.h"
bool compare2(const Point&p1, const Point&p2) {
	if (p1.y > p2.y) return true;
	else if (p1.y < p2.y) return false;
	else return p1.x < p2.x;
}
bool compare(const Point&p1, const Point&p2) {
	if (p1.y < p2.y) return true;
	else if (p1.y > p2.y) return false;
	else return p1.x < p2.x;
}
bool HaveCommonElement(std::vector<Point>* vp1, std::vector<Point>* vp2) {
	for(auto &m: *vp1) {
		for(auto &n: *vp2) {
			if (m == n) return true;
		}
	}
	return false;
}
bool CollisionToWall(std::vector<Point>* vp){

	for (auto& m: *vp) {
		if(m.x < LEFTSIDE|| m.x > RIGHTSIDE) return true;
		if(m.y > 20) return true;
	}
	return false;
}

