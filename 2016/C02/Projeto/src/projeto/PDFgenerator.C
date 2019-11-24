#include "PDFgenerator.h"
#include <iostream>

using namespace std;

int PDFgenerator::N = 0;

PDFgenerator::PDFgenerator(TF1* pdf, unsigned int seed) : R(seed)
{
	if(pdf)
	{
		F0 = pdf;
		F0->GetRange(a,b);

	}
	else
		F0 = nullptr;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

PDFgenerator::PDFgenerator(TF1& pdf, double xmin, double xmax, unsigned int seed) : R(seed)
{
	F0 = &pdf;
	
	F0->GetRange(a,b);
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

PDFgenerator::~PDFgenerator()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void PDFgenerator::SetFunction(TF1& func)
{
	F0 = &func;
	F0->GetRange(a,b);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

void PDFgenerator::SetSeed(unsigned int seed)
{
	R.SetSeed(seed);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

/*void PDFgenerator::SetLimits(double xmin, double xmax)
{
	if(xmax < xmin)
		std::swap(xmax,xmin);
	a = xmin;
	b = xmax;
	if (F0) F0->SetRange(a,b);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}*/

TF1& PDFgenerator::GetFunction()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
	return *F0;
}

//recursive method, generates a random at a time
double PDFgenerator::AcceptanceRejection(const TF1& aux, const TF1& inv)
{
	//generate uniform
	double y = R.Uniform();
	//invert
	double x = inv.Eval(y);
	double ratio = F0->Eval(x)/aux.Eval(x);
	
	/*cout << F0->Eval(x) << " "  << aux.Eval(x) <<endl;
	cout << x <<endl;*/

	N++;
	if(ratio > 1)
	{
		cout << __PRETTY_FUNCTION__ <<"ATTENTION!! your auxiliar function isn't good for x = "<< x << " returning 0 \n\n\n\n\n" << endl;
		exit (1);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	//accept or not?
	if(R.Uniform() < ratio)
		return x;
	else
		return AcceptanceRejection(aux, inv);
}

bool PDFgenerator::AuxTester(const TF1& aux, double &x, double eps)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	if(F0)
	{
		F0->GetRange(a,b);
		for (x = a; x <= b; x+=eps)
		{
			if(F0->Eval(x) > aux.Eval(x))
				return false;
		}

		return true;
	}
	else
	{
		cout << "No function set! Returning false." << endl;
		return false;
	}
}

int PDFgenerator::GetN() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return N;
}