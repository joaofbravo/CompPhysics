#include "FCtools.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

double FCtools::RoundOffError(int i){
	if (i < 0){
		std::cout << "Please insert a non negative integer." << std::endl;
		exit (1);
	}

	return fabs(((double)sqrt(i) - (float)sqrt(i)) / (double)sqrt(i));
}

TGraph* FCtools::RoundOffErrorG(int imin, int imax){
	double i[imax - imin + 1];
	double rel_error[imax - imin + 1];

	for (int j = imin; j < imax + 1; ++j) {
		i[j - imin] = j;
		rel_error[j - imin] = RoundOffError(j);
	}

	TGraph* gr = new TGraph (imax - imin, i, rel_error);

	return gr;
}

TH1D* FCtools::RoundOffErrorH(int imin, int imax){
	TH1D* hist = new TH1D ("histerror", "Square Root Relative Errors", (imax - imin) / 10, 0, 60e-9);

	for (int i = imin; i < imax + 1; ++i)
		hist->Fill(RoundOffError(i));

	return hist;
}