#include <iostream>
#include <cstdlib>

using namespace std;

double*** fdoublev(int row, int col, int dpt, int val){
	
	int i, j, k;

	if(row <=0 || col <=0 || dpt <= 0){
		cout << "Please insert only positive integers." << endl;
		exit (-1);
	}

	double*** v = new double**[row];

	for(i=0; i<row; ++i){
		v[i] = new double*[col];

		for(j=0; j<col; ++j){
			v[i][j] = new double[dpt];

			for(k=0; k<dpt; ++k)
				v[i][j][k] = val;
		}
	}

	return v;
}


void print(double*** v, int row, int col, int dpt){

	int i, j, k;

	for(k=0; k<dpt; ++k){
		for(i=0; i<row; ++i){
			for(j=0; j<col; ++j)
				cout << v[i][j][k] << " ";

			cout << endl;
		}

		cout << endl;
	}

	cout << endl;
}


void deletev(double*** v, int row, int col){

	int i, j;

	for(i=0; i<row; ++i){
		for(j=0; j<col; ++j)
			delete[] v[i][j];

		delete[] v[i];
	}

	delete[] v;
}