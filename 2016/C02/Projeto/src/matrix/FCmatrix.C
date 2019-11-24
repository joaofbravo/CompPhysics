#include "FCmatrix.h"
#include "EqSolver.h"
#include <iostream>

using namespace std;

FCmatrix::FCmatrix(double** fM, int fn, int fm) : M(vector<Vec> (fn,Vec(fm)))
{
	if(fM){
		for (int i = 0; i < fn; ++i)
			M[i] = Vec(fm,fM[i]);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrix::FCmatrix(double* fM, int fn, int fm) : M(vector<Vec> (fn))
{
	for (int i = 0; i < fn; ++i)
		M[i] = Vec(fm,&fM[i*fm]);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrix::FCmatrix(vector<Vec> vec) : M(vec.size())
{
	for (unsigned int i = 0; i < M.size(); ++i)
	{
		M[i] = Vec(vec[i].size());
		for(int j = 0; j < vec[i].size();j++)
			M[i][j] = vec[i][j];
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

FCmatrix::~FCmatrix()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif		
}


void FCmatrix::SetMatrix(double** Mat, int n, int m)
{
	M.clear();
	for (int i = 0; i < n; ++i)
		M.push_back(Vec(m,Mat[i]));
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== Get methods ===============

Vec& FCmatrix::GetRawVec(int i)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return M[i];
}

const Vec& FCmatrix::GetRawVec(int i) const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return M[i];
}

string FCmatrix::GetClassName() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return classname;
}

const int FCmatrix::RawSize() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return (int) M.size();
}

const unsigned int FCmatrix::size() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return (unsigned int) M.size();
}

//=============== operator[] - GetRow ===============

//Não está implementado
Vec& FCmatrix::operator[] (int)
{
	cout << __PRETTY_FUNCTION__ << endl;
	cout << "Something is wrong!!! I'm only used for class FCmatrixFull and you are calling me with " << classname << ". Blame the programmers..." << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	//return;
}

//=============== work on Matrix ===============

void FCmatrix::swapRows(int, int, double*)
{
	cout << "You cannot swap Rows in a Banded Matrix! Convert it into a Full Matrix to perform the operation." << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void FCmatrix::swapCols(int, int)
{
	cout << "You cannot swap Cols in a Banded Matrix! Convert it into a Full Matrix to perform the operation." << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

double FCmatrix::Determinant() const
{
	EqSolver S(*this,Vec(this->size()));
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ <<endl;
	#endif

	return S.Determinant();
}

//=============== Print ===============

void FCmatrix::Print(short int p, short int w) const
{
	cout << endl;

	for(unsigned int i = 0; i < M.size(); i++)
		M[i].Print(p, w);
	
	cout << endl;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}