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

using namespace std;

const int n = 10, d=2;

// for testing and evaluating porpuses
int myArray[n][d] =
   {
       {1,1},
	   {2,2},
	   {3,3},
	   {4,4},
	   {5,5},
	   {6,6},
	   {7,7},
	   {8,8},
       {9,9},
	   {10,10}
   };

float calculateDistance(int a[2], int b[2]){
	cout << "sakis: " <<a[0] << "makis: " << a[1]<< endl;
	float sum = 0;
	for (int i = 0; i < d ; i++) {
		sum = sum + pow( a[i] - b[i] , 2);
	}
	cout <<"to real sum einai:"<<  sum <<endl;
	return sqrt(sum);
}



int main() {
	int X[n][d];
	for (int i = 0; i < n ; i++)
		{
			for (int j = 0; j < d ; j++)
					{
						X [i][j]= rand() % 100;
					}
		}
	for (int i = 0; i < n ; i++)
			{
				for (int j = 0; j < d ; j++)
						{
							 cout << X[i][j] << " ";
						}
			cout << "index" << i << " "  << endl;
			}


	float distances[n-1];
	int matrix[d];
	int vantagePoint[d];
	for (int j = 0; j < d; j++) {
		vantagePoint[j] = X[n-1][j]; //apothikeuo to simeio kanontas epanalipsi sto row gia na paro tis times ton dimensions (eg (X,Y)=(2,12))
			}
	for ( int i = 0;  i < n-1; i++) {
		for (int j = 0; j < d; j++) {
		//	matrix[j] = X[i][j];
			matrix[j] = myArray[i][j];
		}
		cout << "sakis prin fugei: " << matrix[0] << "makis prin fugei: " << matrix[1]  << endl;
		distances[i] =  calculateDistance(matrix, vantagePoint );
		cout <<"Distances["<<i<<"]: " << distances[i] << endl;
	}

	//cout << n << endl; // prints !!!Hello There!!!
	return 0;
}
