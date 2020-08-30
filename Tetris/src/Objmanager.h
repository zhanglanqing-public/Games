#pragma once
#include "global.h"
#include "Heap.h"
#include "Object.h"
#include "Buffer.h"

#define kbhit	_kbhit
#define getch	_getch

struct  Heap;
struct Buffer;

struct ObjectManager {
	Heap* hp;
	Object* obj;
	Buffer* screen;
	bool gameOver;

	ObjectManager(Heap* s, Buffer* buffer_) { hp = s; screen = buffer_; gameOver = false; obj = nullptr; }
	char Keyboard(){
		if (!kbhit()) {
			return getch();
		} else {
			return '\0';
		}
	}
	bool ObjValid() { return obj != nullptr && obj->frozen == false; }
	void MoveLeft() { obj->MoveLeft(); }
	void MoveRight() { obj->MoveRight(); }
	void MoveDown() {
		if (!obj->CanMoveDown()) {
			for (auto& m: *(obj->vp)) {
				if (m.y == 1) {
					gameOver = true;
				}
			}
		}
		obj->MoveDown();
	}
	void Init();
	void SetColor(const Color& color);
	void Print(std::string& oth) {
		if (!screen) return;
		SetColor(obj->color);
		screen->Update(hp->vp, obj->vp, oth);
		SetColor(Color::White());
		
	}
	void Delay() {
		for(int i=0; i<(5-speed)*20; i++) {
			for(int j=0; j<100; j++) {
				int *p = new int; delete p;
				if (kbhit()) {
					char key=getch();
					if (key=='a') {
						MoveLeft();
					} else if (key == 'd') {
						MoveRight();
					} else if (key == ' ') {
						Change();
					}
				}
			}
		}
	}

	void Change() { obj->Change(); }
};

