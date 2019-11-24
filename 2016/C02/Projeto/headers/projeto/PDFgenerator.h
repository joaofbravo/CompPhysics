#ifndef __PDFgenerator__
#define __PDFgenerator__

#include "TF1.h"
#include "TRandom3.h"

class PDFgenerator {
public:
	PDFgenerator(TF1* pdf =nullptr,unsigned int seed =0);
	PDFgenerator(TF1& pdf, double xmin =0, double xmax =1, unsigned int seed =0);

	~PDFgenerator();

	void SetFunction(TF1& func);
	// void SetLimits(double xmin =0, double xmax =1);
	void SetSeed(unsigned int seed);


	TF1& GetFunction();


	//recursive method, that generates a random at a time; set function first
	double AcceptanceRejection(const TF1& aux, const TF1& inv);

	//x will be the maximum abscissa until which the method ran
	bool AuxTester(const TF1& aux, double& x, double precision =1e-6);
	int GetN() const;

private:
	static int N;
	TRandom3 R;

	TF1* F0;
	double a;
	double b;
};

#endif