#include <bits/stdc++.h>
#include "Stripe.h"

using namespace std;

void Stripe::initializeStripeMeasure(Interval xin, Interval yin)
		{
			x_interval.makeInterval(xin.bottom,xin.top);
			y_interval.makeInterval(yin.bottom,yin.top);
			x_union = 0;
			tree = NULL;
		}

void Stripe::printStripe()
		{
			cout<<"Stripe: ";
			x_interval.printInterval();
			y_interval.printInterval();
			cout<<"X_union = "<<x_union<<"\n";
			tree->printTree(tree);
			cout<<"\n";
		}

void Stripe::makeIntPoints()
		{
			int_points.clear();
			tree->utilTree(tree, int_points);
		}

void Stripe::printIntPoints()
		{
			for(auto it = int_points.begin(); it != int_points.end(); it++)
			{
				cout<<"Point:"<<it->first<<" End:"<<it->second<<"---";
			}
			cout<<"\n";
		}