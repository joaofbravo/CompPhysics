#include "TF1.h"
#include "cFCgraphics.h"
#include "TH1F.h"
#include "PhotonFunctor.h"
#include "PositronFunctor.h"
#include "ElePosFunctor.h"
#include "Integrator.h"
#include "TRandom3.h"



ElePosFunctor Func(true);
double funcAuxiliar(double* var, double* par);
double funcSigma(double* var, double* par);


int main()
{
	cFCgraphics G;
	TRandom3 R(0);

	/*double E = 1000;
	Func.SetEnergy(E);

	Integrator Integ0(0,1,Func.SectionDiff);
	Integrator Integ1(0,1,Func.Auxiliar);

	cout << "Efficiency: " << Integ0.SimpsonAdaptative(1e-6)/Integ1.SimpsonAdaptative(1e-6) << endl;

*/

	TPad* pad1 = G.CreatePad("pad1");
	// Func.Auxiliar.SetLineColor(kBlue);
	
	TF1 Auxiliar("Auxiliar",funcAuxiliar,1,5000);
	Auxiliar.SetLineColor(kRed);
	Auxiliar.SetTitle("Funtion: Perda de Energia continua por unidade de distancia; E(Mev); dE/dx(MeV.cm^{-1}) ");

	G.AddObject(&Auxiliar, "pad1");
	// G.AddObject(&Func.Auxiliar, "pad1","same");
	G.AddObject(pad1);


	
	/*TH1F hist ("hist","Histogram: Distribuicao do cos(theta) dos fotoes; cos(#theta) ; N hits", 100, 0, 1);

	TF1 ajuste("ajuste", funcAuxiliar, 0., 1,  1);

	for (int i = 0; i < 1e7; ++i)
		hist.Fill(Func.gen0.AcceptanceRejection(Func.Auxiliar,Func.InvAuxiliar));

	hist.SetMarkerStyle(33);
	hist.SetMarkerSize(1);
	hist.Fit("ajuste");

	TPad* pad2 = G.CreatePad("pad2");
	G.AddObject(&hist, "pad2","P");
	// G.AddObject(&ajuste, "pad2","same");
	
	G.AddObject(pad2);
*/
	G.Draw();
	G.Print("plots/dEdxPositron.pdf");






	return 0;
}

double funcAuxiliar(double* var, double* par)
{

	Func.SetSigma(var[0]);
	Func.SetParticleEnergy(var[0]);

	return Func.dEdx.Eval(var[0]);
}
