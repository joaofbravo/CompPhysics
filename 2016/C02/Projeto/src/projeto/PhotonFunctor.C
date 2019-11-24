#include "PhotonFunctor.h"
#include "TMath.h"
#include <iostream>

using std::cout;
using std::endl;

PhotonFunctor::PhotonFunctor(unsigned int seed, string element) :

	// [0] -> Ppar [1] -> A
	PdfPares("PdfPares","[1]*exp(-[0]*x)"),

	// [0] -> Ppar [1] -> A
	InvPares("InvPares","-log(x)/[0]"),
	
	// x -> E fot, [0] -> me
	k("k","x/[0]"),
	
	// [0] -> RmeC/(-h), x -> e, y -> k
	b("b","[0]/(2*y*x*(1-x))"),

	// x -> k , [0] -> a
	F0("F0","(-0.1774 - 12.10*[0]+11.18*[0]*[0])*pow(2./x,1./2.)+(8.523+73.26*[0]-44.41*[0]*[0])*(2./x)-(13.52+121.1*[0]-96.41*[0]*[0])*pow(2./x,3./2.)+(8.946+62.05*[0]-63.41*[0]*[0])*(2./x)*(2./x)"),

	// x -> F0(k), [0] -> RmeC/(-h), [1] - > fc
	g0("g0","4*log([0])-4*[1] + x"),
	
	// x -> b(x,k)
	g1("g1","7./3.-2*log(1+x*x)-6*x*atan(1./x)-x*x*(4-4*x*atan(1./x)-3*log(1+1./(x*x)))"),
	
	// x -> b(x,k)
	g2("g2","11./6.-2*log(1+x*x)-3*x*atan(1./x)+0.5*x*x*(4-4*x*atan(1./x)-3*log(1+1./(x*x)))"),

	// x -> e, y -> E fot
	Phi1("Phi1", this, &PhotonFunctor::funcPhi1, 0., 1., 0., 1., 0, "", ""),

	// x -> e, y -> E fot
	Phi2("Phi2", this, &PhotonFunctor::funcPhi2, 0., 1., 0., 1., 0, "", ""),

	// x -> e, [0] -> E
	SectionDiff("SectionDiff", this, &PhotonFunctor::funcSectionDiff, 0., 1., 1),

	// x -> e, y -> E fot
	SectionDiff2D("SectionDiff2D", this, &PhotonFunctor::funcSectionDiff2D, 0., 1., 5., 5000., 0, "", ""),

	// x -> E, [0] -> e
	SectionDiffCurve("SectionDiffCurve", this, &PhotonFunctor::funcSectionDiffCurve, 5., 5000., 1),
	
	// x -> E fot
	K("K","x < 25? 0.5 : x < 50? 0.20 + (0.5-0.2) * (x - 50) /(25-50) :   x < 80? 0.16 + (0.20-0.16) * (x - 80) /(50-80) : x < 125? 0.12 + (0.16-0.12) * (x - 125) /(80-125) : x < 500? 0.09 + (0.12-0.09) * (x - 500) /(125-500) : 0.04 + (0.09-0.04) * (x - 5000) /(500-5000) "),

	// x -> E fot
	conc("conc","x < 25? 0.49 : x < 50? 0.25 :   x < 80? 0.24 :  x < 125 ? 0.22 : x < 250 ? 0.19 : x < 500 ? 0.16 : x < 1000 ? 0.13 : x < 2000 ? 0.1 : x < 3000 ? 0.07 : 0.06 "),

	// x -> e, [0] -> K, [1] -> a, [2] -> min
	// Auxiliar("Auxiliar", "x < [0] ? [1]: x < 1-[0] ? [2]*cosh(TMath::ACosH([1]/[2])/([0]-0.5)*(x-0.5)): [1] "),

	Auxiliar("Auxiliar",this, &PhotonFunctor::funcAuxiliar, 0., 1., 0),
	// x -> e, y -> E fot
	Auxiliar2D("Auxiliar2D", this, &PhotonFunctor::funcAuxiliar2D, 0., 1, 5., 5000., 0, "", ""),

	// [0] -> fk, [1] -> a, [2] -> c
	// InvAuxiliar("InvAuxiliar", this, &PhotonFunctor::funcInvAuxiliar, 0., 1., 3),

	InvAuxiliar("InvAuxiliar", this, &PhotonFunctor::funcInvAuxiliar, 0., 1., 1),

	// x -> cos(teta), [0] -> beta
	dNdx("dNdx","1/((1-[0]*x)*(1-[0]*x))"),

	// x -> y, [0] -> beta
	InvdNdx("InvdNdx","([0]-1 +2*x)/(1-[0] + 2*[0]*x)"),

	gen0(&SectionDiff, seed)

{
	SetElement(element);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}


