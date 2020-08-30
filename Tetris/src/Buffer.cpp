
#include "Buffer.h"



void Buffer::Gotoxy(Point P) {
	int x = P.x, y = P.y;
	if (x < 1 || x > 40) return;
	if (y < 1 || y > 21) return;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x * 2 - 2;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);	
}



void Buffer::Update(std::vector<Point>* heap, std::vector<Point>* obj, std::string& otherState) {
	memset(next, 0, sizeof(next));
	for (auto& m: *heap) {
		next[m.x][m.y] = true;
	}
	for (auto& m: *obj) {
		next[m.x][m.y] = true;
	}

	for (int i = 0; i < otherState.size(); i++) {
		int row = i / 12; // 0-19
		int col = i % 12; // 0-11
		if (otherState[i] == 'x') {
			next[col + 17][row + 1] = true;
		}
	}

	for (int i = 1; i <= 40; i++) {
		for (int j = 1; j <= 20; j++) {
			if (G[i][j] == next[i][j]) {}
			else if(G[i][j] == true && next[i][j] == false) {
				Gotoxy(Point(i, j));
				std::cout << "  ";
			} else {
				Gotoxy(Point(i, j));
				std::cout << "\u2588";
			}
		}
	}
	memcpy(G, next, sizeof(G));
}

