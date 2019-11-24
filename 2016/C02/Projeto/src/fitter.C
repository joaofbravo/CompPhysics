#include "FCtools.h"
#include "Spline3Interpolator.h"
#include "cFCgraphics.h"
#include "TF1.h"
#include "TPad.h"
#include "TGraph.h"

using namespace std;


int main()
{
	FCtools tools;
	cFCgraphics G;

	FCmatrixFull data = tools.ReadFileToMatrix("interpolateddata/showerslength.txt");

	double * ex= new double[data.size()];
	double * ey= new double[data.size()];


	for (int i = 0; i < data.size()-1; ++i)
	{
		ex[i] = data[i][0];
		ey[i] = data[i][1];
		// cout << ex[i] << " " << ey[i] <<endl;
	}

	TF1 teor("f","x/43",1000,5000);

	/*Spline3Interpolator spline(data.size()-1,ex,ey);
	TF1 FuncSpline (spline.GetInterpolationFunction());

	FuncSpline.SetLineColor(kBlue);
	FuncSpline.SetRange(1000,5000);*/
	teor.SetLineColor(kRed);

	TF1 fit("fit","x/[0] +[1]");

	fit.SetParameter(0,43);

	fit.SetLineColor(kGreen);

	TGraph graph(data.size()-1,ex,ey);
	graph.SetTitle("Heitler relation;E(MeV);N_{max}");
	graph.SetMarkerStyle(20);
	graph.SetMarkerSize(1);
	graph.Fit("fit");

	TPad* pad1 = G.CreatePad("pad1");

	G.AddObject(&graph,"pad1","AP");
	G.AddObject(&fit,"pad1","same");
	G.AddObject(&teor,"pad1","same");

	G.AddObject(pad1);

	G.Draw();
	G.Print("plots/Heitler.pdf");

	return 0;
}