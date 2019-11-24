#include "TROOT.h"
#include "MyFormula.h"
#include "TFormula.h"
#include "Spline3Interpolator.h"
#include "Func1D.h"
#include "TGraph.h"
#include <iostream>

using namespace std;

int MyFormula::fcounter = -1;

MyFormula::MyFormula(string form) {

	fcounter++;

	if(!form.empty())
	{
		string name = "formula";
		name += std::to_string(fcounter);
		F = TFormula(name.c_str(), form.c_str());
		expression = form;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__<<endl;
	#endif
}

MyFormula::~MyFormula(){
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__<<endl;
	#endif
}

void MyFormula::SetFormula(string form) {

	if(!form.empty())
	{
		string name = "formula";
		name += std::to_string(fcounter);
		F = TFormula(name.c_str(), form.c_str());
		expression = form;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__<<endl;
	#endif
}

void MyFormula::DrawAndSave(double xmin, double xmax){

	if (xmin > xmax) {
		double c = xmin;
		xmin = xmax;
		xmax = c;
	}

	// n intervalos
	double h = (xmax - xmin)/500.;

	// n+1 pontos
	double ey[501];
	double ex[501];
	double x;
	int i;

	for (i = 0, x = xmin; i < 501; ++i, x+=h) {
		ex[i] = x;
		ey[i] = F.Eval(x);
		// cout << ex[i] << "   " << ey[i] << endl;
	}

	cFCgraphics G;
	TGraph *g = new TGraph(501,ex,ey);
	g->SetMarkerStyle(20);
	g->SetMarkerColor(kBlack);
	g->SetMarkerSize(1);
	g->SetTitle(expression.c_str());

	G.AddObject(g);
	G.Draw();
	G.Print("MyFormula.pdf");

	delete g;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__<<endl;
	#endif
}