////============================================================================
//// Name        : vptree_cilk.cpp
//// Author      : Giorgos Tsalidis
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Vantage Point Tree Cilk API implementation in C++
////============================================================================
//
//#include <iostream>
//#include <cstdlib>
//#include <tgmath.h>
//#include <cmath>
//#include <climits>
//#include <iomanip>
//#include <cilk/cilk.h>
//#include <cilk/cilk_api.h>
//#include "../inc/vptree.h"
//
//
//using namespace std;
//
//vptree::vptree(int x) {
//	cout << "create tree ID : " << x << endl;
//	this->x = x;
//}
//
//
//vptree::~vptree() {
//	cout << "DESTRUCTION! " << endl;
//}
//
//int vptree::getX() {
//	cout << "my tree ID : " << x << endl;
//	return x;
//}
//
//vptree * vptree::buildvp(double *X, int n, int d) {
//
//	this->getX();
//
//	this->data = X;
//	this->n = n;
//	this->d = d;
//
//	cout << "my matrix" << endl;
//	this->printData();
//
//	this->ptr_idx = d * (n - 1); // index
//	this->ptr_vp = X + this->ptr_idx; // vantage point
//
//	// init matrix for dist & indexs
//	int inOutSize = n / 2 + 1;
//	double *dist = (double *) malloc((n - 1) * sizeof(double));
//	int *indexMatrix = (int*) malloc((n - 1) * sizeof(int));
//	int *innerMatrix = (int*) malloc((inOutSize) * sizeof(int));
//	int *outterMatrix = (int*) malloc((inOutSize) * sizeof(int));
//
//	for (int i = 0; i < (n - 1); i++) {
//		*(indexMatrix + i) = i;
//	}
//
//	// calc distiance
//	this->calcDistanceMatrix(dist, n - 1, indexMatrix);
//	cout << "distance kai kala....:" << endl;
//	for (int i = 0; i < (n - 1); i++) {
//		cout << *(dist + i) << endl;
//	}
//
//	// find median
//	double median = findMedian(dist, n - 1);
//	cout << "median is:" << median << endl;
//	this->ptr_md = median; // radius
//
//	// split data
//	//partition matrix of distances to inner and outer points according to the median distance
//	int count_inner = 0;
//	int count_outter = 0;
//
//	for (int i = 0; i < (n - 1); i++) {
//
//		if (*(dist + i) >= median) { //distances[i] !=0.0 gia na vgazo ekso to vantage point
//			*(outterMatrix + count_outter) = *(indexMatrix + i);
//			count_outter++;
//		} else {
//			*(innerMatrix + count_inner) = *(indexMatrix + i);
//			count_inner++;
//		}
//	}
//	cout << "Loipon ta kanamae split!" << endl;
//
//	for (int i = 0; i < count_inner; i++) {
//		cout << "index inner : " << *(innerMatrix + i) << endl;
//	}
//
//	cout << "Loipon ta kanamae split!" << endl;
//	for (int i = 0; i < count_outter; i++) {
//		cout << "outer inner : " << *(outterMatrix + i) << endl;
//	}
//	// delete distance
//	free(dist);
//
//	// create 2 vptree obj
//	vptree in(this->x * 10 + 1);
//	vptree out(this->x * 10 + 2);
//
//	// set inner,outer pointers
//	this->ptr_in = &in;
//	this->ptr_out = &out;
//
//	cout << "name : " << this->getInner()->getX() << endl;
//
//	// call buildVPTREE 2x
//
//
//	cilk_spawn  this->ptr_in->buildvpTREE(this->data, count_inner, d, innerMatrix);
//	this->ptr_out->buildvpTREE(this->data, count_outter, d, outterMatrix);
//	cilk_sync;
//
//	//free memory
//	free(innerMatrix);
//	free(outterMatrix);
//	free(indexMatrix);
//
//}
//
//vptree * vptree::buildvpTREE(double *X, int n, int d, int *myIndex) {
//
//	this->getX();
//
//	this->data = X;
//	this->n = n;
//	this->d = d;
//
//	// set break
//	if (n <= 1) {
//
//		return this;
//	}
//
//	cout << "my matrix" << endl;
//	this->printDataWithIndex(myIndex);
//
//
//	this->ptr_idx = d * (*(myIndex + (n - 1))); // index
//	this->ptr_vp = X + this->ptr_idx; // vantage point
//
//	// init matrix for dist & indexs
//	int inOutSize = n / 2 + 1;
//	double *dist = (double *) malloc((n - 1) * sizeof(double));
//	int *indexMatrix = (int*) malloc((n - 1) * sizeof(int));
//	int *innerMatrix = (int*) malloc((inOutSize) * sizeof(int));
//	int *outterMatrix = (int*) malloc((inOutSize) * sizeof(int));
//
//	for (int i = 0; i < (n - 1); i++) {
//		*(indexMatrix + i) = *(myIndex + i);
//	}
//
//	// calc distiance
//	this->calcDistanceMatrix(dist, n - 1, indexMatrix);
//	cout << "distance kai kala....:" << endl;
//	for (int i = 0; i < (n - 1); i++) {
//		cout << *(dist + i) << endl;
//	}
//
//	// find median
//	double median = cilk_spawn findMedian(dist, n - 1);
//	cout << "median is:" << median << endl;
//	this->ptr_md = median; // radius
//
//	// split data
//	//partition matrix of distances to inner and outer points according to the median distance
//	int count_inner = 0;
//	int count_outter = 0;
//
//	for (int i = 0; i < (n - 1); i++) {
//
//		if (*(dist + i) >= median) { //distances[i] !=0.0 gia na vgazo ekso to vantage point
//			*(outterMatrix + count_outter) = *(indexMatrix + i);
//			count_outter++;
//		} else {
//			*(innerMatrix + count_inner) = *(indexMatrix + i);
//			count_inner++;
//		}
//	}
//	cout << "Loipon ta kanamae split!" << endl;
//
//	for (int i = 0; i < count_inner; i++) {
//		cout << "index inner : " << *(innerMatrix + i) << endl;
//	}
//
//	cout << "Loipon ta kanamae split!" << endl;
//	for (int i = 0; i < count_outter; i++) {
//		cout << "outer inner : " << *(outterMatrix + i) << endl;
//	}
//	// delete distance
//	free(dist);
//
//	// create 2 vptree obj
//	vptree in(this->x * 10 + 1);
//	vptree out(this->x * 10 + 2);
//
//	// set inner,outer pointers
//	this->ptr_in = &in;
//	this->ptr_out = &out;
//
//	// call buildVPTREE 2x
//
//	cilk_spawn  this->ptr_in->buildvpTREE(this->data, count_inner, d, innerMatrix);
//	this->ptr_out->buildvpTREE(this->data, count_outter, d, outterMatrix);
//	cilk_sync;
//
//	//free memory
//	free(innerMatrix);
//	free(outterMatrix);
//	free(indexMatrix);
//}
//
//void vptree::calcDistanceMatrix(double *distance, int size, int *index) {
//
//	for (int i = 0; i < size; i++) {
//		*(distance + i) = this->calculateDistance(
//				this->data + (*(index + i)) * d);
//	}
//}
//
//// This function calculates distances between tow points
//double vptree::calculateDistance(double *a) {
//	double sum = 0;
//	for (int i = 0; i < d; i++) {
//		sum = sum + pow(*(a + i) - *(this->ptr_vp + i), 2);
//	}
//	return sqrt(sum);
//}
//
//void vptree::printData() {
//	for (int i = 0; i < this->n; ++i) {
//		cout << i << ": ";
//		for (int j = 0; j < this->d; ++j) {
//			cout << *(this->data + i * this->d + j) << " , ";
//		}
//		cout << endl;
//	}
//}
//
//void vptree::printDataWithIndex(int *index) {
//	for (int i = 0; i < this->n; ++i) {
//		cout << i << ": ";
//		for (int j = 0; j < this->d; ++j) {
//			cout << *(this->data + *(index + i) * this->d + j) << " , ";
//		}
//		cout << endl;
//	}
//}
//
//// Standard partition process of QuickSort().
//// It considers the last element as pivot
//// and moves all smaller element to left of
//// it and greater elements to right
//int partition(double arr[], int l, int r) {
//	double x = arr[r];
//	int i = l;
//	for (int j = l; j <= r - 1; j++) {
//		if (arr[j] <= x) {
//			swap(arr[i], arr[j]);
//			i++;
//		}
//	}
//	swap(arr[i], arr[r]);
//	return i;
//}
//// This function returns k'th smallest
//// element in arr[l..r] using QuickSort
//// based method.  ASSUMPTION: ALL ELEMENTS
//// IN ARR[] ARE DISTINCT
//double kthSmallest(double arr[], int l, int r, int k) {
//	// If k is smaller than number of
//	// elements in array
//	if (k > 0 && k <= r - l + 1) {
//
//		// Partition the array around last
//		// element and get position of pivot
//		// element in sorted array
//		int index = partition(arr, l, r);
//
//		// If position is same as k
//		if (index - l == k - 1)
//			return arr[index];
//
//		// If position is more, recur
//		// for left subarray
//		if (index - l > k - 1)
//			return kthSmallest(arr, l, index - 1, k);
//
//		// Else recur for right subarray
//		return kthSmallest(arr, index + 1, r, k - index + l - 1);
//	}
//	// If k is more than number of
//	// elements in array
//	return INT_MAX;
//}
////find median
//double findMedian(double *distances, int sizeofDistances) {
//	int n1, n2;
//	double median;
//	double tempDist[sizeofDistances];
//	for (int i = 0; i < sizeofDistances; i++) {
//		tempDist[i] = *(distances + i);
//	}
//	if (sizeofDistances % 2 == 0) {
//		n1 = (sizeofDistances + 2) / 2;
//		n2 = sizeofDistances / 2;
//		median = (kthSmallest(tempDist, 0, sizeofDistances - 1, n1)
//				+ kthSmallest(distances, 0, sizeofDistances - 1, n2)) / 2.0;
//	} else {
//		median = kthSmallest(tempDist, 0, sizeofDistances - 1,
//				(sizeofDistances + 1) / 2);
//	}
//	return median;
//}
//
//vptree * vptree::getInner() {
//	return this->ptr_in;
//}
//
//vptree * vptree::getOuter(vptree * T) {
//	return this->ptr_out;
//}
//// return radius
//double vptree::getMD(vptree * T) {
//	return this->ptr_md;
//}
//
////epistrefei ti thesi mnimis tou vantage point
//double * vptree::getVP(vptree * T) {
//	return this->ptr_vp;
//}
////epistrefei to idx ston pinaka mou
//int vptree::getIDX(vptree * T) {
//	return this->ptr_idx;
//}
//
//void vptree::setInner(vptree * T) {
//	this->ptr_in;
//}
//
//void vptree::setOuter(vptree * T) {
//	this->ptr_out;
//}
//
//void vptree::setMD(vptree * T) {
//	this->ptr_md;
//}
//
//void vptree::setVP(vptree * T) {
//	this->ptr_vp;
//}
//void vptree::setIDX(int index) {
//	this->ptr_idx = index;
//}
