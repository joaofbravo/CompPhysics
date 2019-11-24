#include "Interpolator.h"
#include "TF1.h"
#include "TGraph.h"
#include <iostream>

int Interpolator::funccounter = 0;

Interpolator::Interpolator(int fN, double *fx, double *fy, TF1* f0) : DataPoints(fN, fx, fy)
{
	funccounter++;

	if(N > 0) {
		string name("FInterpolator");
		name += std::to_string(funccounter);

		FInterpolator = new TF1(name.c_str(), this, &Interpolator::fInterpolator, fx[0], fx[N-1], 0);
	}
	else 
		FInterpolator = nullptr;

	if(f0)
	{
		F0 = new TF1(*f0);
		F0->SetRange(fx[0], fx[N-1]);
	}
	else
		F0 = nullptr;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Interpolator::Interpolator(int fN, double *fx, double *fy, TF1& f0) : DataPoints(fN, fx, fy)
{
	funccounter++;
	
	if(N > 0) {
		string name("FInterpolator");
		name += std::to_string(funccounter);

		FInterpolator = new TF1(name.c_str(), this, &Interpolator::fInterpolator, fx[0], fx[fN-1], 0);
	}
	else 
		FInterpolator = nullptr;

	F0 = new TF1(f0);
	F0->SetRange(fx[0], fx[fN-1]);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Interpolator::Interpolator(const Interpolator& interpol) : DataPoints(interpol.N, interpol.x, interpol.y)
{
	funccounter++;

	if(N > 0) {
		string name("FInterpolator");
		name += std::to_string(funccounter);

		FInterpolator = new TF1(name.c_str(), this, &Interpolator::fInterpolator, x[0], x[N-1], 0);
	}
	else 
		FInterpolator = nullptr;

	if(interpol.F0)
	{
		F0 = new TF1(*interpol.F0);
		F0->SetRange(x[0], x[N-1]);
	}
	else
		F0 = nullptr;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Interpolator::~Interpolator()
{
	if(FInterpolator)	delete FInterpolator;
	if(F0)				delete F0;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Interpolator::SetDataPoints(int fN, double* fx, double* fy)
{
	DataPoints::SetDataPoints(fN,fx,fy);
	
	if (fN > 0){
		FInterpolator->SetRange(x[0], x[N-1]);
		
		if(F0)
			F0->SetRange(x[0], x[N-1]);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Interpolator::SetFunction(TF1& f) {
	if(F0)
		delete F0;

	F0 = new TF1 (f);
	F0->SetRange(x[0], x[N-1]);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

const TF1& Interpolator::GetInterpolationFunction() const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *FInterpolator;
}

void Interpolator::Draw() const {
	if(N < 2)
	{
		cout << __PRETTY_FUNCTION__ << ": ERROR! Please set more than one data point." << endl;
		return;
	}

	cFCgraphics G;

	TGraph *g = new TGraph(N,x,y);
	g->SetMarkerStyle(20);
	g->SetMarkerColor(kBlack);
	g->SetMarkerSize(1);
	g->SetTitle("DataPoints + Interpolated Function;x;y");

	TPad *pad1 = G.CreatePad("pad1");
	G.AddObject(g,"pad1","AP");
	G.AddObject(FInterpolator,"pad1","same");
	G.AddObject(pad1);

	if(F0) {
		string title = "Underlying function: ";
		title += (string) F0->GetExpFormula();
		title += ";x;y";

		F0->SetTitle(title.c_str());

		TPad *pad2 = G.CreatePad("pad2");
		G.AddObject(F0,"pad2");
		G.AddObject(pad2);
	}

	G.Draw();

	if(g) delete g;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Interpolator::Print(string FILE) const {
	if(F0)
		cout << "Underlying Function: " << F0->GetExpFormula() << endl;

	DataPoints::Print(FILE);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

double Interpolator::fInterpolator(double *var, double *par) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return Interpolate(var[0]);
}