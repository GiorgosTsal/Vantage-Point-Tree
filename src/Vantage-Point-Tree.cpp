//============================================================================
// Name        : Vantage-Point-Tree.cpp
// Author      : Giorgos Tsalidis
// Version     :
// Copyright   : Your copyright notice
// Description : Vantage Point Tree in C++
//============================================================================

#include <iostream>
#include <cstdlib>
#include <tgmath.h>
#include <cmath>
#include <climits>
#include <iomanip>

using namespace std;
//na valo sto telos dunamika na vazei to n kai to d
const int n = 10, d = 2;


// for testing and evaluating porpuses
//na thumitho na ton valo float
int myArray[n][d] = {
    { 10, 4 },
    { 5, 8 },
    { 6, 11 },
    { 4, 4 },
    { 5, 5 },
    { 16, 7 },
    { 7, 7 },
    { 8, 11 },
    { 9, 1 },
    { 3, 1 } //assume this point(last point) as vantage point
};


// This function calculates distances between tow points
float calculateDistance(int a[2], int b[2])
{
	float sum = 0;
	for (int i = 0; i < d; i++) {
		sum = sum + pow(a[i] - b[i], 2);
	}
	return sqrt(sum);
}
// Standard partition process of QuickSort().
// It considers the last element as pivot
// and moves all smaller element to left of
// it and greater elements to right
int partition(float arr[], int l, int r)
{
    float x = arr[r];
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
float kthSmallest(float arr[], int l, int r, int k)
{
//	for (int i = 0; i < 9; ++i) {
//		 cout << "to array stin kthSmallest einai: " << arr[i] <<endl;
//	}
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
//find median
float findMedian(float distances[], int sizeofDistances){
	 int n1, n2;
	 float median;
	 if (sizeofDistances % 2 == 0) {
	         n1 = (sizeofDistances + 2) / 2;
	         n2 = sizeofDistances / 2;
	         median = (kthSmallest(distances, 0, sizeofDistances - 1, n1) + kthSmallest(distances, 0, sizeofDistances - 1, n2)) / 2.0;
	 }
	 else {
			 median = kthSmallest(distances, 0, sizeofDistances - 1, (sizeofDistances+1)/2 );
			 cout << "MAKIS:" <<median<<endl;

	 }
	 return median;
}
//populate array with random floats numbers
void populateArray(float X[n][d]){
	  for (int i = 0; i < n; i++) {
	        for (int j = 0; j < d; j++) {
	            X[i][j] = rand()/float(RAND_MAX)*24.f+1.f;	//rand() % 100;
	        }
	    }
}

class VPtree
{
  public:


};

VPtree buildVPtree(){
	VPtree tree;
	return tree;
}

// param <name="idxOfDataset">indexes to a set of n points in d dimensions with coordinates dataset(1:n,1:d)
// param <name="idxOfVP"> the index of the vantage point in the original set
void buildVPtree(int idxOfDataset[], int datasetSize){
	int idxOfvantagePoint =idxOfDataset[datasetSize-1];//theto os vantage point to last point tou matrix
	cout << "to index tou NEW vantage point ston original pinaka einai: "<<idxOfvantagePoint<<endl;
	for(int i = 0; i < datasetSize; ++i){
		cout << "mesa stin sunartisi to innerIdx["<<i<<"] einai : "<< idxOfDataset[i] <<endl;
	}
	if (datasetSize==0) {
		//teleionei to build tou binary tree
	} else {
		//find distance between given vantage point and all other points of the dataset

		int nVantagePoint[d];
		for (int j = 0; j < d; j++) {
			nVantagePoint[j] = myArray[idxOfvantagePoint][j];//apothikeuo to simeio kanontas epanalipsi sto row gia na paro tis times ton dimensions (eg (X,Y)=(2,12))
		        cout <<"To nVantage Point einai: " << nVantagePoint[j] << endl;
		}
		int nPointToCalcDistance[d];
		float distances2[datasetSize-1], tempDistences2[datasetSize-1];
		 //Calculate distances from vantage point to all other points


		for (int i = 0; i < datasetSize-1; i++) { //mexri -1 giati panta theto os vantage point to last point tou matrix
			for (int j = 0; j < d; j++) {
				nPointToCalcDistance[j] = myArray[idxOfDataset[i]][j];
			//	cout << "To nPointToCalcDistance [" << j << "] einai : "<< nPointToCalcDistance[j] << endl;
			}
			distances2[i] = calculateDistance(nPointToCalcDistance, nVantagePoint);
			tempDistences2[i] = distances2[i];
			cout << "To distances2 [" << i << "] einai : "<< distances2[i] << endl;
		}
		//find median of the distances matrix
		int sizeoftempDistances2 = sizeof(tempDistences2) / sizeof(tempDistences2[0]);
	//	float median2 = findMedian(tempDistences2, sizeoftempDistances2);
		//cout << "to median2 pou gurnaei i findMedian(tempDistences2) einai: " << median2 <<endl;

		//partition matrix of distances to inner and outer points according to the median distance
	}

}

int main()
{
    float X[n][d];
    int idxOfX[n];
    populateArray(X);
//Block to check the values of X matrix
//    for (int i = 0; i < n; i++) {
//   	        for (int j = 0; j < d; j++) {
//   	            cout << "To X["<< i << "]["<< j << "] einai: "      <<X[i][j] << endl;
//   	        }
//   	     cout <<  endl;
//   	    }
// uncomment for debug

    //Hold the indexes of my X matrix where my points stored
    for (int i = 0; i < n; i++) {
    	idxOfX[i] = i;
    }

    float distances[n-1], tempDistances[n-1]; //compare with the
    int idxOfdistances[n-1];
    int pointToCalcDistance[d];
    int vantagePoint[d];
    int idxOfVantagePoint = n - 1;



    for (int j = 0; j < d; j++) {
        vantagePoint[j] = myArray[idxOfVantagePoint][j];//apothikeuo to simeio kanontas epanalipsi sto row gia na paro tis times ton dimensions (eg (X,Y)=(2,12))
        cout <<"To Vantage Point einai: " << vantagePoint[j] << endl;
    }

    //Calculate distances from vantage point to all other points
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < d; j++) {
        	pointToCalcDistance[j] = myArray[i][j];
        //    cout << "To pointToCalcDistance [" << j << "] einai : "<< pointToCalcDistance[j] << endl;
        }
        distances[i] = calculateDistance(pointToCalcDistance, vantagePoint);
        tempDistances[i] = distances[i];
        cout << "To distances [" << i << "] einai : "<< distances[i] << endl;
    }

    int n = sizeof(distances) / sizeof(distances[0]);
    int sizeoftempDistances = sizeof(distances) / sizeof(distances[0]);
    float median = findMedian(tempDistances, sizeoftempDistances);
    cout << "to median pou gurnaei i findMedian(tempDistences) einai: " << median <<endl;


 //   int distancesLength = sizeof(distances)/sizeof(distances[0]);
    int idxOfdistancesLength = sizeof(idxOfdistances)/sizeof(idxOfdistances[0]);

    //partition matrix of distances to inner and outer points according to the median distance
    int count_inner = 0 ;
    int count_outter = 0 ;
    int outerIdx[n/2 +1 ] , innerIdx[n/2 + 1];


    for (int i = 0;  i < idxOfdistancesLength; ++i) {
    	if (distances[i] >= median && distances[i] != 0.0) { //TODO na valo k distances[i] !=0.0 gia na vgazo ekso to vantage point
    		outerIdx[count_outter] = idxOfX[i];
    		cout << "========OUTER [" << count_outter << "] einai : "<< outerIdx[count_outter] << " kai to distances["<< i <<"] einai: " << distances[i] << " kai to pragmatiko simeio einai to: (" << myArray[idxOfX[i]][0] << ","<< myArray[idxOfX[i]][1] << ")=============" << endl;
    		count_outter++;
		} else if(distances[i] != 0.0){
			innerIdx[count_inner] = idxOfX[i];
			cout << "INNER [" << count_inner << "] einai : "<< innerIdx[count_inner]<< " kai to distances["<< i <<"]  einai: " << distances[i] << " kai to pragmatiko simeio einai to: (" << myArray[idxOfX[i]][0] << ","<< myArray[idxOfX[i]][1] << ")" << endl;
			count_inner++;
		}
	}
    cout << "INNER einai episis kai to Vantage Point."<<  endl;

//    cout << "to size tou innerIdx prin to kaleso: " <<sizeof(innerIdx)/sizeof(innerIdx[0]) <<endl;
    for(int i = 0; i < sizeof(innerIdx)/sizeof(innerIdx[0]); ++i){
    	cout << "to innerIdx["<<i<<"] einai : "<< innerIdx[i] <<endl;
    }

    //int innerIdxLength = sizeof(innerIdx)/sizeof(innerIdx[0]);
    cout << "==================================END OF FIRST ITERATION==================================================================" << endl ;

    cout << "to count_inner inee: " <<count_inner <<endl;
   // buildVPtree(innerIdx,count_inner);
    return 0;
}
