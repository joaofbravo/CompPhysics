#include "FCmatrixFull.h"
#include "FCmatrixBanded.h"

#include <iostream>

using namespace std;
int main()
{

	double mat[][4]= {
		{1,2,3,4},
		{3,2,1,0},
		{5,2,3,6},
		{1,6,3,8}
	};

	double mat0[][5]= {
		{1,2,3,4,2},
		{2,2,1,0,5},
		{1,2,3,6,1},
		{3,6,3,8,0},
		{2,5,2,8,0}
	};		

	double **M1 = new double*[4];
	for (int i = 0; i < 4; ++i)
	{
		M1[i]=new double[4];
		for (int j = 0; j < 4; ++j)
			M1[i][j]=mat[i][j];
	}

	FCmatrixFull A(M1,4,4);
	A.Print();

	vector<Vec> M2(5,Vec(5));

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
			M2[i][j]=mat0[i][j];
	}

	FCmatrixFull B(M2);
	B.Print();
	cout << endl;
	
	FCmatrixBanded C(B,1);

	FCmatrixFull D(C);
	D.Print();


	D.swapRows(1,2);
	D.Print();

	A.Transpose();
	A.Print();

	D.swapCols(3,4);
	D.Print();


	D+=A;
	D.Print();

	double mat15[][2]= {
		{1,2},
		{2,2},
	};


	vector<Vec> M25(2,Vec(2));

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
			M25[i][j]=mat15[i][j];
	}

	FCmatrixFull E(M25);
	E.Print();
	cout << endl;


	FCmatrixFull F(E.Inverse());
	F.Print();
}