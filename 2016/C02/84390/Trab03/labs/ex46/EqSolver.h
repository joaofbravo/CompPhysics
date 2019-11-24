#ifndef __EqSolver__
#define __EqSolver__

#include "FCmatrix.h"
#include "FCmatrixFull.h"
#include "Vec.h"
#include <vector>

using std::vector;

class EqSolver {
public:
	EqSolver();
	EqSolver(const FCmatrix&, const Vec&); // matriz M e vector de constantes b
	~EqSolver();

	// Set methods
	void SetMatrix(const FCmatrix&);
	void SetConstants(const Vec&);
	void ResetFlags();

	// Get methods
	const FCmatrix& GetMatrix() const;
	const Vec& GetConstants() const;

	//return triangular matrix and changed vector of constants
	bool GaussElimination(FCmatrix&, Vec&);
	Vec GaussEliminationSolver();
	//decomposição LU com |L|=1
	Vec LUdecompositionSolver(Vec = Vec(0));

	Vec JacobiIterator(double =1.E-4, Vec = Vec(0));
	Vec GaussSeidelIterator(double =1.E-4, Vec = Vec(0)); 
	Vec SORIterator(double =1.E-4, Vec = Vec(0)); 

	const FCmatrix& Invert();
	double Determinant();

	void Print(short int = 0, short int = 0) const;

private:
	bool LUdecomposition(FCmatrix&);
	int Pivoting(FCmatrix&, int, Vec&);
	bool GeneralIterator(FCmatrix&, Vec&, double eps, Vec& x, int N, bool method); //method true=Jacobi, false=GaussSeidel

	FCmatrix *M;         //matriz de coeffs
	Vec b;               //vector de constantes
	vector<int> permute; //vector permutação para LU
	FCmatrixFull FCmatrixnull;

	bool line_change;
	bool singular;
	bool LU_done;
	bool gauss_singular; //sem ser LU
};

#endif