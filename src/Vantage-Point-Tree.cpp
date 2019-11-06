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

//ctrl + shift + / <--NUM_KEYPAD_DIVIDE gia collapse
// for testing and evaluating porpuses
//na thumitho na ton valo float
float myArray[n][d] = {
    { 10.0, 4.0 },
    { 5.0, 8.0 },
    { 6.0, 11.0 },
    { 4.0, 4.0 },
    { 5.0, 5.0 },
    { 16.0, 7.0 },
    { 7.0, 7.0 },
    { 8.0, 11.0 },
    { 9.2, 1.0 },
    { 3.1, 1.0 } //assume this point(last point) as vantage point
};


// This function calculates distances between tow points
float calculateDistance(float a[2], float b[2])
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
	int idxOfVP;
	float vantagePoint[d];
	float median;
	int *idxOfOuter, *idxOfInner;

  public:
	VPtree* buildVPtree(int idxOfInnerDataset[], int innerSize, int idxOfOuterDataset[], int outerSize){
		VPtree T;
		VPtree * T_ptr;
		T_ptr = &T;
		int outerIdx2[n/2 +1 ] , innerIdx2[n/2 + 1];
		int count_inner2 = 0 ;
		int count_outter2 = 0 ;
		int idxOfvantagePoint =idxOfInnerDataset[innerSize-1];//theto os vantage point to last point tou matrix

		cout << "TO innerSize EINAI: " << innerSize <<"  KAI TO outerSize EINAI" << outerSize << endl;
		if (innerSize <= 1 && outerSize <= 1) {
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~telos olon~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" <<endl <<endl<<endl <<endl;
		} else {
			if (innerSize <= 1) {
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~telos mono tou inner~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" <<endl<<endl <<endl;
			} else {
				//mia gia to calculate tou inner dataset
					cout << "to index tou NEW vantage point ston original pinaka einai: "<<idxOfvantagePoint<<endl;
					for(int i = 0; i < innerSize; ++i){
						cout << "mesa stin sunartisi to innerIdx["<<i<<"] einai : "<< idxOfInnerDataset[i] <<endl;
					}

						//Calculate distances from vantage point to all other points of the given dataset
						float nVantagePoint[d];
						for (int j = 0; j < d; j++) {
							nVantagePoint[j] = myArray[idxOfvantagePoint][j];//apothikeuo to simeio kanontas epanalipsi sto row gia na paro tis times ton dimensions (eg (X,Y)=(2,12))
								cout <<"To nVantage Point einai: " << nVantagePoint[j] << endl;
						}
						float nPointToCalcDistance[d];
						float distances2[innerSize-1], tempDistences2[innerSize-1];
						for (int i = 0; i < innerSize-1; i++) { //mexri -1 giati panta theto os vantage point to last point tou matrix
							for (int j = 0; j < d; j++) {
								nPointToCalcDistance[j] = myArray[idxOfInnerDataset[i]][j];
								//cout << "To nPointToCalcDistance [" << j << "] einai : "<< nPointToCalcDistance[j] << endl;
							}
							distances2[i] = calculateDistance(nPointToCalcDistance, nVantagePoint);
							tempDistences2[i] = distances2[i];
							cout << "To distances2 [" << i << "] einai : "<< distances2[i] << endl;
						}


						//Find median of the distances matrix
						int sizeoftempDistances2 = sizeof(tempDistences2) / sizeof(tempDistences2[0]);
						//hold the indexes of the distances
						int idxOfDistances2[innerSize-1];
						float median2 = findMedian(tempDistences2, sizeoftempDistances2);
						cout << "to median2 pou gurnaei i findMedian(tempDistences2) einai: " << median2 <<endl;


						//Partition matrix of distances to inner and outer points according to the median distance
						int idxOfdistances2Length = sizeof(idxOfDistances2)/sizeof(idxOfDistances2[0]);
						for (int i = 0;  i < idxOfdistances2Length; ++i) {
							if (distances2[i] >= median2 && distances2[i] != 0.0) { // distances[i] !=0.0 gia na vgazo ekso to vantage point
								outerIdx2[count_outter2] = idxOfInnerDataset[i];
								cout << "========OUTER2 [" << count_outter2 << "] einai : "<< outerIdx2[count_outter2] << " kai to distances2["<< i <<"] einai: " << distances2[i] << " kai to pragmatiko simeio einai to: ("
										<< myArray[idxOfInnerDataset[i]][0] << ","<< myArray[idxOfInnerDataset[i]][1] << ")=============" << endl;
								count_outter2++;
							} else if(distances2[i] != 0.0){
								innerIdx2[count_inner2] = idxOfInnerDataset[i];
								cout << "INNER2 [" << count_inner2 << "] einai : "<< innerIdx2[count_inner2]<< " kai to distances2["<< i <<"]  einai: " << distances2[i] << " kai to pragmatiko simeio einai to: ("
										<< myArray[idxOfInnerDataset[i]][0] << ","<< myArray[idxOfInnerDataset[i]][1] << ")" << endl;
								count_inner2++;
							}
						}
						//edo pou exo ta stoixeia mou : vp, median, outer iner indexes kano populate to antikeimeno mou me ta antistoixa
						this->idxOfVP = idxOfvantagePoint;
						for (int j = 0; j < d; j++) {
							this->vantagePoint[j] = nVantagePoint[j];
							cout <<"To this->vantagePoint[j] einai: " << this->vantagePoint[j] << endl;
						}
						this->median = median2;
						this->idxOfInner = innerIdx2;
						this->idxOfOuter = outerIdx2;
						cout << "To this->idxOfVP einai: " << this->idxOfVP <<endl;
						cout << "To this->median einai: " << this->median << " eno to official median2 einai " << median2 <<endl;
						cout << "To *this->idxOfInner einai: " << *this->idxOfInner << " eno to official innerIdx2 einai " << *innerIdx2 <<endl;
						cout << "To *this->idxOfOuter einai: " << *this->idxOfOuter << " eno to official outerIdx2 einai " << *outerIdx2 <<endl;



						cout << "INNER einai episis kai to Vantage Point."<<  endl;
						cout << "--------------ARXI ANADROMIS GIA TA PROTA INNER1------------------------"<<  endl <<endl <<endl <<endl;
						buildVPtree(innerIdx2, count_inner2, outerIdx2, count_outter2);
						cout << "--------------TELOS ANADROMIS GIA TA PROTA INNER INNER1------------------------"<<  endl<<endl <<endl <<endl;
					}
			//Ypologizo ta antistoixa gia ta outer
			if (outerSize <= 1) {
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~telos mono tou outer~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl<<endl <<endl<<endl <<endl;
			} else {
				idxOfvantagePoint =idxOfOuterDataset[outerSize-1];//theto os vantage point to last point tou matrix
				count_inner2 = 0 ;
				count_outter2 = 0 ;

				cout << "to index tou NEW vantage point ston original pinaka einai: "<<idxOfvantagePoint<<endl;
				for(int i = 0; i < outerSize; ++i){
					cout << "mesa stin sunartisi to innerIdx["<<i<<"] einai : "<< idxOfOuterDataset[i] <<endl;
				}
				if (outerSize<=1) {
					cout << "teleiosame me sena!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl<<endl <<endl<<endl <<endl;
					//teleionei to build tou binary tree
				} else {
					//find distance between given vantage point and all other points of the dataset

					float nVantagePoint[d];
					for (int j = 0; j < d; j++) {
						nVantagePoint[j] = myArray[idxOfvantagePoint][j];//apothikeuo to simeio kanontas epanalipsi sto row gia na paro tis times ton dimensions (eg (X,Y)=(2,12))
							cout <<"To nVantage Point einai: " << nVantagePoint[j] << endl;
					}
					float nPointToCalcDistance[d];
					float distances2[outerSize-1], tempDistences2[outerSize-1];
					 //Calculate distances from vantage point to all other points


					for (int i = 0; i < outerSize-1; i++) { //mexri -1 giati panta theto os vantage point to last point tou matrix
						for (int j = 0; j < d; j++) {
							nPointToCalcDistance[j] = myArray[idxOfOuterDataset[i]][j];
							cout << "To nPointToCalcDistance [" << j << "] einai : "<< nPointToCalcDistance[j] << endl;
						}
						distances2[i] = calculateDistance(nPointToCalcDistance, nVantagePoint);
						tempDistences2[i] = distances2[i];
						cout << "To distances2 [" << i << "] einai : "<< distances2[i] << endl;
					}
					//find median of the distances matrix
					int sizeoftempDistances2 = sizeof(tempDistences2) / sizeof(tempDistences2[0]);
					//hold the indexes of the distances
					int idxOfDistances2[innerSize-1];
					float median2 = findMedian(tempDistences2, sizeoftempDistances2);
					cout << "to median2 pou gurnaei i findMedian(tempDistences2) einai: " << median2 <<endl;

					//partition matrix of distances to inner and outer points according to the median distance
					int idxOfdistances2Length = sizeof(idxOfDistances2)/sizeof(idxOfDistances2[0]);

					//partition matrix of distances to inner and outer points according to the median distance

					for (int i = 0;  i < idxOfdistances2Length+1; ++i) {

						if (distances2[i] >= median2 && distances2[i] != 0.0) { // distances[i] !=0.0 gia na vgazo ekso to vantage point
							outerIdx2[count_outter2] = idxOfOuterDataset[i];
							cout << "========OUTER2 [" << count_outter2 << "] einai : "<< outerIdx2[count_outter2] << " kai to distances2["<< i <<"] einai: " << distances2[i] << " kai to pragmatiko simeio einai to: ("
									<< myArray[idxOfOuterDataset[i]][0] << ","<< myArray[idxOfOuterDataset[i]][1] << ")=============" << endl;
							count_outter2++;
						} else if(distances2[i] != 0.0){
							innerIdx2[count_inner2] = idxOfOuterDataset[i];
							cout << "INNER2 [" << count_inner2 << "] einai : "<< innerIdx2[count_inner2]<< " kai to distances2["<< i <<"]  einai: " << distances2[i] << " kai to pragmatiko simeio einai to: ("
									<< myArray[idxOfOuterDataset[i]][0] << ","<< myArray[idxOfOuterDataset[i]][1] << ")" << endl;
							count_inner2++;
						}
					}
					cout << "INNER einai episis kai to Vantage Point."<<  endl;


					this->idxOfVP = idxOfvantagePoint;
					for (int j = 0; j < d; j++) {
						this->vantagePoint[j] = nVantagePoint[j];
						cout <<"To this->vantagePoint[j] einai: " << this->vantagePoint[j] << endl;
					}
					this->median = median2;
					this->idxOfInner = innerIdx2;
					this->idxOfOuter = outerIdx2;
					cout << "To this->idxOfVP einai: " << this->idxOfVP <<endl;
					cout << "To this->median einai: " << this->median << " eno to official median2 einai " << median2 <<endl;
					cout << "To *this->idxOfInner einai: " << *this->idxOfInner << " eno to official innerIdx2 einai " << *innerIdx2 <<endl;
					cout << "To *this->idxOfOuter einai: " << *this->idxOfOuter << " eno to official outerIdx2 einai " << *outerIdx2 <<endl;

					cout << "--------------ARXI ANADROMIS GIA TA PROTA INNER2------------------------"<<  endl <<endl<<endl <<endl;
					buildVPtree(innerIdx2, count_inner2, outerIdx2, count_outter2);
					cout << "--------------TELOS ANADROMIS GIA TA PROTA INNER INNER2------------------------"<<  endl<<endl<<endl <<endl;

				}
			}
		}
		//fill obj T with median, vp, in kai out klp
		return T_ptr;
	}
};



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
    float pointToCalcDistance[d];
    float vantagePoint[d];
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


    int idxOfdistancesLength = sizeof(idxOfdistances)/sizeof(idxOfdistances[0]);

    //partition matrix of distances to inner and outer points according to the median distance
    int count_inner = 0 ;
    int count_outter = 0 ;
    int outerIdx[n/2 +1 ] , innerIdx[n/2 + 1];


    for (int i = 0;  i < idxOfdistancesLength; ++i) {
    	if (distances[i] >= median && distances[i] != 0.0) { //distances[i] !=0.0 gia na vgazo ekso to vantage point
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



    //int innerIdxLength = sizeof(innerIdx)/sizeof(innerIdx[0]);
    cout << "==================================END OF FIRST ITERATION==================================================================" << endl << endl << endl;

    cout << "==================================BEGGINING OF FIRST INNER AND OUTTER PARTITION============================================" <<endl;

    VPtree vptree;
    vptree.buildVPtree(innerIdx,count_inner, outerIdx,count_outter);

    return 0;
}

