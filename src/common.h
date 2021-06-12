#pragma once
#include <string>
#include <iostream>
#include <fstream>


struct Point {
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
};


struct FieldPos {
	int x, y;
	FieldPos(int x, int y) : x(x), y(y) {}
};

#define MAX_VELOCITY 20000.0f
#define AIR_RESISTANCE 0.02f