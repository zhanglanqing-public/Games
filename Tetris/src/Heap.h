#pragma once
#include "global.h"
#include "Object.h"
struct Object;
struct Heap {
	std::vector<Point>* vp; //the set of points in the heap now
	Heap() {
		vp = new std::vector<Point>();
	
	}
	void Clear();
	void AddObject(Object* obj);


};
