#pragma once
#include "global.h"
#include "Point.h"

struct Buffer {
	bool G[41][21];		// what is on screen now.
	bool next[41][21];	// next state of screen.

	
	Buffer() { 
		memset(G,0,sizeof(G));
		for (int i = 1; i <= 21; i++) {
			Gotoxy(Point(15, i));
			std::cout << " |";
		}
	
	}
	void Gotoxy(Point P);
	void Update(std::vector<Point>* heap, std::vector<Point>* obj, std::string& otherState);
	
	
	std::string EncodeStateToString() {
		// 20 rows 12 cols, 240 bytes in total.
		std::string ret(240, 'o');
		int cnt = 0;
		for (int i = 1; i <= 20; i++) {
			for (int j = LEFTSIDE; j <= RIGHTSIDE; j++) {
				if (G[j][i]) {
					ret[cnt] = 'x';
				}
				cnt++;
			}
		}
		return ret;
	}
};
