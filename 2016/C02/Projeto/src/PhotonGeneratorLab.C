#include "PDFgenerator.h"
#include "PhotonFunctor.h"
#include "TH1F.h"
#include "TPad.h"
#include "cFCgraphics.h"
#include "Spline3Interpolator.h"
#include "TGraph.h"

using namespace std;

int main()
{
	PhotonFunctor funcs;
	cFCgraphics G;

	

	// funcs.SectionDiff2D.SetRange(0,5,1,5000);
	funcs.SectionDiff2D.SetTitle("SectionDiff;#epsilon;E #gamma (MeV); d #sigma / d #epsilon");

	TPad* pad0 = G.CreatePad("pad0");
	G.AddObject(&funcs.SectionDiff2D, "pad0","surf4");
	G.AddObject(pad0);

	TPad* pad1 = G.CreatePad("pad1");
	G.AddObject(&funcs.Auxiliar2D, "pad1","surf1");
	G.AddObject(pad1);



	TF1 conc("conc","x < 25? 0.49 : x < 50? 0.25 :   x < 80? 0.24 :  x < 125 ? 0.22 : x < 250 ? 0.19 : x < 500 ? 0.16 : x < 1000 ? 0.13 : x < 2000 ? 0.1 : x < 3000 ? 0.07 : 0.06 ",0,5000);

	TPad* pad2 = G.CreatePad("pad2");
	G.AddObject(&conc,"pad2");
	// G.AddObject(pad2);


	TF1 k("k","x < 25? 0.5 : x < 50? 0.20 + (0.5-0.2) * (x - 50) /(25-50) :   x < 80? 0.16 + (0.20-0.16) * (x - 80) /(50-80) : x < 125? 0.12 + (0.16-0.12) * (x - 125) /(80-125) : x < 500? 0.09 + (0.12-0.09) * (x - 500) /(125-500) : 0.04 + (0.09-0.04) * (x - 5000) /(500-5000) ",0,5000);

	TPad* pad3 = G.CreatePad("pad3");
	G.AddObject(&k,"pad3");
	// G.AddObject(pad3);


	
	TF1 aux("aux","x < [0] ? [1]: x < 1-[0] ? [2]*cosh(TMath::ACosH([1]/[2])/([0]-0.5)*(x-0.5)): [1] ",0,1);

	TF2 plane = funcs.SectionDiff2D;

	double E = 1333.333333;

	// cout << k.Eval(E) << endl;
	aux.SetParameters(conc.Eval(E),plane.Eval(k.Eval(E),E)+0.44,plane.Eval(0.5,E)+0.44);
	aux.SetLineColor(kBlue);
	
	funcs.SectionDiff.SetParameter(0,E);

	TPad* pad4 = G.CreatePad("pad4");
	G.AddObject(&funcs.SectionDiff, "pad4"/*,"same"*/);
	G.AddObject(&aux, "pad4");

	G.AddObject(pad4);




	funcs.SetEnergy(E);

	TPad* pad5 = G.CreatePad("pad5");
	funcs.InvAuxiliar.SetMarkerStyle(20);
	funcs.InvAuxiliar.SetMarkerSize(0.5);
	// funcs.InvAuxiliar.SetRange(0.89,0.93);
	G.AddObject(&funcs.InvAuxiliar, "pad5","pcol");

	G.AddObject(pad5);

	// cout << funcs.gen0.AcceptanceRejection(funcs.Auxiliar,funcs.InvAuxiliar) << endl;

	TH1F hist("hist","geracao marada",200,0,1);
	for (int i = 0; i < 1000000; ++i)
		hist.Fill(funcs.gen0.AcceptanceRejection(funcs.Auxiliar,funcs.InvAuxiliar));
	
	
	TPad* pad6 = G.CreatePad("pad6");
	G.AddObject(&hist, "pad6");
	G.AddObject(pad6);

	const double me = 0.5109989461;
	
	double Beta = sqrt(E*(E+2*me))/(E+me);

	funcs.dNdx.SetParameter(0,Beta);
	funcs.InvdNdx.SetParameter(0,Beta);

	TPad* pad7 = G.CreatePad("pad7");
	G.AddObject(&funcs.dNdx, "pad7");
	G.AddObject(pad7);



	TRandom3 R(0);
	TH1F hist0("hist0","cossenos",200,0,1);
	for (int i = 0; i < 1000000; ++i)
		hist0.Fill(funcs.InvdNdx.Eval(R.Uniform()));
	
	
	TPad* pad8 = G.CreatePad("pad8");
	G.AddObject(&hist0, "pad8");
	G.AddObject(pad8);

	G.Draw();
	G.Print("execs/PhotonDCS.pdf");

	/*for (double x = 5; x <= 5000; x+=1)
	{
		funcs.Auxiliar.SetParameter(0,x);
		funcs.gen0.GetFunction().SetParameter(0,x);
		
		double y = 0;
		if(!funcs.gen0.AuxTester(funcs.Auxiliar,y,1e-4))
		{
			cout << "It failed for E = " << x << endl;
			exit(1);
		}
		else
			cout << "It worked for E = " << x << endl;
	}*/

	return 0;		
}