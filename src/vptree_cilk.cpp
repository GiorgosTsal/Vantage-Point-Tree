////============================================================================
//// Name        : vptree_cilk.cpp
//// Author      : Giorgos Tsalidis
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Vantage Point Tree Cilk API implementation in C++
////============================================================================

#include <iostream>
#include <cstdlib>
#include <tgmath.h>
#include <cmath>
#include <climits>
#include <iomanip>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "../inc/vptree.h"

using namespace std;

//construct with x as helper to recognize my tree ID
vptree::vptree(int x) {
	//create-set tree ID 
	this->x = x;
}

//destructor
vptree::~vptree(){
	
}
//get my tree ID 
int vptree::getX(){
    return x;
}



vptree * vptree::buildvp(double *X, int n, int d){


	this->getX();

	this->data = X ; //theto ston data ton X
	this->n = n;
	this->d = d;

	this->ptr_idx = d*(n-1); // index
	this->ptr_vp =  X+this->ptr_idx; // vantage point

	// Initialize-allocate space for distances & indexes
	int inOutSize = n/2 + 1;
	double *dist = (double *)malloc((n-1) * sizeof(double));
	int *indexMatrix = (int*)malloc((n-1) * sizeof(int));
	int *innerMatrix = (int*)malloc((inOutSize) * sizeof(int));
	int *outterMatrix = (int*)malloc((inOutSize) * sizeof(int));

	//Store the indexes of the original dataset into another matrix
	for(int i=0; i<(n-1); i++){
		*(indexMatrix+i) = i ;
	}

	// Calculate the distances from the vantage point to all other points of the current dataset(X) and store it on an array
	this->calcDistanceMatrix(dist,n-1,indexMatrix);
	
	// Find Median(radius) of the current dist matrix with QuickSelect
	double median = findMedian(dist, n-1);
	//Set median
	this->ptr_md = median; // radius

	// Splitting data
    //Partition matrix of distances to inner and outer points according to the median distance
    int count_inner = 0 ;
    int count_outter = 0 ;

	for (int i = 0;  i < (n-1); i++) { //until n-1 to leave out the vantage point tree because as assume every time tha the vantage point is the last point(n-1) of my dataset

		if (*(dist + i) >= median) { 
			*(outterMatrix+count_outter) = *(indexMatrix + i);
			count_outter++;
		} else {
			*(innerMatrix + count_inner) = *(indexMatrix + i);
			count_inner++;
		}
	}

	// Delete distance to free memory
	free(dist);

	// Create 2 vptree obj- one for inner and one for outter 
	vptree in(this->x*10+1);
	vptree out(this->x*10+2);


	// Set inner,outer pointers
	this->ptr_in = &in;
	this->ptr_out = &out;

	
	// Call buildVPTREE 2x one for inner and one of outter dataset

	cilk_spawn this->ptr_in->buildvpTREE(this->data, count_inner, d,innerMatrix);
	this->ptr_out->buildvpTREE(this->data, count_outter, d,outterMatrix);
	cilk_sync;

	//Free memory
	free(innerMatrix);
	free(outterMatrix);
	free(indexMatrix);
}

// Recursively builds the binary tree and returns a pointer to the vptree object
//<parameter>*myindex: the index of the point in the original set
vptree * vptree::buildvpTREE(double *X, int n, int d,int *myIndex){


	this->data = X ;
	this->n = n;
	this->d = d;

	// Set break
	if(n<=1){

		return this;
	}

	this->ptr_idx = d*(*(myIndex+(n-1))); // index of the point in the original set
	this->ptr_vp =  X+this->ptr_idx; // vantage point

	// Initialize-allocate space for distances & indexes
	int inOutSize = n/2 + 1;
	double *dist = (double *)malloc((n-1) * sizeof(double));
	int *indexMatrix = (int*)malloc((n-1) * sizeof(int));
	int *innerMatrix = (int*)malloc((inOutSize) * sizeof(int));
	int *outterMatrix = (int*)malloc((inOutSize) * sizeof(int));

	for(int i=0; i<(n-1); i++){
		*(indexMatrix+i) = *(myIndex+i) ;
	}

	// Calculate the distances from the vantage point to all other points of the current dataset(X) and store it on an array
	this->calcDistanceMatrix(dist,n-1,indexMatrix);


	// Find Median(radius) of the current dist matrix with QuickSelect
	double median = cilk_spawn findMedian(dist, n-1);
	//Set median
	this->ptr_md = median; // radius

	// Splitting data
    //Partition matrix of distances to inner and outer points according to the median distance
   // Create arrays for inner and outer points
    int count_inner = 0 ;
    int count_outter = 0 ;

	for (int i = 0;  i < (n-1); i++) {

		if (*(dist + i) >= median) { 
			*(outterMatrix+count_outter) = *(indexMatrix + i);
			count_outter++;
		} else {
			*(innerMatrix + count_inner) = *(indexMatrix + i);
			count_inner++;
		}
	}

	// Delete distance to free memory
	free(dist);



	// Create 2 vptree obj- one for inner and one for outter 
	vptree in(this->x*10+1);
	vptree out(this->x*10+2);

	// Set inner,outer pointers
	this->ptr_in = &in;
	this->ptr_out = &out;



	// Call buildVPTREE 2x one for inner and one of outter dataset

	cilk_spawn this->ptr_in->buildvpTREE(this->data, count_inner, d,innerMatrix);
	this->ptr_out->buildvpTREE(this->data, count_outter, d,outterMatrix);
	cilk_sync;

	//Free memory
	free(innerMatrix);
	free(outterMatrix);
	free(indexMatrix);
}


