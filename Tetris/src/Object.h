#pragma once
#include "global.h"
#include "Heap.h"

#include <cassert>
#include <cstdint>

struct Heap;

class Color {
public:
	uint8_t ToWindowsColor() const {
		switch (color) {
		case RED:    return FOREGROUND_INTENSITY | FOREGROUND_RED;
		case GREEN:  return FOREGROUND_INTENSITY | FOREGROUND_GREEN;
		case BLUE:   return FOREGROUND_INTENSITY | FOREGROUND_BLUE;
		case YELLOW: return FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
		case WHITE:  return FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		default: assert(false);
		}
		return 0; // Make compiler happy
	}
	Color static Random() {
		static auto seed = static_cast<unsigned int>(time(nullptr));
		static auto rander = std::default_random_engine(seed);
		return Color(rander() % KINDS);
	}
	Color static White() {
		return Color(WHITE);
	}

private:
	enum : uint8_t {
		RED,
		GREEN,
		BLUE,
		YELLOW,
		WHITE,
		KINDS = WHITE,
	};
	
	Color(uint8_t c) : color(c) {}
	uint8_t color;
};

struct Object {
	std::vector<Point>* vp;
	Heap* sc;
	int direction;
	bool frozen;
	Color color;

	Object(Heap* s) : sc(s), frozen(false), color(Color::Random()) {}
	virtual ~Object() {} // Delete sc ?

	bool CanMoveLeft();
	bool CanMoveRight();
	bool CanMoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	virtual bool Canchange() { return true; }
	virtual void Change() {}
};
