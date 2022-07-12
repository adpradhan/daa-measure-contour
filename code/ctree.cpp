
#include <bits/stdc++.h>
#include "ctree.h"

using namespace std;

ctree::ctree(int val, string sd, ctree *ls, ctree *rs)
	{
		value = val;
		side = sd;
		lson = ls;
		rson = rs;
	}

	ctree* ctree::insertTree(ctree* root, int val, string sd, ctree *ls, ctree *rs)
	{
		if(root == NULL)
			return new ctree(val, sd, ls, rs);
		else if(val <= root->value)
			root->lson = insertTree(root->lson, val, sd, ls, rs);
		else
			root->rson = insertTree(root->rson, val, sd, ls, rs);

		return root;
	}

	void ctree::utilTree(ctree *root, map<int, string> &int_points)
	{
		if(root == NULL)
			return;

		utilTree(root->lson, int_points);
		if(root->side != "undef")
			int_points.insert(make_pair(root->value, root->side));
		utilTree(root->rson, int_points);
	}

	void ctree::printTree(ctree *root)
	{
		if(root == NULL)
			return;

		printTree(root->lson);
		cout<<root->value<<"-"<<root->side<<"  ";
		printTree(root->rson);
	}