#include <iostream>

using namespace std;

//Multiplicar matriz por vetor coluna
void Mmultiply(double** mx, double* vr, int m, int n, double* pt){
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			pt[i] += mx[i][j] * vr[j];
		}
	}
}

//Print da matriz
void printM(double** mx, int row, int col){

	for(int j=0; j<row; ++j){
		for(int i=0; i<col; ++i)
			cout << mx[i][j] << " ";

		cout << endl;
	}
}


//Apagar matrizes
void deleteM(double** mx, int row){

	for(int i=0; i<row; ++i)
		delete[] mx[i];

	delete[] mx;
}