PhotonFunctor::~PhotonFunctor()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void PhotonFunctor::SetElement(string element)
{
	Consts.SetElement(element);
		
	const double A = Consts.A;
	const double P = Consts.P;
	const double alpha = Consts.alpha;
	const double Na = Consts.Na;
	const double Re = Consts.Re;
	const double Z = Consts.Z;
	const double X0 = Consts.X0;

	// cout << X0 << endl;
	const double pPar = 7./9.*P/X0; //2.248e-01 -> expressão 6
	const double me = Consts.me;
	const double Rmech = Consts.Rmech;
	const double a = alpha*Z;
	const double fc = a*a*(1./(1+a*a)+0.202059-0.03693*a*a+0.00835*a*a*a*a-0.00201*a*a*a*a*a*a+0.00049*a*a*a*a*a*a*a*a-0.00012*a*a*a*a*a*a*a*a*a*a+0.00003*a*a*a*a*a*a*a*a*a*a*a*a);

	// cout << 1./pPar << endl;
	PdfPares.SetParameters(pPar,A);
	InvPares.SetParameters(pPar,A);
	k.SetParameter(0,me);
	b.SetParameter(0,Rmech);
	F0.SetParameter(0,a);
	g0.SetParameters(Rmech,fc);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void PhotonFunctor::SetSeed(unsigned int seed)
{
	gen0.SetSeed(seed);
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void PhotonFunctor::SetEnergy(double E)
{
	SectionDiff.SetParameter(0,E);
	
	// double fk =  conc.Eval(E);
	// double a = SectionDiff2D.Eval(K.Eval(E),E)+0.48;
	// double c = SectionDiff2D.Eval(0.5,E)+0.48;
	// // cout << "b: " << b << endl;
	// Auxiliar.SetParameters(fk,a,c);
	// InvAuxiliar.SetParameters(fk,a,c);
}

//=============== Composed Functions ===============

double PhotonFunctor::funcPhi1(double* var,double* par)
{
	double fk = k.Eval(var[1]);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	double emin = 1./fk; 
	if(var[0] < emin || var[0] > 1 - emin)
		return 0;

	return g1.Eval(b.Eval(var[0],fk)) + g0.Eval(F0.Eval(fk));
}

double PhotonFunctor::funcPhi2(double* var,double* par)
{
	double fk = k.Eval(var[1]);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	double emin = 1./fk; 
	if(var[0] < emin || var[0] > 1 - emin)
		return 0;

	return g2.Eval(b.Eval(var[0],fk)) + g0.Eval(F0.Eval(fk));
}

double PhotonFunctor::funcSectionDiff(double* var,double* par)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return 2*(0.5-var[0])*(0.5-var[0])*Phi1.Eval(var[0],par[0]) + Phi2.Eval(var[0],par[0]);
}

double PhotonFunctor::funcSectionDiff2D(double* var,double* par)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return 2*(0.5-var[0])*(0.5-var[0])*Phi1.Eval(var[0],var[1]) + Phi2.Eval(var[0],var[1]);
}

double PhotonFunctor::funcSectionDiffCurve(double* var,double* par)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return 2*(0.5-par[0])*(0.5-par[0])*Phi1.Eval(par[0],var[0]) + Phi2.Eval(par[0],var[0]);
}

double PhotonFunctor::funcAuxiliar2D(double* var, double* par)
{
	Auxiliar.SetParameters(conc.Eval(var[1]),SectionDiff2D.Eval(K.Eval(var[1]),var[1])+0.48,SectionDiff2D.Eval(0.5,var[1])+0.48);

	// cout << var[0] << " " << var[1] << " " << aux0.Eval(var[0]) << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return Auxiliar.Eval(var[0]);
}

double PhotonFunctor::funcAuxiliar(double* var, double* par)
{
	return 1.2*SectionDiff.Eval(var[0]);
}

double PhotonFunctor::funcInvAuxiliar(double* var, double* par)
{
	// double fk =  par[0];

	// // cout << fk << endl;
	// double a = par[1];
	// // cout << "a: " << a << endl;
	// double c = par[2];
	// // cout << "c: " << c << endl;

	// double b = TMath::ACosH(a/c)/(fk-0.5);
	// // cout << "b: " << b << endl;
	// double cbsinh;
	// // cout << "cbsinh: " << cbsinh << endl;
	
	// if(b!=0)
	// 	cbsinh = c/b * TMath::SinH(b*(0.5-fk));
	// else
	// 	cbsinh = c * (0.5-fk);
	
	// double A = 2*(a*fk + cbsinh);

	// double x = var[0];

	// #ifdef DEBUG
	// cout << __PRETTY_FUNCTION__ << endl;
	// #endif

	// if(x < 0)
	// 	return 0;

	// else if(x < a*fk/A)
	// 	return A*x/a;

	// else if(x < a*fk/A + 2/A*cbsinh)
	// 	if(b!=0)
	// 		return TMath::ASinH(b/c*(A*x-a*fk-cbsinh))/b + 0.5;
	// 	else 
	// 		return (1/c*(A*x-a*fk-cbsinh)) + 0.5;

	// else if(x <= 1)
	// 	return (A*x -2*cbsinh)/a - 2*fk +1;

	// else
	// 	return 0;

	return var[0];
}