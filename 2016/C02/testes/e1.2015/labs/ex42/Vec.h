#ifndef __Vec__
#define __Vec__

#include <vector>
using std::vector;

class Vec {
public:
	Vec(int = 1, double = 0.);
	Vec(int, const double*);
	Vec(const vector<double>&);
	Vec(const Vec&);
	Vec(Vec&&);
	virtual ~Vec();

	// assignments
	const Vec& operator= (const Vec&);
	Vec& operator= (Vec&&);

	// set Vec entries
	void SetEntries (int, double*);

	// operators []
	double& operator[] (int);
	const double& operator[] (int) const;

	// binary operators
	Vec operator+ (const Vec &) const;
	Vec operator- (const Vec &) const;
	Vec operator* (const Vec &) const;
	Vec operator* (double) const;
	Vec operator/ (const Vec &) const;
	Vec operator/ (double) const;
	
	friend Vec operator* (double, const Vec &);
	
	// unary operators
	void operator+= (const Vec &);
	void operator-= (const Vec &);
	void operator*= (const Vec &);
	void operator*= (double);
	void operator/= (const Vec &);
	void operator/= (double);

	Vec operator-() const;
	double operator! () const; // norma

	// others
	double dot (const Vec &) const;
	void swap(int, int);
	const unsigned int size() const;

	virtual void Print(short int = 0, short int = 0) const;

protected:
	int N; // number of elements
	double *entries;
};

#endif