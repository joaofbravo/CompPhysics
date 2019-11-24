#include "FCmatrixFull.h"
#include "EqSolver.h"
#include <iostream>
#include <cmath>

using namespace std;

FCmatrixFull::FCmatrixFull(double** fM, int fn, int fm) : FCmatrix(fM, fn, fm), rowindices(fn)
{
	classname = "full";

	for (int i = 0; i < fn; ++i)
		rowindices[i] = i;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrixFull::FCmatrixFull(double* fM, int fn, int fm) : FCmatrix(fM, fn, fm), rowindices(fn)
{
	classname = "full";

	for (int i = 0; i < fn; ++i)
		rowindices[i] = i;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrixFull::FCmatrixFull(vector<Vec> vec) : FCmatrix(vec), rowindices(vec.size())
{
	classname = "full";

	for (int i = 0; i < M.size(); ++i)
		rowindices[i] = i;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrixFull::FCmatrixFull(const FCmatrix& mat) : rowindices(mat.size())
{
	classname = "full";

	int fn = (int) mat.size();

	for (int i = 0; i < fn; ++i)
		M.push_back(mat[i]);

	for (int i = 0; i < fn; ++i)
		rowindices[i] = i;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrixFull::~FCmatrixFull()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}


//=============== assignments ===============

FCmatrixFull& FCmatrixFull::operator=(const FCmatrix& mat) 
{
	int fn = (int) mat.size();
	
	M.clear();

	for (int i = 0; i < fn; ++i)
		M.push_back(mat[i]);

	vector<int> local(fn);

	for (int i = 0; i < fn; ++i)
		local[i] = i;

	rowindices.swap(local);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	

	return *this;
}

//=============== unary operators ===============

void FCmatrixFull::operator+= (const FCmatrix& mat)
{
	if (M.size() < mat.size())
	{
		for (int i = (int)M.size(); i < mat.size() ; ++i)
		{
			M.push_back(Vec());
			rowindices.push_back(i);
		}
	}

	if(mat.GetClassName() == "full"){
		for (int i = 0; i < mat.size(); ++i)
			((*this).operator[](i)) += mat[i];				
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif		
} 

void FCmatrixFull::operator-= (const FCmatrix& mat)
{
	if (M.size() < mat.size())
	{
		for (int i = (int)M.size(); i < mat.size() ; ++i)
		{
			M.push_back(Vec());
			rowindices.push_back(i);
		}
	}

	if(mat.GetClassName() == "full"){
		for (int i = 0; i < mat.size() && i < M.size(); ++i)
			((*this).operator[](i)) -= mat[i];				
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif		
}

void FCmatrixFull::operator*= (const FCmatrix& mat)
{
	FCmatrixFull copy(*this);

	for (int i = 0; i < M.size(); ++i)
		rowindices[i] = i;

	vector<Vec> m(copy.size(), Vec(mat[0].size()));
	M.swap(m);	

	if(mat.GetClassName() == "full"){
		for (int i = 0; i < M.size(); ++i){
			for (int j = 0; j < M[0].size(); ++j)
				M[i][j] = copy[i].dot(mat.GetCol(j));
		}
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif		
}

void FCmatrixFull::operator*= (double lambda)
{
	for (int i = 0; i < M.size(); ++i){
		for (int j = 0; j < M[i].size(); ++j)
			M[i][j] *= lambda;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== binary operators ===============

FCmatrixFull FCmatrixFull::operator+ (const FCmatrix& mat) const
{
	FCmatrixFull a(*this);
	a += mat;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return a;
}

FCmatrixFull FCmatrixFull::operator- (const FCmatrix& mat) const
{
	FCmatrixFull a(*this);
	a -= mat;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return a;
}

FCmatrixFull FCmatrixFull::operator* (const FCmatrix& mat) const
{	
	FCmatrixFull m((double**)nullptr, (int)M.size(), (int)mat[0].size());

	if(mat.GetClassName() == "full"){
		for (int i = 0; i < M.size(); ++i){
			for (int j = 0; j < mat[0].size(); ++j)
			{
				m[i][j] = M[rowindices[i]].dot(mat.GetCol(j));		
			}	
		}
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif		

	return m;
}

FCmatrixFull FCmatrixFull::operator* (double lambda) const
{
	FCmatrixFull m(*this);

	for (int i = 0; i < m.size(); ++i){
		for (int j = 0; j < m[i].size(); ++j)
			m[i][j] *= lambda;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return m;
}

Vec FCmatrixFull::operator* (const Vec& vec) const
{
	Vec ret((int) M.size());

	for (int i = 0; i < M.size(); ++i)
		ret[i]= M[rowindices[i]].dot(vec);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return ret;
}

FCmatrixFull operator* (double lambda, const FCmatrixFull& mat)
{
	FCmatrixFull m(mat);

	for (int i = 0; i < m.size(); ++i){
		for (int j = 0; j < m[i].size(); ++j)
			m[i][j] *= lambda;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return m;
}

Vec operator* (const Vec& vec, const FCmatrixFull& mat)
{
	Vec ret(mat.size());

	for (int i = 0; i < mat.size(); ++i)
		ret[i] = mat.GetCol(i).dot(vec);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return ret;
}

//=============== operator[] - GetRow ===============

Vec& FCmatrixFull::operator[] (int i)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return M[rowindices[i]];
}

const Vec& FCmatrixFull::operator[] (int i) const
{	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return M[rowindices[i]];
}

const Vec& FCmatrixFull::GetCol(int i) const
{
	aux = Vec((int) M.size());
	
	for (int j = 0; j < M.size(); ++j)
		aux[j] = M[rowindices[j]][i]; 		

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return aux;
}

// normalizer, row/col i, begin in j element

int FCmatrixFull::GetRowMax(double* s, int i, int j) const
{
	Vec row((*this)[i]);

	double max = 0;
	int maxindex = 0;

	for (int k = j; k < M[0].size(); ++k){
		row[k]*=s[k];
		if(max < fabs(row[k]))
		{
			max = fabs(row[k]);
			maxindex = k;
		}
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ <<endl;
	#endif	

	if(max < 1e-14)
		return -1;

	return maxindex;
}

int FCmatrixFull::GetColMax(double* s, int i, int j) const
{
	Vec col(this->GetCol(i));
	
	double max = 0;
	int maxindex = j;

	for (int k = j; k < M[0].size(); ++k){
		col[k]*=s[k];
		if(max < fabs(col[k]))
		{
			max = fabs(col[k]);
			maxindex = k;
		}
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ <<endl;
	#endif	

	if(max < 1e-14)
		return -1;

	return maxindex;
}

//=============== work on Matrix ===============

void FCmatrixFull::swapRows(int i, int j, double* s)
{
	swap(rowindices[i],rowindices[j]);
	
	if(s)
		swap(s[i],s[j]);		

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void FCmatrixFull::swapCols(int i, int j)
{
	for(int c = 0; c < M.size(); c++)
		M[c].swap(i,j);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void FCmatrixFull::Transpose()
{
	vector<Vec> copy;

	for(int i = 0; i < M.size(); i++)
		copy.push_back(GetCol(i));

	M.swap(copy);

	vector<int> copyint(M.size());

	for (int i = 0; i < M.size(); ++i)
		copyint[i] = i;

	rowindices.swap(copyint);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ <<endl;
	#endif
}

FCmatrixFull FCmatrixFull::Inverse() const
{
	Vec b(this->size());
	EqSolver S(*this,b);
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ <<endl;
	#endif

	return S.Invert();
}

//=============== Print ===============

void FCmatrixFull::Print(short int p, short int w) const
{
	cout << endl;

	for(unsigned int i = 0; i < M.size(); i++)
		M[rowindices[i]].Print(p, w);

	cout << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ <<endl;
	#endif	
}