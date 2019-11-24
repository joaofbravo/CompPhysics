#include "ElePosFunctor.h"
#include <iostream>

using std::cout;
using std::endl;

ElePosFunctor::ElePosFunctor(bool ftype,unsigned int seed, string element) :
	
	type(ftype),

	// [0] -> , [1] -> 
	// PdfBrem("PdfBrem","[1]*exp(-[0]*x)"),

	// [0] -> n, [1] -> sigma 	
	InvBremSigma("InvBremSigma","-log(x)/([0]*[1])"),

	// x -> E part, y -> W, [0] -> me
	eps("eps","y/(x+[0])", 0.05e-3, 5000., 0.05e-3, 5000.),
	
	// x -> E part, y -> W, [0] -> RmeC/(/h), [1] -> me
	b("b", this, &ElePosFunctor::funcb, 0.05e-3, 5000., 0.05e-3, 5000., 2, "", ""),

	// x -> E part, y -> W, [0] -> Rmech
	Phi1("Phi1", this, &ElePosFunctor::funcPhi1, 0.05e-3, 5000., 0.05e-3, 5000., 1, "", ""),

	// x -> E part, y -> W, [0] -> Rmech
	Phi2("Phi2", this, &ElePosFunctor::funcPhi2, 0.05e-3, 5000., 0.05e-3, 5000., 1, "", ""),

	// x -> W, [0] -> E part
	BremDFC("BremDFC", this, &ElePosFunctor::funcBremDFC, 0.05e-3, 5000., 1, "", ""),

	// x -> W, y -> E part, [0] -> Re, [1] -> alpha, [2] -> Z
	BremDFC2D("BremDFC2D", this, &ElePosFunctor::funcBremDFC2D, 0.05e-3, 5000., 0.05e-3, 5000., 3, "", ""),

	// x -> E part, [0] -> W
	BremDFCCurve("BremDFCCurve", this, &ElePosFunctor::funcBremDFCCurve, 0.05e-3, 5000., 1, "", ""),

	// [0] concavidade -> 0.05e-3*Brem(0.05e-3)
	Auxiliar("Auxiliar","[0]/x",0.05e-3,5000), 

	// [0] -> Wc, [1] -> E
	InvAuxiliar("InvAuxiliar","[0]*pow([1]/[0],x)"),

	// [0] -> me, x ->E
	beta("beta","sqrt(x*(x + 2* [0]))/(x + [0])"),
	
	//[0] -> me, [1] ->Beta, [2] -> E
	dNdx("dNdx","3/(16*TMath::Pi())*(1+ (x-[1])*(x-[1])/((1-[1]*x)*(1-[1]*x)))*[0]*[0]/(([2] + [0])*([2] + [0]))/((1-[1]*x)*(1-[1]*x))",-1,1),

	//[0] -> me, [1] ->Beta, [2] -> E
	AuxiliarAng("AuxiliarAng","6/(16*TMath::Pi())*[0]*[0]/(([2] + [0])*([2] + [0]))/((1-[1]*x)*(1-[1]*x))",-1,1),
	
	//[0] -> Beta
	InvAuxiliarAng("AuxiliarAng","([0]-1 +2*x)/(1-[0] + 2*[0]*x)",0,1),

	integ(0.05e-3,5000,BremDFC),

	dNdx2D("dNdx2D", this, &ElePosFunctor::funcdNdx2D, -1, 1, 0.05e-3, 5000., 0, "", ""),

	//[0] ->me, x -> E
	gamma("gamma", "1 + x/[0]"),

	//[0]-> I, x ->beta*gamma 
	C("C","1e-6*[0]*[0]*(((0.422377)/(x*x)+(0.0304043)/(x*x*x*x)-(0.00038106)/(x*x*x*x*x*x))+((3.850190)/(x*x)+(0.1667989)/(x*x*x*x)-(0.00157955)/(x*x*x*x*x*x))*1e-3*[0])"),

	//x -> gamma, y -> beta
	fminus("fminus","1-y*y-(2*x-1)/(x*x)*log(2)+((x-1)/x)*((x-1)/x)/8"),

	//x -> gamma, y -> beta
	fplus("fplus","2*log(2)-(y*y)/12*(23+(14)/(x+1)+(10)/((x+1)*(x+1))+4/((x+1)*(x+1)*(x+1)))"),

	//[0]-> C0, [1]-> a, [2]-> U0, [3] -> U1, [4] -> m,	x-> B =  log(b*gamma)/log(10)
	delta("delta"," (x < [2]) ? 0 : (x < [3]) ? 4.6052*x+[0]+[1]*pow([3]-x,[4]) : 4.6052*x+[0]"),

	//x->Z
	I("I","(x < 13) ? 12*x + 7 : 9.76* x + 58.8*pow(x,-0.19)"),

	//x -> E, [0] -> 2πNaRe^2mec^2, [1] -> P/A, [2] -> Z, [3] -> I [4] -> beta, [5] -> gamma

	dEdx("dEdx", this, &ElePosFunctor::funcdEdx, 0.05e-3, 5000., 6, "", ""),

	gen0(&BremDFC,seed)

{
	gen1.SetFunction(dNdx);

	/*const double alpha = 1./137.035999139;
	const double Re = 2.81794e-13;
	const double me = 0.5109989461;
	const double Rmech = 44.503;
	const double Z = 13;
	const double A = 26.9815385;
	const double P = 2.699;
	const double Na = 6.022140857e23;
	const double C0 = -4.24;
	const double a = 0.0802;
	const double U0 = 0.1708;
	const double U1 = 3.01;
	const double m = 3.63;
	const double areamassa = 0.1535;*/

	SetElement(element);

	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
}

ElePosFunctor::~ElePosFunctor()
{
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
}

