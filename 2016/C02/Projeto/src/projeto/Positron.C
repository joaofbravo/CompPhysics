#include "Positron.h"
#include "Photon.h"
#include "FCmatrixRotation.h"
#include "TMath.h"

using namespace std;

ElePosFunctor Positron::FuncElePos(true);
PositronFunctor Positron::FuncPos;

const double mp = 0.5109989461;


Positron::Positron(const TVector3& mom, const TVector3& init) : Particle(mom, init) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Positron::Positron(const Positron& fp) : Particle((Particle&)fp) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Positron::~Positron() {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

const Positron& Positron::operator=(const Positron& fp) {

	Particle::operator=((Particle&)fp);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

void Positron::SetSeed(unsigned int seed) 
{
	R.SetSeed(seed);
	FuncElePos.SetSeed(seed);
	FuncPos.SetSeed(seed);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}


void Positron::SetElement(string element) 
{
	FuncElePos.SetElement(element);
	FuncPos.SetElement(element);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}


//=============== Virtual inherited ===============

int Positron::GetType() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return 2;
}

double Positron::GetEnergy() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return sqrt(mp*mp + P.Mag()*P.Mag()) - mp;
}

list<Particle*> Positron::Interact(bool& del, Interactions& inter)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	del = true;

	double E = GetEnergy();
	list<Particle*> L;
		
	// cout << "Energy0: " << E << endl;
	
	//Too low Energy
	if(E < 5e-5)
		return L;

	//=========== CHOOSING INTERACTION =============

	FuncElePos.SetSigma(E);
	FuncElePos.SetParticleEnergy(E);
	FuncPos.SetEnergy0(E);
	
	double y0 = R.Uniform();
	double y1 = R.Uniform();

	double dist0 = FuncElePos.InvBremSigma.Eval(y0);
	double dist1 = FuncPos.InvProbSigma.Eval(y1);

	if(dist0 < dist1)
	{
		//ENERGY LOSS:
		double dEdx = FuncElePos.dEdx.Eval(E);
		double deltaE = -dEdx*dist0;

		if((E +=deltaE) <= 5e-5)
		{
			dist0 +=  (5e-5 - E)/deltaE;
			dist+=dist0;
			 
			return L;
		}
		
		dist += dist0;
		
		FuncElePos.SetParticleEnergy(E);

		//=========== BREM RADIATON ==============

		inter.BremRad++;

		double W = FuncElePos.gen0.AcceptanceRejection(FuncElePos.Auxiliar, FuncElePos.InvAuxiliar);

		// ========== Positron ==========

		double Epos = E - W;
		// cout << "Energy1: " << Epos << endl;
 
		double Pmagpos = sqrt(Epos*(Epos+2*mp));
		P *= Pmagpos/P.Mag();
		
		if(Epos > 5e-5)
			del = false;
		
		// ========== Photon ==========

		if(W < 5.)
			return L;
		
		double costheta = FuncElePos.gen1.AcceptanceRejection(FuncElePos.AuxiliarAng, FuncElePos.InvAuxiliarAng);
		double sintheta = sqrt(1-costheta*costheta);
		double phi = R.Uniform(0, TMath::TwoPi());

		TVector3 Pphoton (W*sintheta*cos(phi),W*sintheta*sin(phi),W*costheta);

		FCmatrixRotation rot(P);
		Pphoton = rot*Pphoton;

		TVector3 end (pi + P*(dist/P.Mag()));

		L.push_back(new Photon (Pphoton,end));
	}
	else
	{
		//=========== ANNIHILATION =========
		
		inter.PosAnnihilation++;

		//ENERGY LOSS:
		double dEdx = FuncElePos.dEdx.Eval(E);
		double deltaE = -dEdx*dist1;

		if((E +=deltaE) < 5e-5)
		{
			dist1 +=  (5e-5 - E)/deltaE;
			E = 5e-5;
		}

		dist += dist1;

		TVector3 end (pi + P*(dist/P.Mag()));

		FuncPos.SetEnergy1(E);
		
		double u = FuncPos.gen0.AcceptanceRejection(FuncPos.Auxiliar,FuncPos.InvAuxiliar);
		
		double Etot = E + 2*mp;
		double Eph1 = u*Etot;
		double Eph2 = Etot - Eph1;

		// ========== Photon 1 ==========
		
		double costheta1 = FuncPos.costheta1.Eval(u);
		double sintheta1 = sqrt(1-costheta1*costheta1); 
		double phi1 = R.Uniform(0, TMath::TwoPi());

		TVector3 P1 (Eph1*sintheta1*cos(phi1),Eph1*sintheta1*sin(phi1),Eph1*costheta1);

		FCmatrixRotation rot(P);
		P1 = rot*P1;

		L.push_back(new Photon(P1,end));

		// ========== Photon 2 ==========

		// double costheta2 = FuncPos.costheta2.Eval(u);
		// double sintheta2 = sqrt(1-costheta2*costheta2); 
		// double phi2 = phi1 + TMath::Pi();

		// TVector3 P2 (Eph2*sintheta2*cos(phi2),Eph2*sintheta2*sin(phi2),Eph2*costheta2);
		// P2 = rot*P2;

		// L.push_back(new Photon(P2,end));


		// Mas por Conservação do momento linear:
		L.push_back(new Photon(P-P1,end));
	}

	return L;
}

void Positron::Print() const
{
	cout << 2 << "     ";
	Particle::Print();

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Positron::PrintFile(ofstream& F) const
{
	F << 2 << "     ";
	Particle::PrintFile(F);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}