#include "TFormula.h"
#include "TF1.h"
#include "ODEpoint.h"
#include "ODEsolver.h"
#include "ODEdrawer.h"
#include "ZeroFinder.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

ODEsolver solver;
double shoot(double* var, double* par);

int main() {
	double Target = 0.;
	double velocity = 200./3.6;
	double step = 0.01;
	double MaxTime = 100.;
	double b = 0.;
	double m = 100.;
	double g = 9.8;

	//t = x[0]; x = x[1]; vx = x[2]; y = x[3]; vy = x[4]
	//b = [0]; m = [1]; g = [2]
	vector<TFormula> v;
	v.push_back(TFormula("1","x[2]"));
	v.push_back(TFormula("2","-[0]/[1]*x[2]"));
	v.push_back(TFormula("3","x[4]"));
	v.push_back(TFormula("4","-[2]-[0]/[1]*x[4]"));

	double fpar[3] = {b, m, g};
	solver.SetODEfunc(v);
	solver.SetPar(fpar);

	TF1 target("target", shoot, 0, M_PI/2., 4);
	double rootspar[4] = {velocity, step, MaxTime, Target};
	target.SetParameters(rootspar);

	double dist = target.Eval(30.*M_PI/180.);
	cout << "Landing distance with a 30 degree angle: " << dist << " m\n" << endl;

	target.SetParameter(3,200);

	ZeroFinder z(target);
	double theta = z.Secant(5*M_PI/180., 10*M_PI/180., 0.0001);

	if (theta == 0) {
		cout << "\nMethod didn't converge!\n" << endl;
		return -1;
	}
	else
		cout << "\nWe got a hit! Theta = " << theta*180/M_PI << "º for the canon to reach 200 m.\n\n" << endl;

	ODEdrawer a;

	//t, x, vx, y, vy
	double ainit[] = {0, 0, velocity*cos(theta), 0, velocity*sin(theta)};
	ODEpoint ini(5, ainit);

	vector < vector<ODEpoint> > point;
	vector<ODEpoint> points = solver.RK4(ini, step, MaxTime);
	vector<ODEpoint> corrected;

	for (int i = 0; points[i][3] >= 0 && i < points.size(); ++i)
		corrected.push_back(points[i]);

	point.push_back(corrected);

	a.AddPad(point, 1, 3, "Canon Shooting;x (m); y (m)");
	a.Draw();

	return 0;
}

//if method fails return 0
//pars: [0] = |v0|; [1] = h; [2] = Tf; [3] = target;
//var: angle of shooting

double shoot(double* var, double* par)
{
	double ainit[] = {0, 0, par[0]*cos(var[0]), 0, par[0]*sin(var[0])};
	ODEpoint ini(5,ainit);
	vector<ODEpoint> points = solver.RK4(ini,par[1],par[2]);

	int i;

	for (i = 1; points[i][3] > 0 && i < points.size()-1; ++i);
		// points[i].Print(10,10);

	if(points[i][3] > 0)
	{
		cout << "Method did not converge, please add more time, returning NaN.\n" << endl;
		return std::numeric_limits<double>::quiet_NaN();
	}
	else
	{
		// cout << "teta: " << var[0] << " distance from target: " << points[i-1][1] - par[3] << endl;
		return points[i-1][1] - par[3];
	}
}