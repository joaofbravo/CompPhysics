#include "ODEsolver.h"
#include "FCmatrixBanded.h"
#include "EqSolver.h"
#include <iostream>

using namespace std;

ODEsolver::ODEsolver() {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ODEsolver::ODEsolver(const vector<TFormula>& fF) : F(fF) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ODEsolver::~ODEsolver() {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== set methods ===============

void ODEsolver::SetODEfunc(const vector<TFormula>& fF)
{
	F = fF;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ODEsolver::SetPar(double* par)
{
	for (int i = 0; i < F.size(); ++i)
		F[i].SetParameters(par);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== iterative methods ===============

vector<ODEpoint> ODEsolver::Euler(const ODEpoint& point, double h, double Tf)
{
	vector<ODEpoint> ret;
	ret.push_back(point);

	while((ret.end()-1)->T() < Tf)
	{
		ODEpoint& current = *(ret.end()-1);
		double time = current.T();
		ret.push_back(current + h*Eval(current));
		ret[ret.size()-1][0] = time + h;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return ret;
}

vector<ODEpoint> ODEsolver::PredictorCorrector(const ODEpoint& point, double h, double Tf)
{
	vector<ODEpoint> ret;
	ret.push_back(point);

	while((ret.end()-1)->T() < Tf)
	{
		ODEpoint& current = *(ret.end()-1);
		double time = current.T();
		
		ODEpoint prediction = current + h*Eval(current);
		prediction[0] = time + h;

		ret.push_back(current + (Eval(current) + Eval(prediction))*(h*0.5));
		ret[ret.size()-1][0] = time + h;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return ret;
}

vector<ODEpoint> ODEsolver::RK2(const ODEpoint& point, double h, double Tf)
{
	vector<ODEpoint> ret;
	ret.push_back(point);

	while((ret.end()-1)->T() < Tf)
	{
		ODEpoint& current = *(ret.end()-1);
		double time = current.T();

		ODEpoint K1 = current + h*Eval(current)/2.;
		K1[0] = time + h/2;
		ODEpoint K2 = h*Eval(K1);

		ret.push_back(current + K2);
		ret[ret.size()-1][0] = time + h;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return ret;
}

vector<ODEpoint> ODEsolver::RK4(const ODEpoint& point, double h, double Tf)
{
	vector<ODEpoint> ret;
	ret.push_back(point);

	while((ret.end()-1)->T()<Tf)
	{
		ODEpoint& current = *(ret.end()-1);
		double time = current.T();

		// compute slope at ti
		ODEpoint K1 = h*Eval(current);
		ODEpoint sum1 = current + K1/2;
		sum1[0] = time + h/2;

		// compute slope at ti+1/2
		ODEpoint K2 = h*Eval(sum1);
		ODEpoint sum2 = current + K2/2;
		sum2[0] = time + h/2;

		// compute third slope
		ODEpoint K3 = h*Eval(sum2);
		ODEpoint sum3 = current + K3;
		sum3[0] = time + h;

		// calculate slope at end point
		ODEpoint K4 = h*Eval(sum3);

		// use now all four slopes as estimators
		ret.push_back(current + (K1 + 2*(K2+K3) + K4)/6.);
		ret[ret.size()-1][0] = time + h;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return ret;
}

vector<ODEpoint> ODEsolver::FiniteDiff(double t0, double tf, double y0, double yf, double h, bool derivativei, bool derivativef)
{
	int N = (tf-t0)/h;
	h = (tf - t0)/(double) N;

	Vec diagu(N);
	Vec diagc(N+1);
	Vec diagl(N);
	Vec vecn(4);
	Vec b(N+1);

	for (int i = 1; i < N; ++i)
	{
		double t= t0 + h*i;

		for (int j = 0; j < 4; ++j)
			vecn[j] = F[j].Eval(t);

		diagc[i] = vecn[2]- 2*vecn[0]/(h*h);
		diagl[i-1] = vecn[0]/(h*h) - vecn[1]/(2*h);
		diagu[i] = vecn[0]/(h*h) + vecn[1]/(2*h);
		b[i] = vecn[3];
	}

	if(derivativei)
	{
		diagc[0] = F[2].Eval(t0) - 2*F[0].Eval(t0)/(h*h);
		diagu[0] = 2*F[0].Eval(t0)/(h*h);
		b[0] = F[3].Eval(t0) + y0*(2*F[0].Eval(t0)/h - F[1].Eval(t0));
	}
	else
	{
		diagc[0] = 1;
		b[0] = y0;
	}

	if(derivativef)
	{
		diagc[N] = 2*F[0].Eval(tf)/(h*h);
		diagl[N-1] = F[2].Eval(tf)-2*F[0].Eval(tf)/(h*h);
		b[N] = F[3].Eval(tf) - yf*(2*F[0].Eval(tf)/h - F[1].Eval(tf));
	}
	else
	{
		diagc[N] = 1;
		b[N] = yf;
	}

	vector<Vec> bandedV;
	bandedV.push_back(diagu);
	bandedV.push_back(diagc);
	bandedV.push_back(diagl);

	FCmatrixBanded banded(bandedV);
	FCmatrixFull Full(banded);

	EqSolver solve(banded,b);
	Vec x = solve.GaussEliminationSolver();
	
	// banded.Print();
	// b.Print();
	// solve.Print();
	// x.Print();
	
	if(x.size() == 1)
	{
		cout << __PRETTY_FUNCTION__<< ": Couldn't solve the problem, solution did not converge! " << x[0] << endl;
		exit (1);
	}

	vector<ODEpoint> ret(N+1, ODEpoint(2));

	for (int i = 0; i <= N; ++i)
	{
		ret[i][0] = t0 + i*h;
		ret[i][1] = x[i];
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return ret;
}

//=============== private ===============

ODEpoint ODEsolver::Eval(ODEpoint& point)
{
	int Neqs = F.size();
	double fpoint[Neqs+1];
	fpoint[0] = 0.;

	for (int i = 0; i < Neqs; ++i)
		fpoint[i+1] = F[i].EvalPar(point.GetArray());

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return ODEpoint(Neqs+1, fpoint);
}