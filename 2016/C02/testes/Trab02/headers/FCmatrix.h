#ifndef __FCmatrix__
#define __FCmatrix__

#include "Vec.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class FCmatrix {
public:
	FCmatrix(double** =nullptr, int=0, int=0); //matrix fn x fm
	FCmatrix(double*, int, int);
	FCmatrix(vector<Vec>);
	virtual ~FCmatrix();

	// unary operators
	virtual void operator+=(const FCmatrix&) = 0; 
	virtual void operator-=(const FCmatrix&) = 0; 
	virtual void operator*=(const FCmatrix&) = 0; 
	virtual void operator*=(double) = 0;

	// binary operators
	virtual Vec operator*(const Vec&) const = 0;

	// Get methods
	Vec& GetRawVec(int);
	const Vec& GetRawVec(int) const;
	int RawSize() const;
	virtual unsigned int size() const;
	string GetClassName() const;

	// operator[] - GetRow
	virtual Vec& operator[] (int);
	virtual const Vec& operator[] (int) const = 0;
	virtual const Vec& GetCol(int) const = 0;

	// normalizer, row/col i, begin in j element
	virtual int GetRowMax(double*, int, int = 0) const = 0;
	virtual int GetColMax(double*, int, int = 0) const = 0;

	// work on Matrix
	virtual void swapRows(int, int, double* =nullptr);
	virtual void swapCols(int, int);
	virtual void Transpose() = 0;
	double Determinant() const;

	virtual void Print(short int = 0, short int = 0) const;

protected:
	vector<Vec> M;
	string classname;
};

#endif