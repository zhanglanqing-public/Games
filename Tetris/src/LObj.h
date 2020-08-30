#pragma once
#include "Object.h"


struct LObj: public Object {
	std::vector<Point> nextState;
	LObj(Heap* sc): Object(sc) {
		std::default_random_engine randomGenerator;
		vp = new std::vector<Point> ();
		auto target = randomGenerator() % 4;
		direction = 0; //anti clocks wise
		vp->push_back(Point(MID,1));
		vp->push_back(Point(MID,2));
		vp->push_back(Point(MID,3));
		vp->push_back(Point(MID+1,3));

	}

	bool Canchange() override {
		nextState.clear();
		sort(vp->begin(), vp->end(), compare);
		if (direction == 0) {
			auto x = vp->at(3).x;
			auto y = vp->at(3).y;
			nextState.push_back(Point(x, y));
			nextState.push_back(Point(x, y-1));
			nextState.push_back(Point(x-1, y));
			nextState.push_back(Point(x-2, y));
		} else if (direction == 1) {
			auto x = vp->at(2).x;
			auto y = vp->at(2).y;
			nextState.push_back(Point(x, y));
			nextState.push_back(Point(x, y-1));
			nextState.push_back(Point(x, y+1));
			nextState.push_back(Point(x-1, y-1));
		} else if (direction == 2) {
			auto x = vp->at(1).x;
			auto y = vp->at(1).y;
			nextState.push_back(Point(x, y));
			nextState.push_back(Point(x, y+1));
			nextState.push_back(Point(x+1, y));
			nextState.push_back(Point(x+2, y));
		} else {
			auto x = vp->at(1).x;
			auto y = vp->at(1).y;
			nextState.push_back(Point(x, y));
			nextState.push_back(Point(x, y+1));
			nextState.push_back(Point(x, y+2));
			nextState.push_back(Point(x+1, y+2));
		}

		return !(HaveCommonElement(sc->vp, &nextState) ||
				 CollisionToWall(&nextState));
	}

	void Change() override {
		if (!Canchange()) return;
		direction = (direction + 1) % 4;
		copy(nextState.begin(), nextState.end(), vp->begin());
	}

};