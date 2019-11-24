#ifndef __IntegratorMC__
#define __IntegratorMC__

#include "TF1.h"
#include "TFormula.h"

class IntegratorMC {
public:
	IntegratorMC(const TF1* =nullptr, const double* =nullptr, const double* =nullptr);
	IntegratorMC(const TFormula&, const double* =nullptr, const double* =nullptr);
	~IntegratorMC();

	// set/get methods
	void SetFunction(const TFormula&);
	void SetLimits(const double*, const double*);
	TFormula GetFunction() const;

	// MC integral methods
	void UniformRandom(int N, double& result, double& error, bool abs =false) const; // simple integration wiht N samples

	void ImportanceSampling(int N, double& result, double& error, TFormula& pdf, const TFormula* inv) const; // auxiliar function and inverse
	// inverse xn(yn) should be an n dimentional array of 1 dimentional TFormulas, respecting:
	// y0 = int(a0,x0)int(a1,b1)int(a2,b2)...int(an,bn)p(x0,x1,x2,...,xn)dxn dxn-1... dx0

	void AcceptanceRejection(int N, double& result, double& error, TFormula& aux, const TFormula* inv) const; // non-normalized aux Function (aux - actual func) >= 0, in the inv array give the inverse of the pdf obtained from the auxiliar function as above

private:
	static int funccounter;
	TFormula* F;

	int dim;
	double* lowlim;
	double* uplim;
};

#endif
