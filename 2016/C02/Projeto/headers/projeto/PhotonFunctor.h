#ifndef __PHOTONFUNCTOR__
#define __PHOTONFUNCTOR__ 

#include "TF1.h"
#include "TF2.h"
#include "PDFgenerator.h"
#include "ConstantsManager.h"

class PhotonFunctor {
public:
	PhotonFunctor(unsigned int seed = 0,string element = "Aluminium");
	~PhotonFunctor();

	void SetEnergy(double E);
	void SetElement(string element);
	void SetSeed(unsigned int seed);

	//Probabylity of interaction
	TF1 PdfPares;
	TF1 InvPares;

	//Energy distribution
	TF1 SectionDiff;
	TF2 SectionDiff2D;
	TF1 SectionDiffCurve;

	//Auxiliar function to generate Energy distribution
	TF1 Auxiliar;
	TF2 Auxiliar2D;
	TF1 InvAuxiliar;

	//angular distribution
	TF1 dNdx;
	TF1 InvdNdx;

	PDFgenerator gen0;

private:
	ConstantsManager Consts;

	
	//Energy distribution
	TF1 F0;
	TF2 Phi1;
	TF2 Phi2;
	TF2 b;
	TF1 k;
	TF1 g0;
	TF1 g1;
	TF1 g2;

	//Auxiliar function to generate Energy distribution
	TF1 K;
	TF1 conc;

	//user funcs
	double funcPhi1(double* var, double* par);
	double funcPhi2(double* var, double* par);

	double funcSectionDiff(double* var, double* par);
	double funcSectionDiff2D(double* var, double* par);
	double funcSectionDiffCurve(double* var, double* par);

	// double funcAuxiliar(double* var, double* par);
	double funcAuxiliar2D(double* var, double* par);
	double funcAuxiliar(double* var, double* par);
	double funcInvAuxiliar(double* var, double* par);
};

#endif