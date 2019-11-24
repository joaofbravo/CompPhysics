#ifndef __ZeroFunctor__
#define __ZeroFunctor__

// author FB
// Fis Computacional 2016-17
// history - 15 Nov 2016: starting class

class TF1; //forward declaration

class ZeroFunctor {
public:
	ZeroFunctor(TF1* p=nullptr); //it works as default constructor
	~ZeroFunctor();
	double Bisection(double xmin, double xmax, double eps, int NI);

private:
	TF1* f;
};

#endif