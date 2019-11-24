#include "Vec.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

Vec::Vec(int n, double val) : N(n), entries(new double[n])
{
	for (int i = 0; i < n; ++i)
		entries[i] = val;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Vec::Vec(int n, double* pval) : N(n), entries(new double[n])
{
	for (int i = 0; i < n; ++i)
		entries[i] = pval[i];
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Vec::Vec(const vector<double>& vect) : N((int)vect.size()), entries(new double[vect.size()])
{
	for (int i = 0; i < vect.size(); ++i)
		entries[i] = vect[i];
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Vec::Vec(const Vec& vec) : N(vec.N), entries(new double[vec.N])
{
	for (int i = 0; i < vec.N; ++i)
		entries[i] = vec.entries[i];
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Vec::Vec(Vec&& vec) : N(vec.N), entries(new double[vec.N])
{
	entries = vec.entries;

	vec.N = 0;
	vec.entries = nullptr;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Vec::~Vec()
{
	if (entries) delete [] entries;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== assignments ===============

const Vec& Vec::operator= (const Vec& vec) 
{
	N = vec.N;
	if (entries) delete[] entries;
	
	entries = new double[vec.N];
	
	for (int i = 0; i < N; ++i)
		entries[i] =  vec.entries[i];

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

Vec& Vec::operator= (Vec&& vec)
{
	N = vec.N;		
	if (entries) delete[] entries;

	entries = vec.entries;

	vec.N = 0;
	vec.entries = nullptr;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

//=============== set Vec entries ===============

void Vec::SetEntries (int n, double* arr)
{
	if (entries) delete [] entries;

	N = n;
	entries = new double[n];

	for (int i = 0; i < n; ++i)
		entries[i] = arr[i];

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== operators [] ===============

double& Vec::operator[] (int i)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return entries[i];
}

const double& Vec::operator[] (int i) const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return entries[i];	
}

//=============== binary operators ===============

Vec Vec::operator+ (const Vec& vec) const
{
	Vec a(*this);
	a += vec;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return a;
}

Vec Vec::operator- (const Vec& vec) const
{	
	Vec a(*this);
	a -= vec;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return a;
}

Vec Vec::operator* (const Vec& vec) const
{
	Vec a(*this);
	a *= vec;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return a;
}

Vec Vec::operator* (double cc) const
{
	Vec ret(N);

	for (int i = 0; i < N; ++i)
		ret[i] = entries[i] * cc;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return ret;
}

Vec Vec::operator/ (const Vec& vec) const
{
	Vec a(*this);
	a /= vec;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return a;
}


Vec Vec::operator/ (double cc) const
{
	Vec ret(N);

	if(cc != 0.)
	{
		for (int i = 0; i < N; ++i)
			ret[i] = entries[i] / cc;
	}
	else
	{
		cout << "Error! Cannot divide by zero." << endl;
		exit(1);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return ret;
}

// Friend Function
Vec operator* (double cc, const Vec& vec) 
{
	Vec ret(vec.size());

	for (int i = 0; i < vec.size(); ++i)
		ret[i] = vec[i] * cc;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return ret;
}

//=============== unary operators ===============

void Vec::operator+= (const Vec& vec)
{	
	if(N < vec.size())
	{
		double copy[vec.size()] = {0.};
		
		for (int i = 0; i < N; ++i)
			copy[i] = entries[i];
		
		delete [] entries;

		entries = new double[vec.size()];
		N = vec.size();

		for (int i = 0; i < vec.size(); ++i)
			entries[i] =  copy[i] + vec[i];
	}
	else
	{
		for (int i = 0; i < vec.size(); ++i)
			entries[i] += vec[i];
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Vec::operator-= (const Vec& vec)
{
	if(N < vec.size())
	{
		double copy[vec.size()] = {0.};
		
		for (int i = 0; i < N; ++i)
			copy[i] = entries[i];
		
		delete [] entries;

		entries = new double[vec.size()];
		N = vec.size();

		for (int i = 0; i < vec.size(); ++i)
			entries[i] =  copy[i] - vec[i];
	}
	else
	{
		for (int i = 0; i < vec.size(); ++i)
			entries[i] -= vec[i];
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Vec::operator*= (const Vec& vec)
{
	if(N < vec.size())
	{
		double copy[vec.size()] = {0.};
		
		for (int i = 0; i < N; ++i)
			copy[i] = entries[i];
		
		delete [] entries;

		entries = new double[vec.size()];

		int N_old = N;
		N = vec.size();

		for (int i = 0; i < N_old; ++i)
			entries[i] =  copy[i] * vec[i];
	}
	else
	{
		for (int i = 0; i < vec.size(); ++i)
			entries[i] *= vec[i];
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Vec::operator*= (double cc)
{
	for (int i = 0; i < N; ++i)
		entries[i] *= cc;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Vec::operator/= (const Vec& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == 0.)
		{
			cout << "Error! Cannot divide these 2 Vecs. Element v[" << i << "] is zero." << endl;
			exit(1);
		}
	}

	if(N < vec.size())
	{
		double copy[vec.size()] = {0.};
		
		for (int i = 0; i < N; ++i)
			copy[i] = entries[i];
		
		delete [] entries;

		entries = new double[vec.size()];

		int N_old = N;
		N = vec.size();

		for (int i = 0; i < N_old; ++i)
			entries[i] =  copy[i] / vec[i];
	}
	else
	{
		for (int i = 0; i < vec.size(); ++i)
			entries[i] /= vec[i];
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Vec::operator/= (double cc)
{
	if(cc != 0.)
	{
		for (int i = 0; i < N; ++i)
			entries[i] /= cc;
	}
	else
	{
		cout << "Error! Cannot divide by zero." << endl;
		exit(1);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Vec Vec::operator-() const
{
	Vec ret(N);

	for (int i = 0; i < N; ++i)
		ret[i] = -entries[i];
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return ret;
}

double Vec::operator! () const
{
	return sqrt(this->dot(*this));
}

//=============== others ===============

double Vec::dot (const Vec& vec) const
{
	double res = 0.;

	for (int i = 0; i < vec.size() && i < N; ++i)
		res += entries[i] * vec[i];
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return res;
}

void Vec::swap(int a, int b)
{	
	if(a < N && a >= 0 && b < N && b >= 0){
		double C = entries[a];
		entries[a] = entries[b];
		entries[b] = C;
	}
	else {
		cout << "Error! Indexes do not belong to this Vec." << endl;
		exit(1);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

unsigned int Vec::size() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return (unsigned int)N;
}

//=============== Print ===============

void Vec::Print(short int p, short int w) const
{
	streamsize pp = cout.precision();
	streamsize ww = cout.width();

	if (p != 0){
		if (w == 0)
			w = p + 1;

		cout.precision(p);
	}

	for (int i = 0; i < N; ++i)
		cout << setw(w) << entries[i] << "\t";

	cout << endl;

	if (p != 0 || w != 0){
		cout.precision(pp);
		cout << setw(ww); 
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}