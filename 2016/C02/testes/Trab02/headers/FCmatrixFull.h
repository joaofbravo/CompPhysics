#ifndef __FCmatrixFull__
#define __FCmatrixFull__ 

#include "FCmatrix.h"

using std::vector;

class FCmatrixFull : public FCmatrix {
public:
	FCmatrixFull(double** =nullptr, int=0, int=0); //matrix fn x fm
	FCmatrixFull(double*, int, int);
	FCmatrixFull(vector<Vec>);
	FCmatrixFull(const FCmatrix&);
	// FCmatrixFull(FCmatrix&&);
	~FCmatrixFull();

	// assignments
	FCmatrixFull& operator=(const FCmatrix&); 
	// FCmatrixFull& operator=(FCmatrix&&);
	
	// unary operators
	void operator+=(const FCmatrix&); 
	void operator-=(const FCmatrix&); 
	void operator*=(const FCmatrix&); 
	void operator*=(double);

	// binary operators
	FCmatrixFull operator+(const FCmatrix&) const;
	FCmatrixFull operator-(const FCmatrix&) const;
	FCmatrixFull operator*(const FCmatrix&) const;
	FCmatrixFull operator*(double) const;

	Vec operator*(const Vec&) const;

	friend FCmatrixFull operator* (double, const FCmatrixFull&);
	friend Vec operator* (const Vec&, const FCmatrixFull&);

	// operator[] - GetRow
	Vec& operator[] (int);
	const Vec& operator[] (int) const;
	const Vec& GetCol(int) const;

	// normalizer, row/col i, begin in j element
	int GetRowMax(double*, int, int = 0) const;
	int GetColMax(double*, int, int = 0) const;

	// work on Matrix
	void swapRows(int, int, double* =nullptr);
	void swapCols(int, int);
	void Transpose();
	FCmatrixFull Inverse() const;

	void Print(short int = 0, short int = 0) const;

private:
	vector<int> rowindices; // row indices (0,1,2,...)
	mutable Vec aux;
};

#endif