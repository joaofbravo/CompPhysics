#include "DataPoints.h"
#include "TGraph.h"
#include <fstream>
#include <iostream>

DataPoints::DataPoints(int fN, double* fx, double* fy)
{
	if(fN > 0)
	{
		N = fN;
		x = new double[N];
		y = new double[N];
		
		for (int i=0; i<N; i++) {
			x[i] = fx[i];
			y[i] = fy[i];
		}
	}
	else
	{
		N = 0;
		x = nullptr;
		y = nullptr;
		cout << "Atention! You introduced a non-positive number of points. Will use default constructor." << endl;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

DataPoints::~DataPoints() {
	if(x) delete[] x;
	if(y) delete[] y;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void DataPoints::SetDataPoints(int fN, double* fx, double* fy)
{
	if(fN > 0)
	{
		N = fN;
		if(x) delete [] x;
		if(y) delete [] y;

		x = new double[N];
		y = new double[N];

		for (int i=0; i<N; i++) {
			x[i] = fx[i];
			y[i] = fy[i];
		}
	}
	else
		cout << "Atention! You introduced a non-positive number of points. Nothing will be done." << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void DataPoints::Draw() const {
	cFCgraphics G;

	TGraph *g = new TGraph(N,x,y);
	g->SetMarkerStyle(20);
	g->SetMarkerColor(kBlack);
	g->SetMarkerSize(1);

	TPad *pad1 = G.CreatePad("pad1");
	G.AddObject(g,"pad1","AP");
	G.AddObject(pad1);
	G.Draw();

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void DataPoints::Print(string FILE) const {
	ofstream F(FILE);

	cout << "File: " << FILE << endl;

	if(F.is_open())
	{
		for (int i = 0; i < N; ++i)
			F << x[i] << " " << y[i] << endl; 
	}
	else
		cout << endl << endl << "ERROR! Could not open the file." << endl;

	cout << "DataPoints:" << endl;

	for (int i = 0; i < N; ++i)
		cout << x[i] << " " << y[i] << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}