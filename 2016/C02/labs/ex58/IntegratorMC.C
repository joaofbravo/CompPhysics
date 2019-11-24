#include "IntegratorMC.h"
#include "TRandom3.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

int IntegratorMC::funccounter = -1;

IntegratorMC::IntegratorMC(const TF1* fp, const double* lowlimits, const double* uplimits){

	funccounter++;

	if(fp)
	{
		string name("FIntegrand");
		name += std::to_string(funccounter);

		F = new TFormula(name.c_str(), fp->GetExpFormula());
		dim = fp->GetNdim();
		
		if(lowlimits && uplimits)
		{
			lowlim = new double[dim];
			uplim = new double[dim];

			for (int i = 0; i < dim; ++i)
			{
				lowlim[i] =  lowlimits[i];
				uplim[i] =  uplimits[i];
			}
		}
		else
		{
			lowlim = nullptr;
			uplim = nullptr;
		}
	}
	else
	{
		F = nullptr;
		dim = 0;
		lowlim = nullptr;
		uplim = nullptr;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

IntegratorMC::IntegratorMC(const TFormula& form, const double* lowlimits, const double* uplimits){

	funccounter++;

	string name("FIntegrand");
	name += std::to_string(funccounter);

	F = new TFormula(name.c_str(), form.GetExpFormula());
	dim = form.GetNdim();

	if(lowlimits && uplimits)
	{
		lowlim = new double[dim];
		uplim = new double[dim];

		for (int i = 0; i < dim; ++i)
		{
			lowlim[i] = lowlimits[i];
			uplim[i] = uplimits[i];
		}
	}
	else
	{
		lowlim = nullptr;
		uplim = nullptr;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

IntegratorMC::~IntegratorMC(){

	if(lowlim) delete lowlim;
	if(uplim)  delete uplim;
	if(F)      delete F;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== Set/Get methods ===============

void IntegratorMC::SetFunction(const TFormula& form)
{
	if(F) delete F;

	string name("FIntegrand");
	name += std::to_string(funccounter);

	F = new TFormula(name.c_str(), form.GetExpFormula());
	dim = form.GetNdim();

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void IntegratorMC::SetLimits(const double* lowlimits, const double* uplimits)
{
	if(F)
	{
		if(lowlim) delete lowlim;
		if(uplim)  delete uplim;

		lowlim = new double[dim];
		uplim = new double[dim];

		for (int i = 0; i < dim; ++i)
		{
			lowlim[i] = lowlimits[i];
			uplim[i] = uplimits[i];
		}
	}
	else
	{
		cout << __PRETTY_FUNCTION__ << ": No integrand function set!" << endl;
		exit(1);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

TFormula IntegratorMC::GetFunction() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	if(F)
		return *F;
	else
	{
		cout << __PRETTY_FUNCTION__ << ": No integrand function set!" << endl;
		exit(1);
	}
}

//=============== MC integral methods ===============

void IntegratorMC::UniformRandom(int N, double& result, double& error, bool abs) const
{
	if(F)
	{
		TRandom3 R(0);
		double var[dim];
		double eval = 0.;
		result = 0.;
		error = 0.;

		for (int i = 0; i < N; ++i)
		{
			R.RndmArray(dim, var);

			for (int i = 0; i < dim; ++i)
			{
				var[i] *= (uplim[i]-lowlim[i]);
				var[i] += lowlim[i];
			}

			eval = F->EvalPar(var);

			if(abs)
				eval = fabs(eval);

			result += eval;
			error += eval*eval;
			// cout << eval << endl;
		}
		
		result /= (double)N;
		error /= (double)N;
		error -= result*result;
		error /= (double)N;
		error = sqrt(fabs(error));

		for (int i = 0; i < dim; ++i)
		{
			// cout << result << endl;
			result *= (uplim[i]-lowlim[i]);
			error *= (uplim[i]-lowlim[i]);		
		}
	}
	else
	{
		cout << __PRETTY_FUNCTION__ << ": No integrand function set!" << endl;
		exit(1);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void IntegratorMC::ImportanceSampling(int N, double& result, double& error, TFormula& pdf, const TFormula* inv) const
{
	if(F)
	{
		TRandom3 R(0);
		double var[dim];
		double eval = 0.;
		result = 0.;
		error = 0.;

		for (int i = 0; i < N; ++i)
		{
			R.RndmArray(dim, var);

			for (int i = 0; i < dim; ++i)
				var[i] = inv[i].Eval(var[i]);

			eval = F->EvalPar(var)/pdf.EvalPar(var);
			result += eval;
			error += eval*eval;

			// cout << eval << " " << F->EvalPar(var) << " " << pdf.EvalPar(var) << endl;
		}

		result /= (double)N;
		error /= (double)N;
		error -= result;
		error /= (double)N;
		error = sqrt(fabs(error));
	}
	else
	{
		cout << __PRETTY_FUNCTION__ << ": No integrand function set!" << endl;
		exit(1);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void IntegratorMC::AcceptanceRejection(int N, double& result, double& error, TFormula& aux, const TFormula* inv) const
{
	if(F)
	{
		TRandom3 R(0);
		double var[dim];
		double eval = 0.;
		double ratio = 0.;
		result = 0.;
		error = 0.;

		int Negr = 0;
		int Posr = 0;

		for (int i = 0; i < N; ++i)
		{
			R.RndmArray(dim, var);

			for (int i = 0; i < dim; ++i)
			{
				var[i] = inv[i].Eval(var[i]);
				// cout << var[i] << endl;
			}

			// cout << endl;

			eval = F->EvalPar(var);
			ratio = eval/aux.EvalPar(var);

			if(eval > 0)
			{
				if(R.Rndm() < ratio)
					Posr++;
			}
			else
			{
				if(R.Rndm() < ratio)
					Negr++;
			}
		}

		double auxint = 0.;
		double auxerror = 0.;

		IntegratorMC auxIntegral(aux, lowlim, uplim);
		auxIntegral.UniformRandom(N, auxint, auxerror, true);
		
		result = (Posr-Negr)*auxint/(double)N;

		error = auxint*sqrt((Posr+Negr)*(1.-(double)(Posr+Negr)/(double)N))/(double)N + auxerror*result/auxint;
	}
	else
	{
		cout<<__PRETTY_FUNCTION__<< ": No integrand function set!" <<endl;
		exit(1);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}