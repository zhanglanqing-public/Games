#pragma once
#include "Object.h"
struct BarObj :public Object {
	std::vector<Point> nextState;
	BarObj(Heap* sc): Object(sc) {
		std::default_random_engine randomGenerator;
		vp = new std::vector<Point> ();
		direction = randomGenerator() % 2;
		if (direction % 2 == 0) {// represent the v_bar
			vp->push_back(Point(MID,1));
			vp->push_back(Point(MID-1,1));
			vp->push_back(Point(MID+1,1));
			vp->push_back(Point(MID+2,1));
		} else { //represent the h_bar
			vp->push_back(Point(MID,1));
			vp->push_back(Point(MID,2));
			vp->push_back(Point(MID,3));
			vp->push_back(Point(MID,4));
		}
	}
	bool Canchange() override {
		nextState.clear();
		sort(vp->begin(), vp->end(), compare);
		auto mid_x = vp->at(1).x;
		auto mid_y = vp->at(1).y;
		if (direction == 0) {
			nextState.push_back(Point(mid_x, mid_y));
			nextState.push_back(Point(mid_x, mid_y+1));
			nextState.push_back(Point(mid_x, mid_y+2));
			nextState.push_back(Point(mid_x, mid_y+3));
		} else {
			nextState.push_back(Point(mid_x, mid_y));
			nextState.push_back(Point(mid_x-1, mid_y));
			nextState.push_back(Point(mid_x+1, mid_y));
			nextState.push_back(Point(mid_x+2, mid_y));
		}
		if (HaveCommonElement(sc->vp, &nextState) || CollisionToWall(&nextState)) return false;
		else return true;
	}
	void Change() override {
		if (!Canchange()) return;
		direction = direction - 1;
		copy(nextState.begin(), nextState.end(), vp->begin());
	}
};
