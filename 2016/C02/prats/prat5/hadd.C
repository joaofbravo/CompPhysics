#include "TROOT.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TRandom.h" //gRandom
#include "TStyle.h" //gStyle

void hadd() {
	gROOT->SetStyle("Plain");
	gStyle->SetOptStat(1111);
	gStyle->SetOptTitle(1); // =0 supress title box
	gStyle->SetOptFit(1111); // print fit results
	gStyle->SetPalette(1);

	TCanvas *c = new TCanvas();

	TH1F *hg = new TH1F("hg","histogram gauss", 100,1.,9.);
	for (int i=0; i<5000; i++)
		hg->Fill(gRandom->Gaus(5,1.));
	
	TH1F *he = new TH1F("he","histogram expo", 100,1.,9.);
	for (int i=0; i<5000; i++)
		he->Fill(gRandom->Exp(1.));

	TH1F *hsum = new TH1F(*hg); //dereference hg pointer
	hsum->Add(he,1.);
	
	he->GetYaxis()->SetRangeUser(0.,200.);
	he->SetFillColor(9);
	he->DrawCopy();
	hg->SetFillColor(kRed);
	hg->DrawCopy("same");
	hsum->SetMarkerStyle(20);
	hsum->SetMarkerColor(3);
	hsum->SetMarkerSize(1.2);
	
	hsum->Draw("Esame"); //draw with errors
}