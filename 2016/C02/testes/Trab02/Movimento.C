#include "FCtools.h"
#include "FCmatrixFull.h"
#include "Spline3Interpolator.h"
#include "TF1.h"
#include "Integrator.h"
#include <iostream>
#include "TRandom3.h"

using namespace std;

Spline3Interpolator Interpol;
double finvert(double *x, double *par);
double fmultiply(double *x, double *par);
double SecantFindRoots(double x_1, double x_0, TF1 func, double eps);

int main() {
	FCtools reader;

	FCmatrixFull M(reader.ReadFileToMatrix("txt/corpo_velocidade.data"));

	int size = M.GetCol(1).size();
	double Vx [size];
	double x [size];

	M.GetCol(0).Print();
	M.GetCol(1).Print();

	for (int i = 0; i < size; ++i) {
		Vx[i] = M.GetCol(1)[i]; // cout << Vx[i] << " ";
		x[i] = M.GetCol(0)[i];  // cout << x[i] << endl;
	}

	Interpol.SetDataPoints(size, x, Vx);

	// Interpol.Draw();

	double vel = Interpol.Interpolate(14.5);
	cout << "Velocity at 14.5Km = " << vel << endl;

	double xmaxvel = SecantFindRoots(10, 10.5, Interpol.GetDerivativeInterpolationFunction(), 1e-10);
	cout << "Max Velocity position = " << xmaxvel << endl;

	// //problema para valores proximos de zero:  dt = dx/dVx
	// TF1 inverse("inverse", finvert, x[0], x[size], 0);
	// Integrator integ(0.001, xmaxvel, inverse);

	// double time, error;
	// integ.SimpsonRule(1000, time, error);
	// cout << "Time for Velocity position = " << time << " +- " << error << endl;

	TRandom3 r(0);

	double avg = 0.;
	for (int i = 0; i < 100000; ++i)
		avg += Interpol.Interpolate(r.Rndm() * xmaxvel);
	avg /= 100000;

	double ttt = xmaxvel / avg;
	cout << "Time for Max Velocity position = " << ttt << "h" << endl;


	TF1 dVxVx("dVx.Vx", fmultiply, x[0], x[size], 0);
	Integrator integ2(0, 8, dVxVx);

	double potency, error2;
	integ2.SimpsonRule(1000, potency, error2);
	cout << "Potency from 0 to 8Km = " << potency << " +- " << error2 << "Kg.Km²/h²" << endl;

	return 0;
}

double finvert(double *x, double *par) {
	return 1. / Interpol.Interpolate(x[0]);
}

double fmultiply(double *x, double *par) {
	return Interpol.Interpolate(x[0]) * Interpol.InterpolateDerivative(x[0]);
}

double SecantFindRoots(double x_1, double x_0, TF1 func, double eps)
{
	double x_n = x_1;
	double x_n1 = x_0;
	double x_n2 = x_0;
	int i;

	for(i = 0; i < 100; i++)
	{  
		x_n2 = x_n1;
		x_n1 = x_n1 - (func.Eval(x_n1)*(x_n1-x_n))/(func.Eval(x_n1)-func.Eval(x_n));

		x_n = x_n2;

	  //cout <<fprintf('x%d = %.20d \n',i,x_n1);

		if (fabs(x_n2-x_n1) <= eps)
			break;
	}

	if(i < 100)
	{
		cout << "Solution Found!  Iterations: " << i<< endl;
		return x_n;
	}
	else
	{
		cout << "Atention!!! Solution not found!!!   " << x_n << endl;
		return 0;
	}
}