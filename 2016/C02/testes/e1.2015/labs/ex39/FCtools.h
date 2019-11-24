#ifndef __FCtools__
#define __FCtools__

#include "TGraph.h"
#include "TH1D.h"

class FCtools {
public:
	static double RoundOffError(int i);
	static TGraph* RoundOffErrorG(int imin, int imax);
	static TH1D* RoundOffErrorH(int imin, int imax);
};

#endif