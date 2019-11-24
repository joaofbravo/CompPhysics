#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TFile.h"

void mRoot1()
{
	TH1F **h= new TH1F*[5];
	h[0] =  new TH1F("Histogram0","My first histogram",100,-10,10); // xbins, xmin, xmax 
	h[1] =  new TH1F("Histogram1","My second histogram",100,-10,10);
	h[2] =  new TH1F("Histogram2","My third histogram",100,-10,10);

	//TF1 *f1 = new TF1("f1","x",-5,5);
	TF1 *f2 = new TF1("f2","2*x*x", -10, 10);
	TF1 *f3 = new TF1("f3","1./sqrt(2*TMath::Pi()*[0])*exp(-0.5*(x/[0])*(x/[0]))", -10, 10);
	TF1 *f[2];

	f[0] = new TF1("f4","[0]*sin(x)/x", 0, TMath::TwoPi());
	f[1] = new TF1("f5","[0]*x*x*x*x+[1]*x*x-2", -4, 4);
	
	f[0]->SetParameter(0,10);
	f[1]->SetParameter(0,4); //podia ser f[1]->SetParameters(4,2)
	f[1]->SetParameter(1,2);
	f3->SetParameter(0,1);
	
	for (int i=0; i<10000; i++)
	{
		h[0]->Fill(gRandom->Uniform(-5,5));
		h[1]->Fill(f2->GetRandom());
		h[2]->Fill(f3->GetRandom());
	}

	cout << "Hist1 nº of bins: " << h[0]->GetNbinsX() << endl;
	cout << "Hist2 nº of bins: " << h[1]->GetNbinsX() << endl;
	cout << "Hist3 nº of bins: " << h[2]->GetNbinsX() << endl;

	TCanvas *c = new TCanvas ("c", "My first canvas", 1200, 800);
	c->Divide(3,2); //(Nx, Ny)
	
	c->cd(1);
	h[0]->DrawCopy();
	
	c->cd(2);
	h[1]->DrawCopy();
	
	c->cd(3);
	h[2]->DrawCopy();
	
	c->cd(4);
	f[0]->DrawCopy();
	
	c->cd(5);
	f[1]->DrawCopy();

	// Passar para ficheiro
	TFile o31("Output31.root","RECREATE");
	o31.cd();

	for(int i=0; i<3;i++)
		h[i]->Write();

	for(int i=0; i<2; i++)
		f[i]->Write();

	o31.ls(); // show contents
	o31.Close();

	// for (int i = 0; i < 3; ++i)
	// 	delete h[i];

	// delete[] h;
	// delete f2;
	// delete f3;
	// delete f[0];
	// delete f[1];
}