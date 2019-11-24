#include "Spline3Interpolator.h"
#include "NevilleInterpolator.h"
#include "NewtonInterpolator.h"
#include "LagrangeInterpolator.h"
#include "TF1.h"
#include "TMath.h"
#include "Func1D.h"
#include <cmath>

int main()
{
	int NMAX = 20;
	double fx[NMAX];
	double fy[NMAX];

	double x;
	int i;

	// for (i=0, x=0.; i < NMAX && x < 100.; i++, x += 30./NMAX)
	// {
	// 	fx[i]= x;
	// 	fy[i]= sin(x+0.0001) / (x+0.0001);
	// }

	// TF1 f("f1","sin(x+0.0001)/(x+0.0001)", 0, 15);

	// Spline3Interpolator Inter0(i,fx,fy,f);
	// Inter0.Draw();

	// LagrangeInterpolator Inter1(i,fx,fy,f);
	// Inter1.Draw();

	// NewtonInterpolator Inter2(i,fx,fy,f);
	// Inter2.Draw();

	// NevilleInterpolator Inter3(i,fx,fy,f);
	// Inter3.Draw();

	// Func1D deriv(Inter0.GetInterpolDerivative());
	// deriv.Draw();
	
	// Func1D integ(Inter0.GetInterpolPrimitive());
	// integ.Draw();

	//==============================

	// Inter0.SetDataPoints(i-5,fx,fy);
	// Inter0.Draw();

	// Inter1.SetDataPoints(i-6,fx,fy);
	// Inter1.Draw();

	// Inter2.SetDataPoints(i-7,fx,fy);
	// Inter2.Draw();

	// Inter3.SetDataPoints(i-8,fx,fy);
	// Inter3.Draw();
	
	//==============================

	// for (i=0, x=0.; i < NMAX && x < 50.; i++, x += 10./NMAX)
	// {
	// 	fx[i]= x;
	// 	fy[i]= cos(3*x) / (0.4 + (x-2.)*(x-2.));
	// }

	// TF1 f2("f2","cos(3*x)/(0.4+(x-2.)*(x-2.))", 0, 30);

	// Spline3Interpolator I0(i,fx,fy,f2);
	// I0.Draw();

	// LagrangeInterpolator I1(i,fx,fy,f2);
	// I1.Draw();

	// NewtonInterpolator I2(i,fx,fy,f2);
	// I2.Draw();

	// NevilleInterpolator I3(i,fx,fy,f2);
	// I3.Draw();

	// Func1D derivative(I0.GetInterpolDerivative());
	// derivative.Draw();

	//==============================

	int M = 30;
	double Fx[M];
	double Fy[M];

	for (i=0, x=0.; i < M && x < 50.; i++)
	{
		Fx[i]= x;
		Fy[i]= cos(3*x)/(0.4+(x-2.)*(x-2.));
		x += TMath::Pi()/8;
	}

	TF1 f3("f3","cos(3*x)/(0.4+(x-2)*(x-2))", 0, 100);

	Spline3Interpolator Iff(i,Fx,Fy,f3);
	Iff.Draw();
	Spline3Interpolator Igg(Iff);
	Igg.Draw();

	Func1D ffderiv(Igg.GetInterpolDerivative());
	ffderiv.Draw();
	
	Func1D ffinteg(Igg.GetInterpolPrimitive());
	ffinteg.Draw();

	cout << "A primitiva está claramente um nojo. Falta impor condições de fronteira." << endl;
	cout << "A derivada não funciona sempre também pela falta de condições de fronteira." << endl;

	return 0;
}