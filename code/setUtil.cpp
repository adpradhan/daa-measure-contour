#include "setUtil.h"
/**
	 * Finds the union of two sets
	 * 
	 * @param s1
     * @param s2
*/
set<int> findSetUnion(set<int> s1, set<int> s2)
{
    for(auto i: s2)
    {
        s1.insert(i);
    }
    return s1;
}
/**
	 * This function finds the intersection between two vectors of Intervals. Here the intervals are sorted so it can be achieved in O(n) time complexity.
	 * This function returns the sorted vector of Intervals.
	 * 
     * 
	 * @param i1
     * @param i2
*/
vector<Interval> findIntersect(vector<Interval> &i1, vector<Interval> &i2)
{
    vector<Interval> ans;
    int j=0;
    for(int i=0;(i<i1.size() && j<i2.size());)
    {
        if((i1[i].bottom == i2[j].bottom) && (i1[i].top == i2[j].top) && (i1[i].ID == i2[j].ID))
        {
            ans.push_back(i1[i]);
            j++;
            i++;
        }
        else if((i1[i].bottom == i2[j].bottom) && (i1[i].top == i2[j].top) && (i1[i].ID > i2[j].ID) )
        {
            j++;
        }
        else if((i1[i].bottom == i2[j].bottom) && (i1[i].top == i2[j].top) && (i1[i].ID < i2[j].ID) )
        {
            i++;
        }
        else if((i1[i].bottom > i2[j].bottom))
        {
            j++;
        }
        else if((i1[i].bottom < i2[j].bottom))
        {
            i++;
        }
        else if((i1[i].top > i2[j].top))
        {
            j++;
        }
        else if((i1[i].top < i2[j].top))
        {
            i++;
        }

    }
    return ans;
}
/**
	 * This function finds the union between two vectors of Intervals. Here the intervals are sorted so it can be achieved in O(n) time complexity.
	 * This function returns the sorted vector of Intervals.
     * 
	 * @param i1
	 * @param i2
*/
vector<Interval> findUnion(vector<Interval> i1, vector<Interval> i2)
{
    vector<Interval> ans;
    int j=0;
    int i;
    for(i=0;(i<i1.size() && j<i2.size());)
    {
        if(i1[i].bottom<i2[j].bottom)
        {
            ans.push_back(i1[i]);
            i++;
        }
        else if(i1[i].bottom>i2[j].bottom)
        {
            ans.push_back(i2[j]);
            j++;
        }
        else if((i1[i].bottom==i2[j].bottom)&&(i1[i].top<i2[j].top))
        {
            ans.push_back(i1[i]);
            i++;
        }
        else if((i1[i].bottom==i2[j].bottom)&&(i1[i].top>i2[j].top))
        {
            ans.push_back(i2[j]);
            j++;
        }
        else if((i1[i].bottom==i2[j].bottom)&&(i1[i].top==i2[j].top) && (i1[i].ID<i2[j].ID))
        {
            ans.push_back(i1[i]);
            i++;
        }
        else if((i1[i].bottom==i2[j].bottom)&&(i1[i].top==i2[j].top) && (i1[i].ID>i2[j].ID))
        {
            ans.push_back(i2[j]);
            j++;
        }
        else
        {
            ans.push_back(i2[j]);
            j++;
            i++; //all same case
        }
    }
    while(i<i1.size())
    {
        ans.push_back(i1[i]);
        i++;
    }
    while(j<i2.size())
    {
        ans.push_back(i2[j]);
        j++;
    }
    return ans;
}
/**
	 * This function finds the difference between two vectors of Intervals. Here the intervals are sorted so it can be achieved in O(n) time complexity.
	 * This function returns the sorted vector of Intervals.
	 * 
	 * @param i1
	 * @param i2
*/
vector<Interval> findDifference(vector<Interval> &i1, vector<Interval> &i2)
{
    vector<Interval> ans;
    int j=0;
    int i;
    for(i=0;(i<i1.size() && j<i2.size());)
    {
        if((i1[i].bottom == i2[j].bottom) && (i1[i].top == i2[j].top) && (i1[i].ID == i2[j].ID))
        {
            j++;
            i++;
        }
        else if((i1[i].bottom == i2[j].bottom) && (i1[i].top == i2[j].top) && (i1[i].ID > i2[j].ID) )
        {
            j++;
        }
        else if((i1[i].bottom == i2[j].bottom) && (i1[i].top == i2[j].top) && (i1[i].ID < i2[j].ID) )
        {
            ans.push_back(i1[i]);
            i++;
        }
        else if((i1[i].bottom > i2[j].bottom))
        {
            j++;
        }
        else if((i1[i].bottom < i2[j].bottom))
        {
            ans.push_back(i1[i]);
            i++;
        }
        else if((i1[i].top > i2[j].top))
        {
            j++;
        }
        else if((i1[i].top < i2[j].top))
        {
            ans.push_back(i1[i]);
            i++;
        }
    }
    while(i<i1.size())
    {
        ans.push_back(i1[i]);
        i++;
    }
    return ans;
}