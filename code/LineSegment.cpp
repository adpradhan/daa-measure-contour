#include <bits/stdc++.h>
#include "LineSegment.h"

using namespace std;

void LineSegment::makeLineSegment(Interval in, int co)
	{
		interval.makeInterval(in.bottom,in.top);
		coord = co;
	}

void LineSegment::printLineSegment()
	{
		cout<<"p1:"<<interval.bottom<<" p2:"<<interval.top<<" coord:"<<coord<<"\n";
	}