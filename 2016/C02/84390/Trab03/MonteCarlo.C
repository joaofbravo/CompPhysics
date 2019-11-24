#include "FCtools.h"
#include "FCmatrixFull.h"
#include "Spline3Interpolator.h"
#include <iostream>
#include "TF1.h"
#include "Integrator.h"
#include "TH1F.h"
#include "cFCgraphics.h"



using namespace std;

int main() {
	FCtools F;
	FCmatrixFull M (F.ReadFileToMatrix("brem.data"));

	int size = M.GetCol(1).size();
	double ey [size];
	double ex [size];

	// M.GetCol(0).Print();
	// M.GetCol(1).Print();

	for (int i = 0; i < size; ++i) {
		ey[i] = M.GetCol(1)[i];  // cout << ey[i] << " ";
		ex[i] = M.GetCol(0)[i];  // cout << ex[i] << endl;
	}

	Spline3Interpolator interpol(size, ex, ey);
	// interpol.Print();

	interpol.Draw();

	TF1 f(interpol.GetInterpolationFunction());
	f.SetRange(1,14);

	// (14-1)/100 = 0.13
	//procura pelo bin de 10MeV
	double bin = 0.;
	for (int i = 0; i < 100; ++i, bin+=0.13){
		if((bin+0.13) > 10)
			break; 
	}
	cout << bin << endl;

	double result, result2;
	double error, error2;

	Integrator simpson(bin, bin+0.13, f);
	simpson.SimpsonRule(10000, result, error);
	cout << result << " +- " << error << "\trelative: " << error/result << endl;

	Integrator simpson2(1., 14., f);
	simpson2.SimpsonRule(10000, result2, error2);
	cout << result2 << " +- " << error2 << "\trelative: " << error2/result2 << endl << endl;

	cout << "Prob in bin with 10MeV: " << result/result2 << endl;
	
	int N = 1./(0.01*0.01*result/result2);
	cout << "Number of events : " << N << endl << endl;

	TH1F* hist = new TH1F("hist", "Energies", 100, 1., 14.);

	for (int i = 0; i < N; ++i) {
		hist->Fill(f.GetRandom());
	}

	cFCgraphics C;
	C.AddObject(hist);
	
	C.Draw();
	C.Print("ElectronBrem.pdf");

	delete hist;

	return 0;
}