#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "Interval.h"

class LineSegment
{
	public:
		Interval interval;
		int coord;
	void makeLineSegment(Interval in, int co);

	void printLineSegment();
};

#endif