void ElePosFunctor::SetSigma(double E)
{
	BremDFC.SetParameter(0,E);
	integ.SetMax(E);
	double sigma = integ.SimpsonAdaptative(1e-27);
	InvBremSigma.SetParameter(1,sigma);
	
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
}

void ElePosFunctor::SetParticleEnergy(double E)
{
	// cout <<"Sigma: " <<sigma <<endl;
	InvAuxiliar.SetParameter(1,E);
	double fBeta = beta.Eval(E);
	// cout << "\n\n\n\nbeta: " << fBeta <<endl;
	dNdx.SetParameter(1,fBeta);
	dNdx.SetParameter(2,E);
	AuxiliarAng.SetParameter(1,fBeta);
	AuxiliarAng.SetParameter(2,E);
	InvAuxiliarAng.SetParameter(0,fBeta);
	dEdx.SetParameter(4,fBeta);
	dEdx.SetParameter(5,gamma.Eval(E));
}

void ElePosFunctor::SetSeed(unsigned int seed)
{
	gen0.SetSeed(seed);
	gen1.SetSeed(seed);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ElePosFunctor::SetElement(string element)
{
	Consts.SetElement(element);
		
	const double alpha = Consts.alpha;
	const double Re = Consts.Re;
	const double me = Consts.me;
	const double Rmech = Consts.Rmech;
	const double Z = Consts.Z;
	const double A = Consts.A;
	const double P = Consts.P;
	const double Na = Consts.Na;
	const double C0 = Consts.C0;
	const double a = Consts.a;
	const double U0 = Consts.U0;
	const double U1 = Consts.U1;
	const double m = Consts.m;
	const double areamassa = Consts.areamassa;


	const double n = Na*(P/A);
	const double Wc = 0.05e-3;

	InvBremSigma.SetParameter(0,n);

	eps.SetParameter(0,me);
	b.SetParameters(Rmech, me);
	Phi1.SetParameter(0,Rmech);
	Phi2.SetParameter(0,Rmech);

	BremDFC.SetParameter(0,5000);
	BremDFC2D.SetParameters(Re, alpha, Z);
	Auxiliar.SetParameter(0,1.1*BremDFC.Eval(Wc)*Wc);
	InvAuxiliar.SetParameter(0,Wc);
	beta.SetParameter(0,me);
	dNdx.SetParameter(0,me);
	AuxiliarAng.SetParameter(0,me);
	gamma.SetParameter(0,me);
	delta.SetParameters(C0,a,U0,U1,m);
	C.SetParameter(0,I.Eval(Z));
	dEdx.SetParameters(areamassa, P/A, Z, I.Eval(Z));
	//x -> E, [0] -> 2πNaRe^2mec^2, [1] -> P/A, [2] -> Z, [3] -> I [4] -> beta, [5] -> gamma

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== Composed Functions ===============

double ElePosFunctor::funcb(double* var, double* par)
{
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	double epsilon = eps.Eval(var[0], var[1]);

	return par[0]*0.5*epsilon/((1.+var[0]/par[1]) * (1-epsilon));
}

double ElePosFunctor::funcPhi1(double* var, double* par)
{
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	double fb = b.Eval(var[0], var[1]);

	return 4*log(par[0])+2.-2*log(1+fb*fb)-4*fb*atan(1./fb);
}

double ElePosFunctor::funcPhi2(double* var, double* par)
{
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	double fb = b.Eval(var[0], var[1]);

	return 4*log(par[0])+7./3.-2*log(1+fb*fb)-6*fb*atan(1./fb)-fb*fb*(4-4.*fb*atan(1./fb)-3*log(1+1./(fb*fb)));
}

double ElePosFunctor::funcBremDFC(double* var, double* par)
{
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	return BremDFC2D.Eval(par[0],var[0]);/*1e23*/
}

double ElePosFunctor::funcBremDFC2D(double* var, double* par)
{
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	double epsilon = eps.Eval(var[0], var[1]);

	return par[0]*par[0]*par[1]*par[2]*par[2]/var[1]*(epsilon*epsilon*Phi1.Eval(var[0], var[1]) + 4./3.*(1.-epsilon)*Phi2.Eval(var[0], var[1]));
}

double ElePosFunctor::funcBremDFCCurve(double* var, double* par)
{
	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	return BremDFC2D.Eval(var[0],par[0]);
}

double ElePosFunctor::funcdNdx2D(double* var, double* par)
{
	double fbeta = beta.Eval(var[1]);

	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	
	dNdx.SetParameter(1,fbeta);
	dNdx.SetParameter(2,var[1]);

	// cout <<"Beta: "<<fbeta<< "dN/dx: " <<dNdx.Eval(var[0]) << endl; 
	return dNdx.Eval(var[0]);
}

double ElePosFunctor::funcdEdx(double* var, double* par)
{
	//x -> E, [0] -> 2πNaRe^2mec^2, [1] -> P/A, [2] -> Z, [3] -> I, [4] -> beta, [5] -> gamma
	double f;
	double bg = par[4]*par[5];
	double B = log(bg)/log(10);

	// cout << par[4] << " " << par[5] << " " << bg << endl;
	// cout << B << endl;

	if (type) 
		f = fplus.Eval(par[5]);
	else
		f = fminus.Eval(par[5],par[4]);

	// cout << f << endl;
	// cout << delta.Eval(B) << endl;
	// cout << C.Eval(bg) << endl;

	#ifdef DEBUG
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	return par[0]*par[1]*par[2]/(par[4]*par[4])*(log((var[0]*var[0])/(1e-12*par[3]*par[3])*(par[5]+1)/(2))+f-delta.Eval(B)-2*(C.Eval(bg))/(par[2]));
}