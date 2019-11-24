#include <iostream>
#include <cstdlib>

using namespace std;

int*** fintv(int row, int col, int dpt, int val){

	int i, j, k;

	if(row <=0 || col <=0 || dpt <= 0){
		cout << "Please insert only positive integers." << endl;
		exit (-1);
	}

	int*** v = new int**[row];

	for(i=0; i<row; ++i){
		v[i] = new int*[col];

		for(j=0; j<col; ++j){
			v[i][j] = new int[dpt];

			for(k=0; k<dpt; ++k)
				v[i][j][k] = val;
		}
	}

	return v;
}


void print(int*** v, int row, int col, int dpt){

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


void deletev(int*** v, int row, int col){

	int i, j;

	for(i=0; i<row; ++i){
		for(j=0; j<col; ++j)
			delete[] v[i][j];

		delete[] v[i];
	}

	delete[] v;
}