#ifndef __ELEPOSFUNCTOR__
#define __ELEPOSFUNCTOR__ 

#include "TF1.h"
#include "TF2.h"
#include "PDFgenerator.h"
#include "Integrator.h"
#include "ConstantsManager.h"


using std::string;

class ElePosFunctor {
public:
	ElePosFunctor(bool type, unsigned int seed = 0, string element = "Aluminium");
	~ElePosFunctor();

	void SetSigma(double E);
	void SetParticleEnergy(double E);
	void SetSeed(unsigned int seed);
	void SetElement(string Element);

	// Funcs (DCF = Differential cross section)

	TF1 InvBremSigma;
	
	TF1 BremDFC;
	TF2 BremDFC2D;
	TF1 BremDFCCurve;

	TF1 Auxiliar;
	// TF2 Auxiliar2D;
	TF1 InvAuxiliar;

	//Continuous Energy Loss
	TF1 dEdx;

	//Continuous Energy Loss

	TF1 dNdx; // x -> cos(theta)
	TF2 dNdx2D; // x -> cos(theta), y -> E
	TF1 AuxiliarAng;
	TF1 InvAuxiliarAng;

	PDFgenerator gen0;
	PDFgenerator gen1;

private:
	ConstantsManager Consts;

	//auxiliares
	TF1 beta;
	TF1 gamma;


	TF1 delta;
	TF1 I;
	TF1 C;
	TF2 fminus;
	TF2 fplus;

	TF2 eps;
	TF2 b;
	TF2 Phi1;
	TF2 Phi2;


	double funcb(double* var, double* par);
	double funcPhi1(double* var, double* par);
	double funcPhi2(double* var, double* par);
	double funcBremDFC(double* var, double* par);
	double funcBremDFC2D(double* var, double* par);
	double funcBremDFCCurve(double* var, double* par);
	double funcdNdx2D(double* var, double* par);
	double funcdEdx(double* var, double* par);
	
	Integrator integ;

	bool type; //true -> positron, false -> electron

	// double funcAuxiliar(double* var, double* par);
	// double funcAuxiliar2D(double* var, double* par);
	// double funcInvAuxiliar(double* var, double* par);
};

#endif