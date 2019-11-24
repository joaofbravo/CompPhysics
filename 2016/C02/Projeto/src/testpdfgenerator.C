#include "PDFgenerator.h"
#include "TH1F.h"
#include "TPad.h"
#include "cFCgraphics.h"

int main()
{
	double a = 0;
	double b = 3;
	double d = -1;
	double c = 1;

	TF1 f("f", "[1]*TMath::Abs(cos(x))*exp(-[0]*x)",a,b);
	f.SetParameter(0,1);
	f.SetParameter(1,1);

	//[a,b] -> c*exp(-d*x);
	//inv -> log[1-yexp(-d*a) - y * exp(-d*b)]/(-d);

	TF1 aux("aux","[3]*exp([2]*x)",a,b);

	TF1 inv("inv","log((1-x)*exp([2]*[0]) + x*exp([2]*[1]))/([2])",0,1);

	// cout << inv.Eval(0.1) << endl;

	//par: [0] -> a; [1] -> b; [2] -> d; [3] -> c;
	double par[] = {a,b,d,c};
	aux.SetParameters(par);
	inv.SetParameters(par);

	// cout << inv.Eval(0.1) << endl;

	TH1F hist("hist","Teste",100,a,b);

	//--------------------

	PDFgenerator gen(f,a,b);

	double x = 0;
	if(gen.AuxTester(aux,x))
		cout <<"The auxiliar function is good!"  << endl;
	else
		cout <<"The auxiliar function worked for x < " << x <<endl;

	for (int i = 0; i < 10000000; ++i)
		hist.Fill(gen.AcceptanceRejection(aux,inv));

	cFCgraphics G;

	TPad* pad1 = G.CreatePad("pad1");
	TPad* pad2 = G.CreatePad("pad2");
	TPad* pad3 = G.CreatePad("pad3");

	f.SetLineColor(kBlue);
	aux.SetLineColor(kGreen);
	inv.SetLineColor(kBlack);

	G.AddObject(&hist,"pad1");
	G.AddObject(&f,"pad2");
	G.AddObject(&aux,"pad2","same");
	G.AddObject(&inv,"pad3");

	G.AddObject(pad1);
	G.AddObject(pad2);
	G.AddObject(pad3);

	hist.Fit("f");

	G.Draw();
	
	cout << "\n\nN: " << gen.GetN() << " calls..." << endl << endl;

	return 0;
}