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

using namespace std;

const int n = 10, d = 2;

// for testing and evaluating porpuses
int myArray[n][d] = {
    { 1, 1 },
    { 2, 2 },
    { 3, 3 },
    { 4, 4 },
    { 5, 5 },
    { 6, 6 },
    { 7, 7 },
    { 8, 8 },
    { 9, 9 },
    { 10, 10 }
};

float calculateDistance(int a[2], int b[2])
{
    //cout << "sakis: " <<a[0] << " makis: " << a[1]<< endl;
    float sum = 0;
    for (int i = 0; i < d; i++) {
        cout << "a[i]" << a[i] << endl;
        cout << "b[i]" << b[i] << endl;
        sum = sum + pow(a[i] - b[i], 2);
    }
    cout << "to real sum einai:" << sum << endl;
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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            X[i][j] = rand() % 100;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            // cout << X[i][j] << " ";
            cout << myArray[i][j] << " ";
        }
        cout << "index " << i << " " << endl;
    }

    float distances[n - 1];
    int matrix[d];
    int vantagePoint[d];
    for (int j = 0; j < d; j++) {
        //	vantagePoint[j] = X[n-1][j]; //apothikeuo to simeio kanontas epanalipsi sto row gia na paro tis times ton dimensions (eg (X,Y)=(2,12))
        vantagePoint[j] = myArray[n - 1][j];
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < d; j++) {
            //	matrix[j] = X[i][j];
            matrix[j] = myArray[i][j];
        }
        cout << "sakis prin fugei: " << matrix[0] << " makis prin fugei: " << matrix[1] << endl;
        distances[i] = calculateDistance(matrix, vantagePoint);
        cout << "Distances[" << i << "]: " << distances[i] << endl;
    }

    //cout << n << endl; // prints !!!Hello There!!!

    int arr[] = { 10, 4, 5, 8, 6, 11, 26, 7 };
    //	Doing sizeof( myArray ) will get you the total number of bytes allocated for that array.
    //	You can then find out the number of elements in the array by dividing
    //	by the size of one element in the array: sizeof( myArray[0] )
    int n = sizeof(arr) / sizeof(arr[0]);
    int k;
    int n1, n2;
    k = sizeof(arr) / sizeof(arr[0]);
    cout << "to k einai: " << k << endl;

    if (k % 2 == 0) {
        n1 = (k + 2) / 2;
        n2 = k / 2;
        cout << "n1: " << n1 << endl;

        cout << "n2: " << n2 << endl;
        cout << fixed;
        cout << setprecision(2);
        cout << "n1:Median when k is even is " << kthSmallest(arr, 0, n - 1, n1) << endl;
        cout << "n2:Median when k is even is " << kthSmallest(arr, 0, n - 1, n2) << endl;
        float total = (kthSmallest(arr, 0, n - 1, n1) + kthSmallest(arr, 0, n - 1, n2)) / 2;
        float d = (8 + 7) / 2;

        cout << fixed;
        cout << setprecision(2);
        cout << "total median is: " << total << endl;
        cout << "total median is: " << d << endl;
    }
    else {
        //			int idx = floor(k/2);
        //			k = 5
        //			cout << "idx: "<<idx <<endl;
        //			cout <<"k is: " << k <<endl;
        cout << "Median when k is odd  is " << kthSmallest(arr, 0, n - 1, (k + 1) / 2);
    }

    return 0;
}

