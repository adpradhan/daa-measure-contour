#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Edge.h"

class Rectangle
{
	public:
		int x_left,x_right,y_top,y_bottom;
		Edge left;
		Edge right;
		Edge top;
		Edge bottom;
		Interval x_interval, y_interval;
		int ID;
	void makeRectangle(int xl, int xr, int yb, int yt,int id);
	void printRectangle();
};

#endif