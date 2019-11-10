//============================================================================
// Name        : main.cpp
// Author      : Giorgos Tsalidis
// Version     :
// Copyright   : Your copyright notice
// Description : Vantage Point Tree in C++
//============================================================================

#include <iostream>
#include <bits/stdc++.h>
#include <sys/time.h>

#include "../inc/vptree.h"

using namespace std;

const int n = 10, d = 2;
void populateArray(double *array){
	  for (int i = 0; i < n; i++) {
			for (int j = 0; j < d; j++) {
				*(array + i*d + j) = rand()/double(RAND_MAX)*24.f+1.f;	//rand() % 100;
			}
	  }
}
void printArray(double *array)
{
    cout << __func__ << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << i << ": ";
        for (int j = 0; j < d; ++j)
            cout <<  *(array + i*d + j)<< endl;
       cout << endl;
    }
}




int main()
{

	struct timeval start, end;
	// start timer.
	gettimeofday(&start, NULL);
	// unsync the I/O of C and C++.
	ios_base::sync_with_stdio(false);

	double *X = (double *)malloc(n * d * sizeof(double));
	populateArray(X);

	printArray(X);

	vptree T(3);
    //call of buildvp
	T.buildvp(X, n, d);



    double *array = T.getVP(&T);

    for (int j = 0; j < d; ++j){
    	cout <<  *(array + j)<< endl;
    }


    free(X);
    // stop timer.
    gettimeofday(&end, NULL);
     // Calculating total time taken by the program.
 	double time_taken;

 	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
 	time_taken = (time_taken + (end.tv_usec -
 							  start.tv_usec)) * 1e-6;

 	cout << "Time taken by program is : " << fixed
 		 << time_taken << setprecision(6);
 	cout << " sec" << endl;
	return 0;
}

