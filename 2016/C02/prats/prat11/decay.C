#include "TF1.h"
#include "TH1F.h"
#include "TMath.h"
#include "TRandom.h"

class Decay {
public:
	Decay(double decaytime =87.7) : tau(decaytime) {;}
	double GetDecayTime()
	{
		return -tau*TMath::Log(gRandom->Uniform());
	}

	double GetDecayTimeAC()
	{
		// Random time
		double t = gRandom->Uniform(0,1000.);
		// compute function
		double f = TMath::Exp(-t/tau);
		//accept or not?
		if(gRandom->Uniform() < f)
			return t;
		else
			return GetDecayTimeAC();
	}

private:
	double tau; //years
};

void decay()
{
	Decay D;
	TH1F *h = new TH1F("decayh", "decay time", 100, 0., 250.);
	
	for (int i = 0; i < 10000; ++i)
		h->Fill(D.GetDecayTime());
	h->DrawCopy();

	TH1F *g = new TH1F("decayg", "decay time", 100, 0., 250.);
	
	for (int i = 0; i < 10000; ++i)
		g->Fill(D.GetDecayTime());

	g->SetMarkerStyle(20);
	g->DrawCopy("sameE");
}