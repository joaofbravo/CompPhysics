#include "OpticalMat.h"

using namespace std;

OpticalMat::OpticalMat(string fname, Double_t fdens, const vector<pair<float,float> > &refindex, TF1* fitf) : Material(fname,fdens), RefIndex(refindex){
	
	lambda = new float[RefIndex.size()];
	n = new float[RefIndex.size()];
	
	for (int i = 0; i < RefIndex.size(); ++i)
		lambda[i] = RefIndex[i].first;

	for (int i = 0; i < RefIndex.size(); ++i)
		n[i] = RefIndex[i].second;

	if (fitf)
		f = new TF1(*fitf);
	else if (name == "Diamante"){
		f = new TF1("fit", this, &OpticalMat::FitRefIndex, 2.39, 2.70, 5);
		f->SetParameters(0.0, 0.0, 0.0, 0.0, 0.0);
	} else 
		f = nullptr;

	cFC = nullptr;
	gr = nullptr;
	
	cout << __PRETTY_FUNCTION__ << endl;
}

OpticalMat::~OpticalMat()
{
	if(f) 		delete f;
	if(lambda) 	delete lambda;
	if(n)	 	delete n;
	if(cFC) 	delete cFC;
	if(gr) 		delete gr;

	cout << __PRETTY_FUNCTION__ << endl;
}

void OpticalMat::SetRefIndex(const vector<pair<float,float> > &data)
{
	RefIndex = data;

	if(lambda) 	delete lambda;
	if(n) 		delete n;

	lambda = new float[RefIndex.size()];
	n = new float[RefIndex.size()];
	
	for (int i = 0; i < RefIndex.size(); ++i)
		lambda[i] = RefIndex[i].first;

	for (int i = 0; i < RefIndex.size(); ++i)
		n[i] = RefIndex[i].second;
	
	cout << __PRETTY_FUNCTION__ << endl;
}

vector<pair<float,float> >& OpticalMat::GetRefIndex()
{
	cout << __PRETTY_FUNCTION__ << endl;
	return RefIndex;
}

void OpticalMat::SetFitRefIndex(TF1* func)
{
	if (f) delete f;
	f = new TF1(*func);

	cout << __PRETTY_FUNCTION__ << endl;
}

TF1* OpticalMat::GetFitRefIndex()
{
	TF1* f0 = new TF1(*f);
	
	cout << __PRETTY_FUNCTION__ << endl;
	return f0;
}

void OpticalMat::DrawRefIndexPoints()
{
	if (cFC) delete cFC;
	if (gr)  delete gr;
	
	cFC = new cFCgraphics();
	
	gr = new TGraph(RefIndex.size(), lambda, n);
	gr->SetMarkerStyle(20);

	cFC->AddObject(gr);
	cFC->Draw();

	cout << __PRETTY_FUNCTION__ << endl;
}

void OpticalMat::DrawFitRefIndex()
{
	if (cFC) delete cFC;
	if (gr)  delete gr;
	
	cFC = new cFCgraphics();
	
	gr = new TGraph(RefIndex.size(), lambda, n);
	gr->SetMarkerStyle(20);
	gr->Fit(f);

	cFC->AddObject(gr);
	cFC->Draw();

	cout << __PRETTY_FUNCTION__ << endl;
}

void OpticalMat::Print(string Out_file)
{
	Material::Print();

	vector<pair<float,float> >::iterator Vit;
	
	for(Vit = RefIndex.begin(); Vit != RefIndex.end(); Vit++)
		cout << "n(" << Vit->first << ") = " << Vit->second << endl;
	cout << endl;
	
	Double_t* par = f->GetParameters();

	cout << "Parameters:" << endl;

	for (int i = 0; i < f->GetNpar(); ++i)
		cout << "p(" << i << ") = " << par[i] << endl;
	cout << endl;

	cFC->Print(Out_file);

	cout << __PRETTY_FUNCTION__ << endl;
}


double OpticalMat::FitRefIndex(double* x, double* par)
{
	if (name == "Diamante")
	{
		cout <<__PRETTY_FUNCTION__ << name << endl;
		return par[0] + par[1]/(x[0]*x[0]-0.028) + par[2]/(x[0]*x[0]-0.028)/(x[0]*x[0]-0.028) + par[3]*x[0]*x[0] + par[4]*x[0]*x[0]*x[0]*x[0];
	} else
	return 0;
}