#ifndef __FCmatrixBanded__
#define __FCmatrixBanded__ 

#include "FCmatrix.h"
#include "FCmatrixFull.h"

using std::vector;

class FCmatrixBanded : public FCmatrix {
public:
	FCmatrixBanded(double** =nullptr, int=1, int=1); //matrix fn x fm
	FCmatrixBanded(double*, int, int);
	FCmatrixBanded(vector<Vec>);
	FCmatrixBanded(const FCmatrix&, int=-1); //if -1, copy the matrix
	~FCmatrixBanded();

	// assignments
	// FCmatrixBanded& operator=(const FCmatrixBanded&, int=-1);

	// unary operators
	void operator+=(const FCmatrix&) {;} //======
	void operator-=(const FCmatrix&) {;} //======
	void operator*=(const FCmatrix&) {;} //======
	void operator*=(double) {;} //======

	// binary operators
	// FCmatrixBanded operator+(const FCmatrix&) const;
	// FCmatrixBanded operator-(const FCmatrix&) const;
	// FCmatrixBanded operator*(const FCmatrix&) const;
	// FCmatrixBanded operator*(double) const;

	Vec operator*(const Vec&) const {return Vec();} //======

	// friend FCmatrixBanded operator* (double, const FCmatrixBanded&);
	// friend Vec operator* (const Vec&, const FCmatrixBanded&);

	// Get methods
	Vec& GetDiagonal(int);
	const Vec& GetDiagonal(int) const;
	double at(int, int) const;
	const unsigned int size() const;

	// operator[] - GetRow
	const Vec& operator[] (int) const;
	const Vec& GetCol(int) const;

	// normalizer, row/col i, begin in j element
	int GetRowMax(double*, int, int = 0) const {return 0;} //======
	int GetColMax(double*, int, int = 0) const {return 0;} //======

	// work on Matrix
	void Transpose();
	FCmatrixFull Inverse() const;
	
	void Print() const;

private:
	int width;
	int dim;
	mutable Vec aux;
};

#endif