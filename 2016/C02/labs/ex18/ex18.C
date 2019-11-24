#include "Matrix.h"
#include <iostream>

using namespace std;

int main(){
	{//alinea a
		double **m1 = new double* [2];
		m1[0] = new double [2];
		m1[1] = new double [2];

		m1[0][0] = 2.;
		m1[1][0] = 5.;
		m1[0][1] = 10.;
		m1[1][1] = 7.;

		double m1_tr = Trace(m1, 2);

		cout << m1_tr << endl << endl;

		deleteM(m1, 2);
	}

	{//alinea b
		double **m2 = new double* [2];
		m2[0] = new double [3];
		m2[1] = new double [3];

		m2[0][0] = 2.;
		m2[1][0] = 3.;
		m2[0][1] = 10.;
		m2[1][1] = 2.;
		m2[0][2] = 5.;
		m2[1][2] = 7.;

		double *m2_row = Mrow(2, m2, 3);

		for (int i = 0; i < 3; ++i)
			cout << m2_row[i] << " ";
		cout << endl << endl;

		delete[] m2_row;
		deleteM(m2, 2);
	}

	{//alinea c
		double **m3 = new double* [2];
		m3[0] = new double [3];
		m3[1] = new double [3];

		m3[0][0] = 2.;
		m3[1][0] = 3.;
		m3[0][1] = 10.;
		m3[1][1] = 2.;
		m3[0][2] = 5.;
		m3[1][2] = 7.;

		double *vec = new double [3] {2, 5, 7};

		double *res = Mmultiply(m3, 2, 3, vec);

		for (int i = 0; i < 2; ++i)
			cout << res[i] << " ";
		cout << endl << endl;

		delete[] res;
		delete[] vec;
		deleteM(m3, 2);	
	}

	{//alinea d
		double **m4 = new double* [2];
		m4[0] = new double [3];
		m4[1] = new double [3];

		m4[0][0] = 2.;
		m4[1][0] = 3.;
		m4[0][1] = 10.;
		m4[1][1] = 2.;
		m4[0][2] = 5.;
		m4[1][2] = 7.;

		double **m5 = new double* [3];
		m5[0] = new double [3];
		m5[1] = new double [3];
		m5[2] = new double [3];

		m5[0][0] = 5.;
		m5[0][1] = 10.;
		m5[0][2] = 15.;
		m5[1][0] = 1.;
		m5[1][1] = 1.;
		m5[1][2] = 1.;
		m5[2][0] = 3.;
		m5[2][1] = 5.;
		m5[2][2] = 4.;

		double **res = new double* [2];
		res[0] = new double [3];
		res[1] = new double [3];
		res[2] = new double [3];

		for (int i = 0; i < 3; ++i)
			res[i] = Mmultiply(m4, 2, 3, m5[i]);

		printM(res, 2, 3);

		deleteM(res, 2);
		deleteM(m5, 3);	
		deleteM(m4, 2);	
	}

	return 0;
}