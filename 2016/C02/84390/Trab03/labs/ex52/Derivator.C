#include "Derivator.h"
#include <cmath>
#include <iostream>

using namespace std;

Derivator::Derivator(const TF1* fp): Func1D(fp)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Derivator::Derivator(const TF1& fp): Func1D(fp)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Derivator::Derivator(const Func1D& f): Func1D((Func1D&)f)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Derivator::Derivator(Func1D&& f): Func1D((Func1D&&)f)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Derivator::~Derivator()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

//=============== derivatives ===============

double Derivator::ForwardDifference(double xval) const
{
	double coef[] = {1,-1};
	double hcoef[] = {1,0};
	double h;

	if(fabs(xval)>1)
		h = fabs(xval)*0.8e-8; //sqrt(1e-16)
	else
		h = 0.8e-8;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return generalderivator(xval,h,1,2,coef,hcoef);
}

double Derivator::BackwardDifference(double xval) const
{
	double coef[] = {1,-1};
	double hcoef[] = {0,-1};
	double h;

	if(fabs(xval)>1)
		h = fabs(xval)*0.8e-8; //sqrt(1e-16)
	else
		h = 0.8e-8;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return generalderivator(xval,h,1,2,coef,hcoef);
}

double Derivator::CentralDifference(double xval) const
{
	double coef[] = {-0.5,0.5};
	double hcoef[] = {-1,1};
	double h;

	if(fabs(xval)>1)
 		h = fabs(xval)*1e-5; //(1e-16)^1/3
		else
			h = 1e-5; 

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return generalderivator(xval,h,1,2,coef,hcoef);
}

double Derivator::CentralFirstAcu4(double xval) const
{
	double coef[] = {1./12.,-2./3.,2./3.,-1./12.};
	double hcoef[] = {-2,-1,1,2};
		double h;

		if(fabs(xval)>1)
		h = fabs(xval)*1.1e-3; //(1e-16)^1/5
	else
		h = 1.1e-3;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return generalderivator(xval,h,1,4,coef,hcoef,true);
}

double Derivator::CentralFirstAcu8(double xval) const
{
	double coef[] = {1./280.,-4./105.,1./5.,-4./5.,4./5.,-1./5.,4./105.,-1./280.};
	double hcoef[] = {-4,-3,-2,-1,1,2,3,4};
	double h;

	if(fabs(xval)>1)
		h = fabs(xval)*2e-2; //(1e-16)^1/9
	else
		h = 2e-2;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return generalderivator(xval,h,1,8,coef,hcoef,true);
}

double Derivator::CentralSecondAcu2(double xval) const
{
	double coef[] = {1,-2,1};
	double hcoef[] = {-1,0,1};
	double h;

	if(fabs(xval)>1)
		h = fabs(xval)*1e-4; //(1e-16)^1/4
	else
		h = 1e-4;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return generalderivator(xval,h,2,3,coef,hcoef,true);
}

double Derivator::CentralSecondAcu4(double xval) const
{
	double coef[] = {-1./12.,4./3.,-5./2.,4./3.,-1./12.};
	double hcoef[] = {-2,-1,0,1,2};
	double h;

	if(fabs(xval)>1)
		h = fabs(xval)*1e-4; //(1e-16)^1/4
	else
		h = 1e-4;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return generalderivator(xval,h,2,5,coef,hcoef,true);
}

double Derivator::CentralForthAcu2(double xval) const
{
	double coef[] = {1,-4,6,-4,1};
	double hcoef[] = {-2,-1,0,1,2};
	double h;

	if(fabs(xval)>1)
		h = fabs(xval)*2e-3; //(1e-16)^1/6
	else
		h = 2e-3;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return generalderivator(xval,h,4,5,coef,hcoef,true);
}

double Derivator::generalderivator(double xval, double h, double order, int N, double* coef,double* hcoef, bool roundupminimizer) const
{
	if(F)
	{
		double ret = 0.;

		if(roundupminimizer)
		{
			double negpart = 0.;
			double pospart = 0.;

			for(int i = 0 ; i<N; i++)
			{
				if(coef[i] < 0)
					negpart += coef[i]*Eval(xval+h*hcoef[i]);
				else
					pospart += coef[i]*Eval(xval+h*hcoef[i]);
			}

			ret = pospart+negpart;
		}
		else
		{
			for(int i = 0 ; i<N; i++)
				ret += coef[i]*Eval(xval+h*hcoef[i]);
		}

		for (int i = 0; i < order; ++i)
			ret /= h;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return ret;
	}
	else
	{		
		cout <<__PRETTY_FUNCTION__<< ": ATENTION! No function added, returning 0."<<endl;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return 0.;
	}
}