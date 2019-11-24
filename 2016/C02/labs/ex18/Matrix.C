#include <iostream>

using namespace std;

//Calcular traço de uma matriz
double Trace(double** mx, int n){
	double trace = 0.;

	for (int i = 0; i < n; ++i)
		trace += mx[i][i];

	return trace;
}

//Retornar elementos da linha i de uma matriz mxn
double* Mrow(int i, double** mx, int n){
	double *row = new double [n];

	i--;

	for (int j = 0; j < n; ++j)
		row[j] = mx[i][j];

	return row;
}

//Multiplicar matriz por vetor coluna
double* Mmultiply(double** mx, int m, int n, double* v){
	double *res = new double [m] {0};

	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			res[i] += mx[i][j] * v[j];
		}
	}

	return res;
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