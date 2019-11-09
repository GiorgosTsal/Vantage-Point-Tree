//============================================================================
// Name        : main.cpp
// Author      : Giorgos Tsalidis
// Version     :
// Copyright   : Your copyright notice
// Description : Vantage Point Tree in C++
//============================================================================

#include <iostream>
#include "vptree.h"

using namespace std;

const int n = 100, d = 2;
void populateArray(double *array){
	  for (int i = 0; i < n; i++) {
			for (int j = 0; j < d; j++) {
				*(array + i*d + j) = rand()/double(RAND_MAX)*24.f+1.f;	//rand() % 100;
				*(array + i*d + j) = rand() % 100;
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


	double *X = (double *)malloc(n * d * sizeof(double));
	populateArray(X);


	printArray(X);
    vptree T(3);
    T.buildvp(X, n, d);

    cout << "radius :" <<T.getMD(&T) << endl;
    cout << "index:" <<T.getIDX(&T) << endl;
    cout << "pointer :" << T.getVP(&T)<< endl;
    double *array = T.getVP(&T);

    for (int j = 0; j < d; ++j){
    	cout <<  *(array + j)<< endl;
    }

    cout << "name : " << T.getOuter(&T)->getX()<<endl;

    cout <<"telos programmatos."<<endl;
	return 0;
}

