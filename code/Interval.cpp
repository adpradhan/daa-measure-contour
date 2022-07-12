#include <bits/stdc++.h>
#include "Interval.h"

using namespace std;


void Interval::makeInterval(int a,int b)
	{
		bottom = a;
		top = b;
		ID = -1;
	}

void Interval::makeInterval(int a,int b,int id)
	{
		bottom = a;
		top = b;
		ID = id;
	}

void Interval::printInterval()
	{
		cout<<"Interval: "<<bottom<<"-"<<top<<" "<<ID<<"\n";
	}