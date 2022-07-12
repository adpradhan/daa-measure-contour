
#include <bits/stdc++.h>
#include "Point.h"
#include "Interval.h"
#include "LineSegment.h"
#include "Edge.h"
#include "Rectangle.h"
#include "ctree.h"
#include "Stripe.h"
#include "StripeStruct.h"
#include "setUtil.h"
#include "sortUtil.h"
#include "utility.h"
#include "divideAndConquer.h"


using namespace std;
int main()
{
	// cin.open("file.txt");
	// cout.open("cout.txt");
	vector<vector<int>> hardCode;
	vector<Rectangle> inputRectangles;
	int n;
	cin>>n;
	int A,B,C,D;
	for(int i=0;i<n;i++)
	{
		cin>>A>>B>>C>>D;
		Rectangle temp_rect;
		temp_rect.makeRectangle(min(A,B),max(A,B),min(C,D),max(C,D),i);
		inputRectangles.push_back(temp_rect);
	}
	vector<Stripe> measure_ans = rectangle_dac(inputRectangles);
	cout<<"Total Measure = "<<calcMeasure(measure_ans)<<"\n";
	vector<Edge> horizontal_edges = giveHEdge(inputRectangles);
	horizontal_edges = removeHDups(horizontal_edges);
	vector<LineSegment> contour_ans = contour_pieces(horizontal_edges, measure_ans);
	cout<<"\nContour Pieces - Horizontal are:\n";
	for(auto line:contour_ans)
	{
		line.printLineSegment();
	}
	vector<LineSegment> v_Lines = giveContourCycles(contour_ans);
	cout<<"\nContour Pieces - Vertical are:\n";
	for(auto line:v_Lines)
	{
		line.printLineSegment();
	}
}

/*
g++ driver.cpp ctree.cpp Edge.cpp Interval.cpp LineSegment.cpp Point.cpp Rectangle.cpp Stripe.cpp utility.cpp setUtil.cpp sortUtil.cpp divideAndConquer.cpp
*/