#include "EqSolver.h"
#include "Vec.h"
#include "FCmatrixFull.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double a[]={3,2,1,3};
	double b[]={2,2,2,4};
	double c[]={1,1,1,7};
	double z[]={1,50,5,49};
	
	// make Matrix
	vector<Vec> V;
	V.push_back(Vec(4,a));
	V.push_back(Vec(4,b));
	V.push_back(Vec(4,c));
	V.push_back(Vec(4,z));

	FCmatrixFull M(V);
	
	// constants vector
	double d[]={4, 2, 9, 5};
	Vec vc(4,d);
	
	// solve linear system
	EqSolver S(M,vc);
	Vec vsol_gauss = S.GaussEliminationSolver();

	cout << "Sol por Gauss: " << endl;
	vsol_gauss.Print();
	cout << endl;

	S.Print(3,8);

	/**********************************/

	// solve linear system
	Vec vsol_lu = S.LUdecompositionSolver();

	cout << "Sol por LUdec: " << endl;
	vsol_lu.Print();

	S.Print(3, 6);

	/**********************************/

	double h[]={ 3, 6, 4};
	double i[]={-9, 5, 3};
	double j[]={ 2, 4, 7};

	// make Matrix
	vector<Vec> M0;
	M0.push_back(Vec(3,h));
	M0.push_back(Vec(3,i));
	M0.push_back(Vec(3,j));

	double k[]={2, 1, 4};
	Vec l(3,k);

	FCmatrixFull M2(M0);
	
	S.SetMatrix(M2);
	S.SetConstants(l);

	Vec x = S.GaussEliminationSolver();

	cout << "\nSolution by Gauss Elimination " << endl;
	x.Print(10);

	cout << endl;

	/**********************************/

	x = S.GaussSeidelIterator(1e-8);
	
	cout << "Solution by GaussSeidel" << endl;
	x.Print(10, 10);

	cout << endl;

	/**********************************/

	x = S.JacobiIterator(1e-8);

	cout << "Solution by Jacobi" << endl;
	x.Print(10, 10);
	
	cout << endl;

	/**********************************/

	x = S.SORIterator(1e-8);

	cout << "Solution by SOR" << endl;
	x.Print(10, 10);
	
	S.Print();

	/**********************************/

	cout << "----------------------" << endl;
	cout << "Determinant of A: " << S.Determinant() << endl << endl << endl;

	S.Print(4, 8);
	cout << "----------------------" << endl;
	S.Invert();
	cout << "----------------------" << endl;
	S.Print(4, 8);

	cout << "Determinant of A⁻¹: " << S.Determinant() << endl;

	/**********************************/

	FCmatrixFull M3 = S.GetMatrix();
	Vec cst = S.GetConstants();

	M3.Print(4, 8);
	cst.Print(4, 8);

	return 0;
}