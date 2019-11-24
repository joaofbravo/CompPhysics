#ifndef __PositronFunctor__
#define __PositronFunctor__ 

#include "TF1.h"
#include "TF2.h"
#include "PDFgenerator.h"
#include "ConstantsManager.h"

class PositronFunctor {
public:
	PositronFunctor(unsigned int seed = 0,string element = "Aluminium");
	~PositronFunctor();

	void SetEnergy0(double E);
	void SetEnergy1(double E);
	void SetElement(string element);
	void SetSeed(unsigned int seed);

	TF1 dsigmadu;
	TF2 dsigmadu2D;
	TF1 Auxiliar;
	TF1 InvAuxiliar;
	TF1 dif;
	TF1 sigmatot;
	TF1 InvProbSigma;
	TF1 costheta1;
	TF1 costheta2;
	TF1 gamma;

	PDFgenerator gen0;

private:
	ConstantsManager Consts;

	TF2 S;

	double funcdsigmadu2D(double* var, double* par);
	double funcdsigmadu(double* var, double* par);
	double funcdif(double* var, double* par);
};

#endif