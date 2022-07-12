#include "classes.h"

vector<Edge> giveHEdge(vector<Rectangle> &rectangles);	
vector<LineSegment> contour_pieces(vector<Edge> &H_edges, vector<Stripe> &stripes);	
void giveContour(Edge h, Stripe s, vector<LineSegment> &all_int);	
vector<Edge> removeHDups(vector<Edge> &hEdges);		
vector<LineSegment> giveContourCycles(vector<LineSegment> &hLines);	
int calcMeasure(vector<Stripe> &S);	