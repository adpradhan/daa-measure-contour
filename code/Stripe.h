#ifndef STRIPE_H
#define STRIPE_H

#include "ctree.h"
#include "Interval.h"

class Stripe
{
	public:
		Interval x_interval, y_interval;
		set<Interval> x_union_set;
		int x_union;
		ctree *tree;
		map<int, string> int_points;
		void initializeStripeMeasure(Interval xin, Interval yin);
		void printStripe();
		// void initializeStripeMeasure (){};

		void makeIntPoints();

		void printIntPoints();
};

#endif