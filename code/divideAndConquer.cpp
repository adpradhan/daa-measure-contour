#include "divideAndConquer.h"
#include "sortUtil.h"
#include "setUtil.h"
/**
	 * This function finds all the x coordinates and y coordinates of the Rectangles.
	 * 
	 * @param rect vector of Rectangle
*/
pair<set<int>,set<int>> compute_R(vector<Rectangle> rect)
{
	pair<set<int>,set<int>> temp;
	set<int> x, y;
	for(int i=0;i<rect.size();i++)
	{
		x.insert(rect[i].x_left);
		x.insert(rect[i].x_right);
		y.insert(rect[i].y_top);
		y.insert(rect[i].y_bottom);
	}
	temp.first = x;
	temp.second = y;
	return temp;
}
/**
	 * This function computes the partitions based on the y coordinates of the horizontal edges. A partition cannot contain any horizontal edge.
	 * 
	 * @param y
*/
vector<Interval> partition(set<int> &y)
{
	vector<Interval> temp;
	int prev = *(y.begin());
	int cnt = 1;
	for(auto i:y)
	{
		if(cnt == 1) {cnt++;continue;}
		Interval t1;
		t1.makeInterval(prev,i);
		temp.push_back(t1);
		prev = i;
	}
	return temp;
}
/**
	 * It computes all the vertical edges of the rectangles and sorts them based on their x coordinates and their edge types.
     * This function is the driver for the divide and conquer step to compute the stripes. This divides the frames into smaller portions and calls the STRIPES function on each.
	 * 
	 * @param rect vector of Rectangle
     * @see STRIPES()
*/
vector<Stripe> rectangle_dac(vector<Rectangle> &rect)
{
	// cout<<"In rectangle_dac:\n";
	vector<Edge> VRX;
	for(auto r:rect)
	{
		VRX.push_back(r.left);
		VRX.push_back(r.right);
	}
	mergeSortV(VRX,0,VRX.size()-1);
	// cout<<"reached here vrs sort done..............\n";
	Interval x_ext;
	x_ext.makeInterval(VRX[0].coord, VRX[VRX.size()-1].coord);
	StripeStruct ans;
	ans = STRIPES(VRX, x_ext );
	vector<Stripe> Measure_ans = ans.S;
	return Measure_ans;
}
/**
	 * This function calls itself recursively until the frame gets one edge each. 
     * It computes the single(partnerless) edges and uses them to compute the x_union with the help of copy, blacken and concat functions.
	 * 
	 * @param V
     * @param x_ext
     * @see copy()
     * @see blacken()
     * @see concat()
*/
StripeStruct STRIPES(vector<Edge> &V,Interval &x_ext/*,L,R,P,S*/)
{
	vector<Interval> L;
	vector<Interval> R;
	set<int> P;
	vector<Stripe> S;
	StripeStruct SS;
	// base case
	if (V.size()==1)
	{
		if(V[0].edgetype == "left")
		{
			L.push_back(V[0].interval);
		}
		else
		{
			R.push_back(V[0].interval);
		}
		P.insert(-100000);
		P.insert(V[0].interval.bottom);
		P.insert(V[0].interval.top);
		P.insert(100000);
		vector<Interval> partitionY = partition(P);
		for(auto in:partitionY)
		{
			Stripe temps;
			Interval tempin;
			tempin.makeInterval(in.bottom, in.top);
			//(A)
			temps.initializeStripeMeasure(x_ext,tempin);
			if((V[0].interval.top == in.top) && (V[0].interval.bottom == in.bottom))
			{
				if(V[0].edgetype == "left")
				{
					temps.x_union = x_ext.top - V[0].coord;
					//(B)
					temps.tree = temps.tree->insertTree(temps.tree, V[0].coord, "left", NULL, NULL);
				}
				else
				{
					temps.x_union = V[0].coord - x_ext.bottom;
					//(C)
					temps.tree = temps.tree->insertTree(temps.tree, V[0].coord, "right", NULL, NULL);
				}
			}
			S.push_back(temps);
		}
	}
	else
    {
        int mid = V.size()/2;
        int xm = V[mid].coord;
        vector<Edge> V1;
        vector<Edge> V2;
        for(int i=0;i<mid;i++)
        {
            V1.push_back(V[i]);
        }
        for(int i=mid;i<V.size();i++)
        {
            V2.push_back(V[i]);
        }
        Interval int1;
        int1.makeInterval(x_ext.bottom,xm );
        Interval int2;
        int2.makeInterval(xm , x_ext.top);
        StripeStruct S1, S2; //pointer?
        S1 = STRIPES(V1,int1);
        S2 = STRIPES(V2,int2);
        vector<Interval> LR = findIntersect(S1.L, S2.R);
        L = findUnion(findDifference(S1.L, LR),S2.L);
        R = findUnion(findDifference(S2.R, LR),S1.R);
        P = findSetUnion(S1.P,S2.P);
        vector<Stripe> S_left = copy(S1.S,P,int1);
        vector<Stripe> S_right = copy(S2.S,P,int2);
        S_left = blacken(S_left, findDifference(S2.R, LR));
        S_right = blacken(S_right, findDifference(S1.L, LR));
        S = concat(S_left, S_right, P, x_ext);
    }
    SS.L = L;
    SS.R = R;
    SS.P = P;
    SS.S = S;
    return SS;
}
/**
	 * This function extends the partitions of the left frame into the right and vice versa.
	 * 
	 * @param S
     * @param P
     * @param x_interval
     * 
*/
vector<Stripe> copy(vector<Stripe> &S,set<int> &P, Interval &x_interval)
{
    vector<Interval> Py = partition(P);
    vector<Stripe> temp;
    for(auto i : Py)
    {
        Stripe temps;
        Interval tempin; tempin.makeInterval(i.bottom, i.top);
        temps.initializeStripeMeasure(x_interval,tempin);
        temp.push_back(temps);
    }
    int j = 0;
    for(int i=0;i<temp.size();)
    {
        {
            if((temp[i].y_interval.bottom>=S[j].y_interval.bottom ) && (temp[i].y_interval.top<=S[j].y_interval.top ) )
            {
                temp[i].x_union = S[j].x_union;
				// (D)
				temp[i].tree = S[j].tree;
                i++;
            }
            else
            {
            	j++;
            }
        }
    }
    return temp;
}
/**
	 * This function blackens the area on left frame based on the single edges in right frame and vice versa.
	 * This is done in O(n) time complexity as all the Intervals are in sorted order.
     * 
	 * @param S
     * @param J
*/
vector<Stripe> blacken(vector<Stripe> &S, vector<Interval> J)
{
    vector<Interval> J_merge;
    if(J.size()>=1)
        J_merge.push_back(J[0]);
    else
        return S;
    for(int i=1;i<J.size();i++)
    {
        if(J_merge[J_merge.size()-1].top>=J[i].bottom)
        {
            J_merge[J_merge.size()-1].top = max(J_merge[J_merge.size()-1].top,J[i].top);
        }
        else
        {
            J_merge.push_back(J[i]);
        }
    }
    int j=0;
    int i=0;
    for(i=0;(i<S.size() && j<J_merge.size());)
    {
        if((S[i].y_interval.bottom >= J_merge[j].bottom) && (S[i].y_interval.top <= J_merge[j].top))
        {
            S[i].x_union = S[i].x_interval.top - S[i].x_interval.bottom;
				// (E)
            S[i].tree = NULL;
            i++;
        }
        else if((S[i].y_interval.bottom >= J_merge[j].top) )
        {
            j++;
        }
        else if((S[i].y_interval.top <= J_merge[j].bottom) )
        {
            i++;
        }
        else
        {
            // cout<<S[i].y_interval.top << " "<<S[i].y_interval.bottom<<"\n";
            // cout<<J_merge[j].top<<" "<<J_merge[j].bottom<<"\n";
            break;
        }
    }
    return S;
}
/**
	 * This is the merge step of the divide and conquer algorithm. 
     * After computing the stripes for each frame, it merges the left and right frame until we get a whole frame.
	 * 
	 * @param S1
     * @param S2
     * @param P
     * @param x_interval
     * 
*/

vector<Stripe> concat(vector<Stripe> &S1, vector<Stripe> &S2, set<int> &P, Interval &x_int)
{
    vector<Interval> Py = partition(P);
    vector<Stripe> temp;
    for(auto i : Py)
    {
        Stripe temps;
        Interval tempin; tempin.makeInterval(i.bottom, i.top);
        temps.initializeStripeMeasure(x_int,tempin);
        temp.push_back(temps);
    }
    //(F)
    for(int i=0;i<temp.size();i++)
    {
        temp[i].x_union = S1[i].x_union +S2[i].x_union;

		if(S1[i].tree != NULL && S2[i].tree != NULL)
			temp[i].tree = temp[i].tree->insertTree(temp[i].tree, S1[i].x_interval.top, "undef", S1[i].tree, S2[i].tree);

		if(S1[i].tree != NULL && S2[i].tree == NULL)
			temp[i].tree = S1[i].tree;

		if(S1[i].tree == NULL && S2[i].tree != NULL)
			temp[i].tree = S2[i].tree;

		if(S1[i].tree == NULL && S2[i].tree == NULL)
			temp[i].tree = NULL;
    }
    return temp;
}