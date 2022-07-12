#ifndef CTREE_H
#define CTREE_H

#include <bits/stdc++.h>
using namespace std;
class ctree
{
	
	public:
	
	int value;
	string side;  
	ctree *lson;
	ctree *rson;
	ctree(int val, string sd, ctree *ls, ctree *rs);

	ctree* insertTree(ctree* root, int val, string sd, ctree *ls, ctree *rs);

	void utilTree(ctree *root, map<int, string> &int_points);

	void printTree(ctree *root);

};

#endif