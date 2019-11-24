#include "PDFgenerator.h"
#include "PositronFunctor.h"
#include "TH1F.h"
#include "TPad.h"
#include "cFCgraphics.h"
#include "Spline3Interpolator.h"
#include "TGraph.h"

int main()
{

	cFCgraphics G;
	PositronFunctor funcs;

	double E = 0.00005;

	funcs.dsigmadu2D.SetTitle("diferencial da seccao eficaz;u;E (MeV); d #sigma / d u");

	TPad* pad0 = G.CreatePad("pad0");
	G.AddObject(&funcs.dsigmadu2D, "pad0","surf1");
	G.AddObject(pad0);

	funcs.dsigmadu.SetTitle("diferencial da seccao eficaz;u; d #sigma / d u");
	funcs.SetEnergy(E);

	funcs.Auxiliar.SetLineColor(kBlue);

	TPad* pad1 = G.CreatePad("pad1");
	G.AddObject(&funcs.Auxiliar, "pad1");
	G.AddObject(&funcs.dsigmadu, "pad1","same");
	G.AddObject(pad1);


	TPad* pad2 = G.CreatePad("pad2");
	G.AddObject(&funcs.InvAuxiliar, "pad2");
	G.AddObject(pad2);

	double fgamma = funcs.gamma.Eval(E);
	double min = 1/(1+ fgamma + sqrt(fgamma*fgamma - 1));

	TH1F hist("hist","cenas da vida",200,min,0.5);
	for (int i = 0; i < 1000000; ++i)
		hist.Fill(funcs.gen0.AcceptanceRejection(funcs.Auxiliar,funcs.InvAuxiliar));

	TPad* pad3 = G.CreatePad("pad3");
	G.AddObject(&hist, "pad3");
	G.AddObject(pad3);

	G.Draw();

}