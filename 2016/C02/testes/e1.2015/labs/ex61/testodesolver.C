#include "ODEsolver.h"
#include "ODEdrawer.h"
#include "TMath.h"
#include "Func1D.h"
#include <iostream>

using namespace std;

int main() {

	vector<TFormula> v;
	v.push_back(TFormula("1","x[2]"));
	v.push_back(TFormula("2","-4*x[1]-2*x[2]"));
	ODEsolver test(v);
 	
 	//lambda = 2
 	//w0^2 = 4
 	//teta(t) = A*exp(-lamda*x/2)*cos(sqrt(w0^2- lambda ^2/4)*x + phi0)

	vector<TF1> vtf1(1, TF1("f1","sqrt(1+1./3.)*exp(-1*x)*cos(sqrt(4-1)*x - atan(1./sqrt(3)))", 0, 5));

	Vec i(3,0.);
	i[0] = 0.;
	i[1] = 1;
	i[2] = 0;

	double step = 0.001;

	// colors
	vector<Color_t> clr1(1, kGreen);
	clr1.push_back(kRed);
	clr1.push_back(kBlue);
	clr1.push_back(kPink);

	// points
	vector<ODEpoint> vRK4 = test.RK4(i, step, 5);
	vector<ODEpoint> vRK2 = test.RK2(i, step, 5);
	vector<ODEpoint> vPC = test.PredictorCorrector(i, step, 5);
	vector<ODEpoint> vE = test.Euler(i, step, 5);

	vector< vector<ODEpoint> > vvec;
	vvec.push_back(vRK4);
	vvec.push_back(vRK2);
	vvec.push_back(vPC);
	vvec.push_back(vE);

	// draw 1D
	ODEdrawer a;

	vvec[0]=vRK4;
	a.AddPad(vvec, 0, 1, "RK4;x;y", "AP", clr1, vtf1);

	a.Draw();
	a.Print("execs/teste.pdf");
	Spline3Interpolator Spline(a.GetSpline(vRK4,0,1));

	Func1D f(Spline.GetInterpolationFunction());
	f.Draw("Pendulo Linear");

	return 0;
}