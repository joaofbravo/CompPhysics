#include "kolmogorov.h"
#include "TH1F.h"
#include "cFCgraphics.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<double> fref(vector<double>&);

int main() {
	srand((unsigned int)time(NULL));

	vector<double> x (51, 0);

	for (int i = 0; i < 50; ++i)
		x[i+1] = x[i] + 0.1;

	/*
	double maxdif[1000000];

	for (int i = 0; i < 1000000; ++i){
		maxdif[i] = KolmogorovTest(Fobs(100, x, GetRandom), fref(x));
		//cout << "Kolomorov diference = " << maxdif[i] << endl;
	}
	*/
	TH1F* h = new TH1F("h", "KolmogorovTest", 1000, 0., 0.1);

	vector<double> ref = fref(x);
	for(int j=0; j<7000000; j++)
		h->Fill(KolmogorovTest(Fobs(1000, x, GetRandom), ref));

	cFCgraphics G;

	TPad* pad1 = G.CreatePad("pad1");

	G.AddObject(h,"pad1");
	G.AddObject(pad1); //ou h
	G.Draw();

	return 0;
}

vector<double> fref(vector<double> &x)
{
	vector<double>::iterator Vit;

	vector<double> res(x.size()-1, 0);
	
	int j = 0;
	
	double intmin = x[0] * x[0];
	
	double max = x[x.size()-1] * x[x.size()-1] - intmin;
	
	for (Vit = x.begin()+1; Vit != x.end() ; Vit++,j++)
		res[j] = ((*Vit)*(*Vit)-intmin)/max;
	
	return res; 
}