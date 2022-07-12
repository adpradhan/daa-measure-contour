#include "classes.h"

StripeStruct STRIPES(vector<Edge> &V,Interval &x_ext/*,L,R,P,S*/); 
pair<set<int>,set<int>> compute_R(vector<Rectangle> rect); 
vector<Interval> partition(set<int> &y);
vector<Stripe> rectangle_dac(vector<Rectangle> &rect);	
vector<Stripe> concat(vector<Stripe> &S1, vector<Stripe> &S2, set<int> &P, Interval &x_int);	
vector<Stripe> blacken(vector<Stripe> &S, vector<Interval> J);	
vector<Stripe> copy(vector<Stripe> &S,set<int> &P, Interval &x_interval);