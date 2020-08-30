#pragma once
#include "Object.h"
struct sqrtObj: public Object {
	std::vector<Point> nextState;

	sqrtObj(Heap* sc): Object(sc) {
		std::default_random_engine randomGenerator;
		vp = new std::vector<Point> ();
		direction = 0; // cannot change
		vp->push_back(Point(MID,1));
		vp->push_back(Point(MID,2));
		vp->push_back(Point(MID+1,1));
		vp->push_back(Point(MID+1,2));
	}

	bool Canchange() override {
		return false;
	}

	void Change() override {
		if (!Canchange()) return;
	}
};
