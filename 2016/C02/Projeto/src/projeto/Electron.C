#include "Electron.h"
#include "Photon.h"
#include "FCmatrixRotation.h"
#include "TMath.h"

using namespace std;

const double me = 0.5109989461;
ElePosFunctor Electron::Func(false);


Electron::Electron(const TVector3& mom, const TVector3& init) : Particle(mom, init) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Electron::Electron(const Electron& fp) : Particle((Particle&)fp) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Electron::~Electron() {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

const Electron& Electron::operator=(const Electron& fp) {

	Particle::operator=((Particle&)fp);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

void Electron::SetSeed(unsigned int seed) {
	R.SetSeed(seed);
	Func.SetSeed(seed);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Electron::SetElement(string element) {
	Func.SetElement(element);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== Virtual inherited ===============

int Electron::GetType() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return 1;
}

double Electron::GetEnergy() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return sqrt(me*me + P.Mag()*P.Mag()) - me;
}

list<Particle*> Electron::Interact(bool& del, Interactions& inter)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	del = true; 

	double E = GetEnergy();
	list<Particle*> L;
	
	if(E < 5e-5)
		return L;

	// cout << "Energy0: " << E << endl;

	Func.SetSigma(E);
	Func.SetParticleEnergy(E);

	inter.BremRad++;

	double y = R.Uniform();
	double dist0 = Func.InvBremSigma.Eval(y);

	double dEdx = Func.dEdx.Eval(E);
	double deltaE = -dEdx*dist0;

	// cout << "Energy0: " <<  E << endl; 
	// cout << "deltaE: " << deltaE << endl;

	if((E+=deltaE) <= 5e-5)
	{
		dist0 +=  (5e-5 - E)/deltaE;
		dist += dist0;

		return L;
	}
	// cout << "Energy1: " <<  E << endl; 
	
	dist+=dist0;
  
	Func.SetParticleEnergy(E);
	double W = Func.gen0.AcceptanceRejection(Func.Auxiliar, Func.InvAuxiliar); //E fot

	// ========== Electron ==========

	double Eele = E-W;
	// cout << "Energy1: " << Eele << endl;

	double Pmagele = sqrt(Eele*(Eele+2*me));
	P*= Pmagele/P.Mag();

	if(Eele > 5e-5)
		del = false;

	// ========== Photon ==========

	if(W < 5.)
		return L;

	double costheta = Func.gen1.AcceptanceRejection(Func.AuxiliarAng, Func.InvAuxiliarAng);
	double sintheta = sqrt(1-costheta*costheta);
	double phi = R.Uniform(0, TMath::TwoPi());

	TVector3 Pphoton (W*sintheta*cos(phi),W*sintheta*sin(phi),W*costheta);

	FCmatrixRotation rot(P);
	Pphoton = rot*Pphoton;

	TVector3 end (pi + P*(dist/P.Mag()));
	L.push_back(new Photon (Pphoton,end));

	return L;
}

void Electron::Print() const
{
	cout << 1 << "     ";
	Particle::Print();

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Electron::PrintFile(ofstream& F) const
{
	F << 1 << "     ";
	Particle::PrintFile(F);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}