#include <bits/stdc++.h>
#include "Rectangle.h"

using namespace std;

void Rectangle::makeRectangle(int xl, int xr, int yb, int yt,int id)
	{
		x_left = xl;
		x_right = xr;
		y_top = yt;
		y_bottom = yb;
		ID = id;
		x_interval.makeInterval(xl,xr,id);
		y_interval.makeInterval(yb,yt,id);
		left.makeEdge(y_interval,xl,"left",id);
		right.makeEdge(y_interval,xr,"right",id);
		top.makeEdge(x_interval,yt,"top",id);
		bottom.makeEdge(x_interval,yb,"bottom",id);
	}

void Rectangle::printRectangle()
	{
		cout<<"Rectangle: "<<ID<<"\n";
		left.printEdge();
		right.printEdge();
		top.printEdge();
		bottom.printEdge();
	}