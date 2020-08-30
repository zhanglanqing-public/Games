#pragma once
#include "Object.h"
struct crossObj: public Object {
	std::vector<Point> nextState;
	crossObj(Heap* sc): Object(sc) {
		std::default_random_engine randomGenerator;
		vp = new std::vector<Point> ();
		direction = 0; // |, begin and clocks wise
		auto target = randomGenerator() % 4;
		vp->push_back(Point(MID,1));
		vp->push_back(Point(MID,2));
		vp->push_back(Point(MID,3));
		vp->push_back(Point(MID+1,2));

	}
	bool Canchange() override {
		nextState.clear();
		sort(vp->begin(), vp->end(), compare);
		if (direction == 0) {
			auto x = vp->at(1).x;
			auto y = vp->at(1).y;
			nextState.push_back(Point(x, y));
			nextState.push_back(Point(x, y+1));
			nextState.push_back(Point(x+1, y));
			nextState.push_back(Point(x-1, y));
		} else if (direction == 1) {
			auto x = vp->at(1).x;
			auto y = vp->at(1).y;
			nextState.push_back(Point(x, y));
			nextState.push_back(Point(x, y+1));
			nextState.push_back(Point(x, y-1));
			nextState.push_back(Point(x-1, y));
		} else if (direction == 2) {
			auto x = vp->at(2).x;
			auto y = vp->at(2).y;
			nextState.push_back(Point(x, y));
			nextState.push_back(Point(x, y-1));
			nextState.push_back(Point(x+1, y));
			nextState.push_back(Point(x-1, y));
		} else {
			auto x = vp->at(2).x;
			auto y = vp->at(2).y;
			nextState.push_back(Point(x, y));
			nextState.push_back(Point(x, y-1));
			nextState.push_back(Point(x, y+1));
			nextState.push_back(Point(x+1, y));
		}
		if (HaveCommonElement(sc->vp, &nextState) || CollisionToWall(&nextState)) return false;
		else return true;
	}

	void Change() override {
		if (!Canchange()) return;
		direction = (direction + 1) % 4;
		copy(nextState.begin(), nextState.end(), vp->begin());
	}
};
