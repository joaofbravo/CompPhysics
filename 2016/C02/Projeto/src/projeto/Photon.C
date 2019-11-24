#include "Photon.h"
#include "Electron.h"
#include "Positron.h"
#include "TMath.h"
#include "FCmatrixRotation.h"

using namespace std;

const unsigned int seed = 0;
PhotonFunctor Photon::Func(seed);

const double me = 0.5109989461;

Photon::Photon(const TVector3& mom, const TVector3& init) : Particle(mom, init) 
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Photon::Photon(const Photon& fp) : Particle((Particle&)fp) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Photon::~Photon() 
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

const Photon& Photon::operator=(const Photon& fp) 
{

	Particle::operator=((Particle&)fp);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

void Photon::SetSeed(unsigned int seed) {
	R.SetSeed(seed);
	Func.SetSeed(seed);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Photon::SetElement(string element) {
	Func.SetElement(element);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}


//=============== Virtual inherited ===============

int Photon::GetType() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return 0;
}

double Photon::GetEnergy() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return P.Mag();
}

list<Particle*> Photon::Interact(bool& del, Interactions& inter) 
{ 
	del = true;

	double E = GetEnergy();
	list<Particle*> L;

	if(E < 5.)
		return L;

	inter.PairProduction++;
	double y = R.Uniform();
	SetDist(Func.InvPares.Eval(y));
	TVector3 end (pi + P*(GetDist()/E));

	Func.SetEnergy(E);
	double eps = Func.gen0.AcceptanceRejection(Func.Auxiliar,Func.InvAuxiliar);
	
	double Eele = eps*E - me;
	double Epos = E - Eele - 2* me;

	// ========== Electron ==========

	double Pmagele = sqrt(Eele*(Eele+2*me));
	double Betaele = Pmagele/(Eele+me);
	Func.InvdNdx.SetParameter(0,Betaele);
	
	double costhetaele = Func.InvdNdx.Eval(R.Uniform());
	double sinthetaele = sqrt(1-costhetaele*costhetaele); 
	double phiele = R.Uniform(0, TMath::TwoPi());

	TVector3 Pele (Pmagele*sinthetaele*cos(phiele),Pmagele*sinthetaele*sin(phiele),Pmagele*costhetaele);

	FCmatrixRotation rot(P);
	Pele = rot*Pele;

	L.push_back(new Electron(Pele,end));

	// ========== Positron ==========

	double Pmagpos = sqrt(Epos*(Epos+2*me));
	double Betapos = Pmagpos/(Epos+me);
	Func.InvdNdx.SetParameter(0,Betapos);
	
	double costhetapos = Func.InvdNdx.Eval(R.Uniform());
	double sinthetapos = sqrt(1-costhetapos*costhetapos); 
	double phipos = phiele + TMath::Pi();

	TVector3 Ppos (Pmagpos*sinthetapos*cos(phipos),Pmagpos*sinthetapos*sin(phipos),Pmagpos*costhetapos);
	Ppos = rot*Ppos;

	L.push_back(new Positron(Ppos,end));
	
	// ========== Tests ==========

	// cout << "Betaele: " << Betaele << endl;
	// cout << "Betapos: " << Betapos << endl;
	// cout << "costhetaele: " << costhetaele << endl;
	// cout << "costhetapos: " << costhetapos << endl;
	// cout << "PhiPos: " << phipos <<endl;
	// cout << "PhiEle: " << phiele <<endl;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return L;
}

void Photon::Print() const
{
	cout << 0 << "     ";
	Particle::Print();

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Photon::PrintFile(ofstream& F) const
{
	F << 0 << "     ";
	Particle::PrintFile(F);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}