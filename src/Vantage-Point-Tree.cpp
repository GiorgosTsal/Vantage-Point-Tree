//============================================================================
// Name        : Vantage-Point-Tree.cpp
// Author      : Giorgos Tsalidis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <tgmath.h>
#include <cmath>
#include <climits>
#include <iomanip>
#include <bits/stdc++.h>  //na thumitho na to vgalo

using namespace std;
//na valo sto telos dunamika na vazei to n kai to d
const int n = 10, d = 2;

//todos
//1) pinaka me index ton simeion mou
//2) ta distances
//3) na sugkrino tis apo staseis me to median k na ta kano storage se 2 neous pinakes mesa k ekso
//   me ta mikrotera k megalutera
//3) to programma tha teleionei otan to array apo ta distances tha einai keno

// for testing and evaluating porpuses
//na thumitho na ton valo double
int myArray[n][d] = {
    { 10, 4 },  //	0	12	1
    { 5, 8 },//	1	34	1
    { 6, 11 },//	2	235	0
    { 4, 4 },//	3	435	0
    { 5, 5 },//	4	34	1
    { 16, 7 },//	5	1	1
    { 7, 7 },//	6	64	1
    { 8, 11 },
    { 9, 1 },
    { 3, 1 } //assume this point(last point) as vantage point
};

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
int partition(int arr[], int l, int r)
{
    int x = arr[r], i = l;
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
int kthSmallest(int arr[], int l, int r, int k)
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

int main()
{
    int X[n][d];
    int idxOfX[n];
    int idxOfmyArray[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            X[i][j] = rand() % 100;
        }
    }
    for (int i = 0; i < n; i++) {
    	idxOfX[i] = i;
    }
    for (int i = 0; i < n; i++) {
    	idxOfmyArray[i] = i;
       }

    float distances[n - 1];
    int idxOfdistances[n-1];
    int matrix[d];
    int vantagePoint[d];
    for (int j = 0; j < d; j++) {
        //	vantagePoint[j] = X[n-1][j]; //apothikeuo to simeio kanontas epanalipsi sto row gia na paro tis times ton dimensions (eg (X,Y)=(2,12))
        vantagePoint[j] = myArray[n - 1][j];
        cout <<"To Vantage Point einai: " << vantagePoint[j] << endl;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < d; j++) {
            //	matrix[j] = X[i][j];
            matrix[j] = myArray[i][j];
        }
        distances[i] = calculateDistance(matrix, vantagePoint);
        cout << "TO distances [" << i << "] einai : "<< distances[i] << endl;

    //    cout << "Distances[" << i << "]: " << distances[i] << endl;
    }
    for (int i = 0; i < n - 1; i++) {
    		idxOfdistances[i] = i;
        }
//    int plithos = sizeof(distances)/sizeof(distances[0]);
//
//        sort(distances, distances+n);
//        for (int i = 0; i < n - 1; i++) {
//
//             cout << "To sorted distances [" << i << "] einai : "<< distances[i] << endl;
//
//         }

    int n = sizeof(idxOfdistances) / sizeof(distances[0]);

    int n1, n2;
    float median;
    //to find median na to kano me sunartisei pou na to epistrefei
    if (n % 2 == 0) {
        n1 = (n + 2) / 2;
        n2 = n / 2;
     //   cout << "n1: " << n1 << endl;

     //   cout << "n2: " << n2 << endl;
      //  cout << fixed;
     //   cout << setprecision(2);
      //  cout << "n1:Median when k is even is " << kthSmallest(arr, 0, n - 1, n1) << endl;
       // cout << "n2:Median when k is even is " << kthSmallest(arr, 0, n - 1, n2) << endl;
        median = (kthSmallest(idxOfdistances, 0, n - 1, n1) + kthSmallest(idxOfdistances, 0, n - 1, n2)) / 2.0;

        //cout << fixed;
        cout << setprecision(2);
    //    cout << "To median tou distances[] einai : " << median << endl; // einai to r
    }
    else {
        //			int idx = floor(k/2);
        //			k = 5
        //			cout << "idx: "<<idx <<endl;
        //			cout <<"k is: " << k <<endl;
        median = kthSmallest(idxOfdistances, 0, n - 1, (n + 1) / 2);
   //     cout << "Median when k is odd  is " << median;
    }
//    int idxOfMedian[]
//    for (int i = 0; i < sizeof(median)/sizeof(median[0]); ++i) {
//
//	}

    int outer[n/2] , inner[n/2];
    int distancesLength = sizeof(distances)/sizeof(distances[0]);
    cout << "To median tou distances[] pou ehei length " << distancesLength << " einai : " << median << endl;
    int idxOfdistancesLength = sizeof(idxOfdistances)/sizeof(idxOfdistances[0]);
    for (int i = 0;  i < idxOfdistancesLength; ++i) {
    //	int medianFloored = (int) floor(distances[median] + 0.5);
    	int medianFloor = floor(median);
    //	cout << "distances[median] = " << distances[medianFloor] << endl;
    	if (idxOfdistances[i] >= medianFloor) {
    		outer[i] = idxOfX[i];
    		cout << "TO OUTER [" << i << "] einai : "<< outer[i] << " kai to distances[i] einai: " << distances[idxOfX[i]] << " kai to pragmatiko simeio einai to: (" << myArray[idxOfX[i]][0] << ","<< myArray[idxOfX[i]][1] << ")" << endl;

		} else {
			inner[i] = idxOfX[i];
			cout << "TO INNER [" << i << "] einai : "<< inner[i]<< " kai to distances[i] einai: " << distances[idxOfX[i]] << " kai to pragmatiko simeio einai to: (" << myArray[idxOfX[i]][0] << ","<< myArray[idxOfX[i]][1] << ")" << endl;
		}
	}



    return 0;
}
