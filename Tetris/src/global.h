#pragma once
#ifdef _MSC_VER
#include <vector>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <memory>
#include <iostream>
#include <map>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <ctime>
#endif
#ifdef __GNUC__
#include <bits/stdc++.h>
#endif
#include "Point.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define LEFTSIDE 1
#define RIGHTSIDE 12
#define MID int((LEFTSIDE + RIGHTSIDE)/2)
extern int speed;
