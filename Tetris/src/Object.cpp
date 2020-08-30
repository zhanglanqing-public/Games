#include "Object.h"
bool Object::CanMoveLeft()  {
	std::vector<Point> tmp;
	for(auto &m:*vp){
		auto tmper = m.leftmove();
		if (tmper.x < LEFTSIDE) return false;
		else tmp.push_back(tmper);
	}
	//is it collision with the Heap ?
	if (HaveCommonElement(sc->vp, &tmp)) return false;
	else return true;
}
bool Object::CanMoveRight() {
	std::vector<Point> tmp;
	for(auto &m:*vp){
		auto tmper = m.rightmove();
		if (tmper.x > RIGHTSIDE) return false;
		else tmp.push_back(tmper);
	}
	//is it collision with the Heap ?
	if (HaveCommonElement(sc->vp, &tmp)) return false;
	else return true;
}
bool Object::CanMoveDown() {
	std::vector<Point> tmp;
	for(auto &m:*vp) {
		auto tmper = m.downmove();
		tmp.push_back(tmper);
	}
	//is it collision with the Heap ?
	if (HaveCommonElement(sc->vp, &tmp)) {
		return false;
	}
	for (auto &m: tmp) {
		if (m.y == 21) return false;
	}

	return true;
}
void Object::MoveLeft() {
	if (frozen || !CanMoveLeft()) return;
	for (auto &m: *vp) {
		m.moveleft();
	}
}
void Object::MoveRight() {
	if(frozen || !CanMoveRight()) return;
	for (auto &m:*vp) {
		m.moveright();
	}
}
void Object::MoveDown() {
	if (frozen) return;
	if (!CanMoveDown()) {
		sc->AddObject(this);
		return;
	}
	for (auto &m:*vp) {
		m.movedown();
	}
}
