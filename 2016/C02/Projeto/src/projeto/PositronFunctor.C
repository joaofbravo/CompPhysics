#include "PositronFunctor.h"
#include <TMath.h>
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::string;

PositronFunctor::PositronFunctor(unsigned int seed, string element) :

	// [0] -> density, [1] -> sigma
	InvProbSigma("InvProbSigma","-log(x)/([0]*[1])"),

	// [0] -> me
	gamma("gamma","1+x/[0]"),

	// x -> u, y -> gamma
	S("S","-(y+1)*(y+1)+(y*y+4*y+1)/x-1/(x*x)"),

	// x -> u, y -> E , [0] -> re
	dsigmadu2D("dsigmadu2D", this, &PositronFunctor::funcdsigmadu2D, 0, 0.5, 0.05e-3, 5000., 1, "", ""),

	// x-> u, [0] -> E
	dsigmadu("dsigmadu", this, &PositronFunctor::funcdsigmadu, 0, 0.5, 1, "", ""),

	// [0] - > min/dsigmadu(min)
	Auxiliar("Auxiliar","[0]/x"),

	// [0] -> min
	InvAuxiliar("InvAuxiliar","[0]*pow(0.5/[0],x)"),

	dif("dif",this,&PositronFunctor::funcdif, 0, 0.5, 1, "", ""),

	// [0] -> Re
	sigmatot("sigmatot","(TMath::Pi() * [0]*[0])/((x + 1)*(x*x -1))*((x*x+4*x+1)*log(x+sqrt(x*x-1))-(3+x)*sqrt(x*x-1))"),

	// [0] -> gamma, x-> u
	costheta1("costheta1","([0]+1-1/x)/sqrt([0]*[0]-1)"),

	// [0] -> gamma, x-> u
	costheta2("costheta2","([0]+1-1/(1-x))/sqrt([0]*[0]-1)"),

	gen0(&dsigmadu,seed)
{

	SetElement(element);

	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
}

PositronFunctor::~PositronFunctor()
{
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
}


void PositronFunctor::SetEnergy0(double E)
{
	dsigmadu.SetParameter(0,E);
	double fgamma = gamma.Eval(E);
	InvProbSigma.SetParameter(1,sigmatot.Eval(fgamma));


	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif	
}

void PositronFunctor::SetEnergy1(double E)
{
	double fgamma = gamma.Eval(E);
	double min = 1/(1+ fgamma + sqrt(fgamma*fgamma - 1));

	Auxiliar.SetParameter(0,0.5*dsigmadu.Eval(0.5));
	InvAuxiliar.SetParameter(0,min);
	costheta1.SetParameter(0,fgamma);
	costheta2.SetParameter(0,fgamma);

	// dsigmadu.SetRange(min,0.5);
	// Auxiliar.SetRange(min,0.5);
	// dif.SetRange(min,0.5);
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif	
}

void PositronFunctor::SetElement(string element)
{
	Consts.SetElement(element);
		
	const double me = Consts.me;
	const double Re = Consts.Re;
	const double Na = Consts.Na;
	const double Z = Consts.Z;
	const double A = Consts.A;
	const double P = Consts.P;
	const double dens = P*(Z/A)*Na;

	gamma.SetParameter(0,me);
	dsigmadu2D.SetParameter(0,Re);
	sigmatot.SetParameter(0,Re);
	InvProbSigma.SetParameter(0,dens);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void PositronFunctor::SetSeed(unsigned int seed)
{
	gen0.SetSeed(seed);
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}



//=============== Composed Functions ===============

double PositronFunctor::funcdsigmadu(double* var, double* par)
{
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	return dsigmadu2D.Eval(var[0],par[0]);
}

double PositronFunctor::funcdsigmadu2D(double* var, double* par)
{
	double fgamma = gamma.Eval(var[1]);

	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	if(var[0] >=  1./(1 + fgamma + sqrt(fgamma*fgamma - 1)))
		return (TMath::Pi() * par[0]*par[0])/((fgamma + 1)*(fgamma*fgamma -1)) * (S.Eval(var[0],fgamma) + S.Eval(1-var[0],fgamma));
	else
		return 0;
}

double PositronFunctor::funcdif(double* var, double* par)
{
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	return Auxiliar.Eval(var[0]) - dsigmadu.Eval(var[0]);
}