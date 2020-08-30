#include "Heap.h"

void Heap::Clear() {
	bool canclear = true;
	while (canclear) {
		canclear = false;
		auto number = RIGHTSIDE - LEFTSIDE + 1;
		sort(vp->begin(), vp->end(), compare2);
		std::vector<std::vector<Point>::iterator> pointers(21); // begin pointer of each row.
		
		std::map<int, int> numLines; // numbers of blocks

		for (auto p=vp->begin(); p!=vp->end(); p++) {
			if (p->x == LEFTSIDE) { pointers[p->y] = p; }
			numLines[p->y]++;
		}

		for (auto p=numLines.begin(); p!=numLines.end(); p++) {
			if (canclear == true) break;
			if (p->second == number) {
				
				canclear = true;
				auto nextelement = vp->erase(pointers[p->first], pointers[p->first] + number);
				for (auto p = nextelement; p!=vp->end(); p++) {
					p->movedown();
				}
			}
		}
	}
}


void Heap::AddObject(Object*obj){
	for (auto& m: *(obj->vp)) {
		vp->push_back(m);
	}
	obj->frozen = true;
	Clear();

}


