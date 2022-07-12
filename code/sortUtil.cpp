#include "sortUtil.h"
/**
	 * This function merges the two arrays of Edges based on their y coordinates.
	 * 
	 * @param arr
	 * @param l
	 * @param m
	 * @param r
*/
void mergeH(vector<Edge> &arr, int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	vector<Edge> L(n1);
	vector<Edge> R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	int i = 0;
	int j = 0;
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i].coord < R[j].coord) {
			arr[k] = L[i];
			i++;
		}
		else if(L[i].coord == R[j].coord){
			if(L[i].edgetype == "bottom" && R[j].edgetype == "bottom"){
				if(L[i].interval.bottom < R[j].interval.bottom){
					arr[k] = L[i];
					i++;
				}
				else{
					arr[k] = R[j];
					j++;
				}
			}
			else if(L[i].edgetype == "bottom" ){
				arr[k] = L[i];
				i++;
			}
			else if (L[i].edgetype == "top" && R[j].edgetype == "top"){
				if(L[i].interval.bottom < R[j].interval.bottom){
					arr[k] = L[i];
					i++;
				}
				else{
					arr[k] = R[j];
					j++;
				}
			}
			else{
				arr[k] = R[j];
				j++;
			}
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}
/**
	 * This function implements merge sort algorithm on the horizontal edges. It makes use of mergeH function. 
	 * 
	 * @param arr
	 * @param l
	 * @param r
	 * @see mergeH()
*/
void mergeSortH(vector<Edge> &arr,int l,int r){
	if(l>=r){
		return;
	}
	int m =l+ (r-l)/2;
	mergeSortH(arr,l,m);
	mergeSortH(arr,m+1,r);
	mergeH(arr,l,m,r);
}
/**
	 * This function merges the two arrays of Edges based on their x coordinates.
	 * 
	 * @param arr
	 * @param l
	 * @param m
	 * @param r
*/
void mergeV(vector<Edge> &arr, int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	vector<Edge> L(n1);
	vector<Edge> R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	int i = 0;
	int j = 0;
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i].coord<R[j].coord) {
			arr[k] = L[i];
			i++;
		}
		else if(L[i].coord == R[j].coord)
        {
            if(L[i].edgetype == "left")
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
        }
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}
/**
	 * This function implements merge sort algorithm on the vertical edges. It makes use of mergeV function. 
	 * 
	 * @param arr
	 * @param l
	 * @param r
	 * @see mergeV()
*/
void mergeSortV(vector<Edge> &arr,int l,int r){
	if(l>=r){
		return;
	}
	int m =l+ (r-l)/2;
	mergeSortV(arr,l,m);
	mergeSortV(arr,m+1,r);
	mergeV(arr,l,m,r);
}
