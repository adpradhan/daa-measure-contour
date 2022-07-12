#include "utility.h"
#include "sortUtil.h"
/**
	 * We sort all the horizontal edges based on the y coordinates, x coordinates. 
	 * 
	 * @param rectangles vector of rectangles
*/
vector<Edge> giveHEdge(vector<Rectangle> &rectangles)
{
	vector<Edge> ans;
	for(auto r:rectangles)
	{
		ans.push_back(r.bottom);
		ans.push_back(r.top);
	}
	mergeSortH(ans,0,ans.size()-1);
	return ans;
}
/**
	 * This function calls giveCountour function per horizontal edge to compute the contours.
	 * 
	 * @param H_edges 
	 * @param stripes
	 * @see giveContour()
*/
vector<LineSegment> contour_pieces(vector<Edge> &H_edges, vector<Stripe> &stripes)
{
	vector<LineSegment> all_int;
	for(int i = 0; i < stripes.size(); i++)
	{
		stripes[i].makeIntPoints();
	}
	int j = 0;
	for(int i = 0; i < H_edges.size(); i++)
	{
		if(stripes[j].y_interval.top != H_edges[i].coord)
			j++;

		if(H_edges[i].edgetype == "bottom")
		{
			giveContour(H_edges[i], stripes[j], all_int);
		}
		else
		{
			giveContour(H_edges[i], stripes[j+1], all_int);
		}
	}
	return all_int;
}
/**
	 * After the computing the contours for the horizontal lines, this function computes and joins them by the vertical contours. 
	 * 
	 * @param hLines
*/
vector<LineSegment> giveContourCycles(vector<LineSegment> &hLines)
{
	map<int, vector<int>>  x_map_y;
	for(int i = 0; i < hLines.size(); i++)
	{
		x_map_y[hLines[i].interval.bottom].push_back(hLines[i].coord);
		x_map_y[hLines[i].interval.top].push_back(hLines[i].coord);
	}

	vector<LineSegment> v_Lines;

	for(auto it = x_map_y.begin(); it != x_map_y.end(); it++)
	{
		vector<int> y_set = it->second;

		for(int i = 0; i < y_set.size(); i+=2)
		{
			LineSegment tempSegment;
			Interval tempInterval;
			tempInterval.makeInterval(y_set[i], y_set[i+1]);
			tempSegment.makeLineSegment(tempInterval, it->first);

			v_Lines.push_back(tempSegment);
		}
	}
	return v_Lines;
}
/**
	 *  For every horizontal edge, this computes the contour.
	 * 
	 * @param h
	 * @param s
	 * @param all_int
*/
void giveContour(Edge h, Stripe s, vector<LineSegment> &all_int)
{
	int x1 = h.interval.bottom;
	int x2 = h.interval.top;
	LineSegment tempSegment;
	Interval tempInterval;
	if(s.int_points.size() == 0)
	{
		tempSegment.makeLineSegment(h.interval, h.coord);
		all_int.push_back(tempSegment);
		return;
	}
	if(s.int_points.begin()->first >= x2 || s.int_points.rbegin()->first <= x1)
	{
		tempSegment.makeLineSegment(h.interval, h.coord);
		all_int.push_back(tempSegment);
		return;
	}
	auto it = s.int_points.lower_bound(x1);
	if(it->second == "left" && it->first > x1 && it->first <= x2)
	{
		tempInterval.makeInterval(x1, it->first);
		tempSegment.makeLineSegment(tempInterval, h.coord);
		all_int.push_back(tempSegment);
		it++;
	}
	while(it != s.int_points.end() && it->first < x2)
	{
		if(it->second == "right")
		{
			auto temp_it = it;
			temp_it++;
			if(temp_it == s.int_points.end() || (temp_it->first >= x2 /*&& temp_it->second == "left"*/))
			{
				tempInterval.makeInterval(it->first, x2);
				tempSegment.makeLineSegment(tempInterval, h.coord);
				all_int.push_back(tempSegment);
				break;
			}
			else
			{
				if(temp_it->second == "left")
				{
					tempInterval.makeInterval(it->first, temp_it->first);
					tempSegment.makeLineSegment(tempInterval, h.coord);
					all_int.push_back(tempSegment);
				}
				it++;
			}
		}
		else
		{
			it++;
		}
	}
}
/**
	 *  This function merges the horizontal edges that are continuous. This reduces the computation when there are too many overlapping edges.
	 * 
	 * @param hEdges
*/
vector<Edge> removeHDups(vector<Edge> &hEdges)
{
	vector<Edge> htemp;
	htemp.push_back(hEdges[0]);
	for(int i=1;i<hEdges.size();)
	{
		while((htemp[htemp.size()-1].coord == hEdges[i].coord) && (htemp[htemp.size()-1].edgetype == hEdges[i].edgetype))
		{
			if(htemp[htemp.size()-1].interval.top >= hEdges[i].interval.bottom)
			{
				htemp[htemp.size()-1].interval.top = max(htemp[htemp.size()-1].interval.top,hEdges[i].interval.top);
			}
			else
			{
				htemp.push_back(hEdges[i]);
			}
			i++;
			if(i>=hEdges.size())
				break;
		}
		if(i<hEdges.size())
			htemp.push_back(hEdges[i]);
		i++;
	}
	return htemp;
}
/**
	 *  This computes the area of the rectangles.
	 * 
	 * @param S
*/
int calcMeasure(vector<Stripe> &S)
{
    int ans = 0;
    for(int i=0;i<S.size();i++)
    {
        ans += (S[i].x_union * (S[i].y_interval.top - S[i].y_interval.bottom));
    }
    return ans;
}