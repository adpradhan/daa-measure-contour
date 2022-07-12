#include <bits/stdc++.h>

#include "Edge.h"
using namespace std;

void Edge::makeEdge(Interval in, int co, string edget,int id)
	{
		interval.makeInterval(in.bottom,in.top,id);
		coord = co;
		edgetype = edget;
		ID = id;
	}

void Edge::printEdge()
	{
		cout<<"Edge: "<<interval.bottom<<"-"<<interval.top<<" "<<edgetype<<" "<<"coord:"<<coord<<" "<<ID<<"\n";
	}