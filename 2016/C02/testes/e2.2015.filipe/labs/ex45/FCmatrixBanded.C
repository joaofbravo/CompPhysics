#include "FCmatrixBanded.h"
#include "EqSolver.h"
#include <iostream>
#include <cstdlib>

using namespace std;

FCmatrixBanded::FCmatrixBanded(double** fM, int n, int bandwidth) : FCmatrix((double**)nullptr, bandwidth, 0), dim(n), width(bandwidth) 
{
	classname = "banded";
	int disp = width/2;

	if(!(width%2))
	{
		cout << "Invalid band width, please provide an odd number!!!" << endl;
		exit (1);
	}

	if(dim <= width/2)
	{
		cout << "Invalid band width, please make sure bandwidth <= number of diagonals of the matrix" << endl;
		exit (1);
	}

	if(fM){
		for (int i = 0; i < width; ++i)
			M[i]=(Vec(dim - abs(i-disp),fM[i]));
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrixBanded::FCmatrixBanded(double* fM, int n, int bandwidth) : FCmatrix((double**)nullptr,bandwidth,0), dim(n), width(bandwidth)
{
	classname = "banded";
	int disp = width/2;

	if(!(width%2))
	{
		cout << "Invalid band width, please provide an odd number!!!" << endl;
		exit (1);
	}

	if(dim <= width/2)
	{
		cout << "Invalid band width, please make sure bandwidth <= number of diagonals of the matrix" << endl;
		exit (1);
	}
	
	for (int i = 0, iterator = 0; i < width; ++i)
	{
		int size = dim - abs(i-disp);
		M[i]=(Vec(size,&fM[iterator]));
		iterator +=size;	
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrixBanded::FCmatrixBanded(vector<Vec> vec) : width((int)vec.size()), FCmatrix(vec), dim((int)vec[vec.size()/2].size()) 
{
	classname = "banded";
	int disp = width/2;

	if(!(width%2))
	{
		cout << "Invalid band width, please provide an odd number!!!" << endl;
		exit (1);
	}

	if(dim <= width/2)
	{
		cout << "Invalid band width, please make sure bandwidth <= number of diagonals of the matrix" << endl;
		exit (1);
	}
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrixBanded::FCmatrixBanded(const FCmatrix& mat, int bandwidth) : width(bandwidth), dim(mat.size())
{
	classname = "banded";

	if(!(width%2))
	{
		cout << "Invalid band width, please provide an odd number!!!" << endl;
		exit (1);
	}

	if(dim <= width/2)
	{
		cout << "Invalid band width, please make sure bandwidth <= number of diagonals of the matrix" << endl;
		exit (1);
	}

	if(mat.GetClassName() == "full")
	{
		if(width == -1)
			width = 2*dim-1;

		if(mat.size()!=mat[0].size())
		{
			cout << "Invalid matrix, please give me a square one!!!" << endl;
			exit (1);
		}

		FCmatrixFull copy(mat);
		
		int disp = width/2;

		for (int k = -disp; k < 1; ++k)
		{	
			Vec diag(dim + k);
			for (int i = 0; i < dim + k; ++i)
				diag[i]=copy[i][i-k];

			M.push_back(diag);	
		}

		for (int k =  1; k <= disp; ++k)
		{	
			Vec diag(dim - k);
			for (int i = 0; i < dim - k; ++i)
				diag[i]=copy[i +k][i];

			M.push_back(diag);
		}
	}
	else if (mat.GetClassName() == "banded")
	{
		if(width == -1)
			width = mat.RawSize();
		
		int min =  std::max(-width/2, -mat.RawSize()/2);
		int max =  std::min(width/2, mat.RawSize()/2);

		for (int i = -width/2; i < -mat.RawSize()/2; ++i)
			M.push_back(Vec(dim + i));

		for (int i = min; i <= max; ++i)
			M.push_back(mat.GetRawVec(mat.RawSize()/2+i));

		for (int i = mat.RawSize()/2; i < width/2; ++i)
			M.push_back(Vec(dim -i +1));
	}
	else
	{
		cout << "I'm incomplete, please define more matrix types, namely " << mat.GetClassName() << endl;
		exit (1);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrixBanded::~FCmatrixBanded()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

//=============== assignments ===============

//=============== unary operators ===============

//=============== binary operators ===============

//=============== Get methods ===============

Vec& FCmatrixBanded::GetDiagonal(int i)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return GetRawVec(width/2+i);
}

const Vec& FCmatrixBanded::GetDiagonal(int i) const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return GetRawVec(width/2+i);
}

double FCmatrixBanded::at(int i, int j) const
{
	int disp = width/2;
	int dif = i-j;

	if(abs(dif) <= disp){
		if(dif < 0)
			return M[dif + disp][i];
		else
			return M[dif + disp][j];
	}
	else
		return	0;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}		

const unsigned int FCmatrixBanded::size() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return (unsigned int)dim;
}

//=============== operator[] - GetRow ===============

const Vec& FCmatrixBanded::operator[] (int i) const
{
	aux = Vec(dim);

	for(int j = 0 ; j < dim; j ++)
		aux[j] = this->at(i,j);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return aux;
}

const Vec& FCmatrixBanded::GetCol(int i) const
{
	aux = Vec(dim);

	for(int j = 0 ; j < dim; j ++)
		aux[j] = this->at(i,j);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return aux;
}

//=============== work on Matrix ===============

void FCmatrixBanded::Transpose()
{
	vector<Vec> copy;

	for(int i = -width; i <= width; i++)
		copy.push_back(GetDiagonal(-i));

	M.swap(copy);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ <<endl;
	#endif
}

FCmatrixFull FCmatrixBanded::Inverse() const
{
	Vec b(this->size());
	EqSolver S(*this,b);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ <<endl;
	#endif

	return S.Invert();
}

//=============== Print ===============

void FCmatrixBanded::Print() const
{
	int disp = width/2;

	cout << endl;
	for (int i = 0; i < dim; ++i)
	{	
		for (int j = 0; j < dim; ++j)
			cout << at(i,j) << " ";	
		cout << endl;
	}
	cout << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}