//This function calculates distances for all points to an array using calculateDistance(double *a) as helper(every two points)
//calculate this distances in parallel
void vptree::calcDistanceMatrix(double *distance,int size, int *index){

	cilk_for (int i=0; i<size; i++){
		*(distance+i) = this->calculateDistance(this->data+(*(index+i))*d);
	}
}


// This function calculates distances between two points
double vptree::calculateDistance(double *a)
{
	double sum = 0;
	for (int i = 0; i < d; i++) {
		sum = sum + pow(*(a+i) - *(this->ptr_vp+i), 2);
	}
	return sqrt(sum);
}

//This function is a helper for printing my results
void vptree::printData(){
	for (int i = 0; i < this->n; ++i)
	{
		cout << i << ": ";
		for (int j = 0; j < this->d; ++j){
			cout <<  *(this->data + i*this->d + j)<< " , ";
		}
	   cout << endl;
	}
}

//This function is a helper for printing my results
void vptree::printDataWithIndex(int *index){
	for (int i = 0; i < this->n; ++i)
	{
		cout << i << ": ";
		for (int j = 0; j < this->d; ++j){
			cout <<  *(this->data + *(index+i)*this->d + j)<< " , ";
		}
	   cout << endl;
	}
}


// Standard partition process of QuickSort().
// It considers the last element as pivot
// and moves all smaller element to left of
// it and greater elements to right
int partition(double arr[], int l, int r)
{
    double x = arr[r];
    int i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= x) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}
// This function returns k'th smallest
// element in arr[l..r] using QuickSort
// based method.  ASSUMPTION: ALL ELEMENTS
// IN ARR[] ARE DISTINCT
double kthSmallest(double arr[], int l, int r, int k)
{
    // If k is smaller than number of
    // elements in array
    if (k > 0 && k <= r - l + 1) {

        // Partition the array around last
        // element and get position of pivot
        // element in sorted array
        int index = partition(arr, l, r);

        // If position is same as k
        if (index - l == k - 1)
            return arr[index];

        // If position is more, recur
        // for left subarray
        if (index - l > k - 1)
            return kthSmallest(arr, l, index - 1, k);

        // Else recur for right subarray
        return kthSmallest(arr, index + 1, r,
            k - index + l - 1);
    }
    // If k is more than number of
    // elements in array
    return INT_MAX;
}
//This function finds median using quickselect and kthSmallest value of an array(my median-th point on the array is splitting the data into two same count points(inner and outer)
double findMedian(double *distances, int sizeofDistances){
	 int n1, n2;
	 double median;
	 double tempDist[sizeofDistances];
 // Find median by creating a copy of distances and using it to QuickSelect
	 for(int i=0;i<sizeofDistances;i++){
		 tempDist[i] = *(distances + i);
	 }
	 if (sizeofDistances % 2 == 0) {
	         n1 = (sizeofDistances + 2) / 2;
	         n2 = sizeofDistances / 2;
	         median = (kthSmallest(tempDist, 0, sizeofDistances - 1, n1) + kthSmallest(distances, 0, sizeofDistances - 1, n2)) / 2.0;
	 }
	 else {
			 median = kthSmallest(tempDist, 0, sizeofDistances - 1, (sizeofDistances+1)/2 );
	 }
	 return median;
}


// Return vantage-point subtree with points inside radius
vptree * vptree::getInner(){
	return this->ptr_in;
}
// Return vantage-point subtree with points outside radius
vptree * vptree::getOuter(vptree * T){
	return this->ptr_out;
}
// Return radius(median of distances to vantage point)
double vptree::getMD(vptree * T){
	return this->ptr_md;
}
//Retunrs coordinates of the vantage point(ti thesi mnimis tou)
double * vptree::getVP(vptree * T){
	return this->ptr_vp;
}
//Return the index in my dataset
int vptree::getIDX(vptree * T){
	return this->ptr_idx;
}
//Set vantage-point subtree with points inside radius
void vptree::setInner(vptree * T){
	this->ptr_in;
}
//Set vantage-point subtree with points outside radius
void vptree::setOuter(vptree * T){
	this->ptr_out;
}
//Set radius(median of distances to vantage point)
void vptree::setMD(vptree * T){
	this->ptr_md;
}
//Set coordinates of the vantage point(ti thesi mnimis tou)
void vptree::setVP(vptree * T){
	this->ptr_vp;
}
//Set the index in my dataset
void vptree::setIDX(int index){
	this->ptr_idx=index;
}




