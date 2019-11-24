#ifndef __ODEsolver__
#define __ODEsolver__

#include "ODEpoint.h"
#include "TFormula.h"
#include <vector>

using std::vector;

class ODEsolver {
public:
	ODEsolver();
	ODEsolver(const vector<TFormula>&);
	~ODEsolver();

	// set methods
	void SetODEfunc(const vector<TFormula>&);
	void SetPar(double*);

	// iterative methods
	vector<ODEpoint> Euler(const ODEpoint& point, double h, double Tf);
	vector<ODEpoint> PredictorCorrector(const ODEpoint& point, double h, double Tf);
	vector<ODEpoint> RK2(const ODEpoint& point, double h, double Tf);
	vector<ODEpoint> RK4(const ODEpoint& point, double h, double Tf);

	/***********************************************************
							WARNING!!!!
	This method (FinitDiff) will only solve equations of the type 
	a(x) y′′(x) + b(x) y′(x) + c(x) y(x) = f(x) will assume the 
	given vector<TFormula> v is the following:
	v[0] = a(x);
	v[1] = b(x);
	v[2] = c(x);
	v[3] = f(x);
	************************************************************/

	vector<ODEpoint> FiniteDiff(double t0, double tf, double y0, double yf, double h, bool derivativei =false, bool derivativef =false);


private:
	ODEpoint Eval(ODEpoint&);
	
	vector<TFormula> F;
};

#endif