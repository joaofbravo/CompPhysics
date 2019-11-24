#include "ODEdrawer.h"
#include "TH2D.h"
#include "TAxis.h"
#include <iostream>

using namespace std;

int ODEdrawer::padcounter = -1;

ODEdrawer::ODEdrawer() {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ODEdrawer::~ODEdrawer(){
	for (vector<TGraph*>::iterator vit1 = graph.begin(); vit1 != graph.end(); ++vit1)
		delete *vit1;

	for (vector<TGraph2D*>::iterator vit2 = graph2d.begin(); vit2 != graph2d.end(); ++vit2)
		delete *vit2;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ODEdrawer::AddPad(const vector< vector<ODEpoint> >& vec, int x, int y, string title, string type, const vector<Color_t>& ODEclr, vector<TF1> f, const vector<Color_t>& TF1clr)
{
	padcounter++;

	int Npoints = 5000;

	int Nsets = vec.size();
	int size[Nsets];
	vector<double*> ey(Nsets);
	vector<double*> ex(Nsets);
	double ymax = 0.;
	double ymin = 0.;

	for (int i = 0; i < Nsets; ++i) {
		int k = 0;

		for (int j = 0; j < vec[i].size(); k++, j+= 1 + vec[i].size()/Npoints)
			{;}
		
		size[i] = k;
		ey[i] = new double[size[i]];
		ex[i] = new double[size[i]];
	}

	for (int i=0; i < Nsets; i++){
		for (int j = 0,k = 0; j < vec[i].size(); k++, j+= 1 + vec[i].size()/Npoints) {
			ey[i][k] = vec[i][j][y];
			ex[i][k] = vec[i][j][x];

			if(ey[i][k] > ymax)
				ymax = ey[i][k];
			if(ey[i][k] < ymin)
				ymin = ey[i][k];

			// cout << vec[i][j][y] << " " << vec[i][j][x] << endl;
		}
		// cout << endl;
	}

	string name("pad");
	name += std::to_string(padcounter);
	TPad* pad = C.CreatePad(name.c_str());

	for (int i = 0; i < Nsets; ++i) {
		graph.push_back(new TGraph(size[i], ex[i], ey[i]));
		graph[graph.size()-1]->SetTitle(title.c_str());
		graph[graph.size()-1]->SetMarkerStyle(20);
		graph[graph.size()-1]->SetMarkerSize(0.5);
		graph[graph.size()-1]->SetLineWidth(2);

		if (i < ODEclr.size()){
			graph[graph.size()-1]->SetMarkerColor(ODEclr[i]);
			graph[graph.size()-1]->SetLineColor(ODEclr[i]);
		}
		else {
			graph[graph.size()-1]->SetMarkerColor(kRed+2);
			graph[graph.size()-1]->SetLineColor(kRed+2);
		}

		if (i == 0) {
			graph[graph.size()-1]->SetMaximum(ymax + (ymax-ymin)/15);
			graph[graph.size()-1]->SetMinimum(ymin - (ymax-ymin)/15);
		}
		else if (i == 1)
			type.erase (type.find("A"), type.find("A")+1);

		C.AddObject(graph[graph.size()-1], name.c_str(), type.c_str());
	}

	for (int i = 0; i < f.size(); ++i) {
		f[i].SetLineWidth(2);

		if (i < TF1clr.size())
			f[i].SetLineColor(TF1clr[i]);
		else
			f[i].SetLineColor(kBlack);

		C.AddObject(&(f[i]), name.c_str(), "same");
	}

	C.AddObject(pad);

	cout << "--- " << name << " Content: ---" << endl;
	C.DumpPad(name.c_str());
	cout << "---------------------" << endl;

	for (int i = 0; i < Nsets; ++i) {
		delete[] ey[i];
		delete[] ex[i];
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ODEdrawer::AddPad(const vector< vector<ODEpoint> >& vec, int x, int y, int z, string title, string type, const vector<Color_t>& ODEclr)
{
	padcounter++;

	int Npoints = 5000;

	int Nsets = vec.size();
	int size[Nsets];
	vector<double*> ez(Nsets);
	vector<double*> ey(Nsets);
	vector<double*> ex(Nsets);
	double zmax = 0.;
	double zmin = 0.;

	for (int i = 0; i < Nsets; ++i) {
		int k = 0;
		
		for (int j = 0; j < vec[i].size(); k++, j+= 1 + vec[i].size()/Npoints)
			{;}

		size[i] = k;
		ez[i] = new double[size[i]];
		ey[i] = new double[size[i]];
		ex[i] = new double[size[i]];
	}

	for (int i=0; i < Nsets; i++){
		for (int j = 0, k = 0; j < vec[i].size(); k++, j+= 1 + vec[i].size()/Npoints) {
			ez[i][k] = vec[i][j][z];
			ey[i][k] = vec[i][j][y];
			ex[i][k] = vec[i][j][x];

			if(ez[i][k] > zmax)
				zmax = ez[i][k];
			if(ez[i][k] < zmin)
				zmin = ez[i][k];

			// cout << vec[i][j][z] << " " << vec[i][j][y] << " " << vec[i][j][x] << endl;
		}
		// cout << endl;
	}

	string name("pad");
	string numb = std::to_string(padcounter);
	name += numb;
	TPad* pad = C.CreatePad(name.c_str());

	for (int i = 0; i < Nsets; ++i) {
		graph2d.push_back(new TGraph2D(size[i], ex[i], ey[i], ez[i]));
		graph2d[graph2d.size()-1]->SetTitle(title.c_str());
		graph2d[graph2d.size()-1]->SetMarkerStyle(20);
		graph2d[graph2d.size()-1]->SetMarkerSize(0.5);
		graph2d[graph2d.size()-1]->SetLineWidth(2);

		if (i < ODEclr.size()){
			graph2d[graph2d.size()-1]->SetMarkerColor(ODEclr[i]);
			graph2d[graph2d.size()-1]->SetLineColor(ODEclr[i]);
		}
		else {
			graph2d[graph2d.size()-1]->SetMarkerColor(kRed+2);
			graph2d[graph2d.size()-1]->SetLineColor(kRed+2);
		}

		if (i == 0) {
			// Não funciona
			// graph2d[graph2d.size()-1]->GetZaxis()->SetLimits(zmin - (zmax-zmin)/15,zmax + (zmax-zmin)/15); 
		}
		else if (i == 1)
			type += " same";

		C.AddObject(graph2d[graph2d.size()-1], name.c_str(), type.c_str());
	}

	C.AddObject(pad);

	cout << "--- " << name << " Content: ---" << endl;
	C.DumpPad(name.c_str());
	cout << "---------------------" << endl;

	for (int i = 0; i < Nsets; ++i) {
		delete[] ez[i];
		delete[] ey[i];
		delete[] ex[i];
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Spline3Interpolator ODEdrawer::GetSpline(const vector<ODEpoint>& vec, int x, int y)
{
	int Npoints = 500;

	double *ay =nullptr;
	double *ax = nullptr;

	int size = 0;
	int inc = 1 + vec.size()/Npoints;

	for (int j = 0; j < vec.size(); size++, j+=inc)
		{;}

	ay = new double[size];
	ax = new double[size];

	for (int j = 0,k = 0; j < vec.size(); k++, j+=inc) 
	{
		ay[k] = vec[j][y];
		ax[k] = vec[j][x];
	}

	return Spline3Interpolator(size,ax,ay);
}

void ODEdrawer::Draw() {
	C.ListObjects();
	C.Draw();

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ODEdrawer::Print(string print) {
	C.Print(print);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}