#include "Photon.h"
#include "Electron.h"
#include "Positron.h"
#include "PhotonFunctor.h"
#include "ElePosFunctor.h"
#include "cFCgraphics.h"
#include "TF1.h"
#include "TH1F.h"
#include "Integrator.h"
#include "TAxis.h"
#include <cmath>
#include <iomanip>
#include <list>

using namespace std;

int main() {

	Interactions inter{0,0,0};

	cout << "\n\n\n\n\n\n===== FOTÃO: =====\n\n\n\n\n\n" << endl;
	TVector3 Pi(0,0,0);
	TVector3 P(0,0,5000);
	Photon a(P,Pi);

	bool boleano;
	list<Particle*> l0 = a.Interact(boleano,inter);

	for (list<Particle*>::iterator i = l0.begin(); i != l0.end(); ++i)
		(*i)->Print();

	cout << "boleano:  " << boleano << endl;

	cout << "\n\n\n\n\n\n===== ELETRÃO: =====\n\n\n\n\n\n" << endl;
	Pi = TVector3(0,0,0);
	P = TVector3(0,0,5000);
	Electron e(P,Pi);
	
	boleano = false;
	int i = 0;
	
	while(!boleano)
	{
		list<Particle*> l1 = e.Interact(boleano,inter);

		for (std::list<Particle*>::iterator i = l1.begin(); i != l1.end(); ++i)
		{
			(*i)->Print();
			delete *(i);
		}
		
		if(!boleano)
			e.Print();
		else
			cout << "DIED!!!!" <<endl;
		i++;

		cout << "\n\niteração completa: " << i << " boleano: " << boleano << endl;
	}

	cout << "N interações: " << i << endl;



	cout << "\n\n\n\n\n\n===== POSITRÃO: =====\n\n\n\n\n\n" << endl;
	
	Positron p(P,Pi);

	boleano = false;
	i = 0;
	
	while(!boleano)
	{
		list<Particle*> l1 = p.Interact(boleano,inter);

		for (std::list<Particle*>::iterator i = l1.begin(); i != l1.end(); ++i)
		{
			(*i)->Print();
			delete *(i);
		}
		
		if(!boleano)
			p.Print();
		else
			cout << "ANNIHILATED!!!!" <<endl;
		i++;

		cout << "\n\niteração completa: " << i << " boleano: " << boleano << endl;
	}

	cout << "N interações: " << i << endl;
	
	cout << "\n\n\n================================\n\n\n"<<endl;

	cout << "N PairProduction: " <<inter.PairProduction <<endl;
	cout << "N BremRad: " <<inter.BremRad  <<endl;
	cout << "N PosAnnihilation: " <<inter.PosAnnihilation  <<endl;


	// ElePosFunctor a(false);

	// a.SetSigma(495);
	// a.SetParticleEnergy(495);

	// cout << a.I.Eval(13) << endl;
	// cout <<	a.gamma.Eval(495)<<endl;
	// cout <<	a.beta.Eval(495)<<endl;
	// cout <<	a.dEdx.Eval(495)<<endl;

	return 0;
}