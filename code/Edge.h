#ifndef EDGE_H
#define EDGE_H

#include "Interval.h"
#include <bits/stdc++.h>
using namespace std;

class Edge
{
	public:
		Interval interval;
		int coord;
		string edgetype;
		int ID;
	void makeEdge(Interval in, int co, string edget,int id);
	void printEdge();
};

#endif