#ifndef VPTREE_H
#define VPTREE_H

#include <iostream>

using namespace std;

class vptree{



public:
    int x;
    vptree(int x);
    ~vptree();
    int getX();
    int ptr_idx,n,d;
    double *data;

	vptree *ptr_in, *ptr_out;
	double ptr_md, *ptr_vp;



	// ========== LIST OF ACCESSORS


	//! Build vantage-point tree given input dataset X
	/*!

	  \param X      Input data points, stored as [n-by-d] array
	  \param n      Number of data points (rows of X)
	  \param d      Number of dimensions (columns of X)
	  \return The vantage-point tree
	*/
	vptree * buildvp(double *X, int n, int d);
	vptree * buildvpTREE(double *X, int n, int d,int *myIndex);

	//! Return vantage-point subtree with points inside radius
	/*!

	  \param node   A vantage-point tree
	  \return The vantage-point subtree
	*/
	vptree * getInner();

	//! Return vantage-point subtree with points outside radius
	/*!

	  \param node   A vantage-point tree
	  \return The vantage-point subtree
	*/
	vptree * getOuter(vptree * T);

	//! Return median of distances to vantage point
	/*!

	  \param node   A vantage-point tree
	  \return The median distance
	*/
	double getMD(vptree * T);

	//! Return the coordinates of the vantage point
	/*!

	  \param node   A vantage-point tree
	  \return The coordinates [d-dimensional vector]
	*/
	double * getVP(vptree * T);

	//! Return the index of the vantage point
	/*!

	  \param node   A vantage-point tree
	  \return The index to the input vector of data points
	*/
	int getIDX(vptree * T);

	void printData();
	void printDataWithIndex(int *index);
	void calcDistanceMatrix(double *distance,int size, int *index);
	double calculateDistance(double *a);

	void setInner(vptree * T);
	void setOuter(vptree * T);
	void setMD(vptree * T);
	void setVP(vptree * T);
	void setIDX(int index);

};

double findMedian(double *distances, int sizeofDistances);


#endif

