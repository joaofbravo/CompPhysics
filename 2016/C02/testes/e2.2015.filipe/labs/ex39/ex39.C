#include "FCtools.h"
#include "cFCgraphics.h"
#include <iostream>

using namespace std;

int main() {

	// for (int i = 1; i < 1001; ++i)
	// 	cout << "Erro de sqrt(" << i << "): " << FCtools::RoundOffError(i) << endl;

	cFCgraphics G;

	TGraph* gr = FCtools::RoundOffErrorG(1, 1000);
	TH1D* hist = FCtools::RoundOffErrorH(1, 1000);
	
	TPad* pad1 = G.CreatePad("pad1");
	TPad* pad2 = G.CreatePad("pad2");

	G.AddObject(gr,"pad1");
	G.AddObject(hist,"pad2");
	G.ListObjects();

	G.AddObject(pad1);
	G.AddObject(pad2);

	G.Draw();

	G.Print("save.png");

	delete gr;
	delete hist;

	return 0;
}