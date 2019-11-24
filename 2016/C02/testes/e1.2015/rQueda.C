#include "ODEsolver.h"
#include "ODEdrawer.h"
#include "ZeroFinder.h"
#include "TF1.h"
#include "Spline3Interpolator.h"
#include "Func1D.h"
#include <cmath>
#include <limits>

using namespace std;

int main()
{
	double b = 5;
	double m = 50;
	double g = 9.8;

	double step = 0.01;
	double MaxTime = 150;

	//t = x[0]; x = x[1]; vx = x[2]; y = x[3]; vy = x[4]
	//b = [0]; m = [1]; g = [2]

	//d^2x/dt^2 = -b/m*(vx)
	//d^2y/dt^2 = -g - b/m*(vy)

	vector<TFormula> v;
	v.push_back(TFormula("1","x[2]"));
	v.push_back(TFormula("2","-[0]/[1]*x[2]"));
	v.push_back(TFormula("3","x[4]"));
	v.push_back(TFormula("4","-[2]-[0]/[1]*x[4]"));

	double fpar[3] = {b,m,g};
	ODEsolver solver;
	solver.SetODEfunc(v);
	solver.SetPar(fpar);

	ODEpoint ini(5);
	ini[0] = 0;
	ini[1] = 0;
	ini[2] = 0;
	ini[3] = 10000;
	ini[4] = 0;

	vector<ODEpoint> points = solver.RK4(ini, step, MaxTime);
	vector<ODEpoint> velocity = points;

	for (int i = 0; i < points.size(); ++i)
		velocity[i][1] = sqrt(points[i][2]*points[i][2] + points[i][4]*points[i][4]); 

	ODEdrawer a;
	Spline3Interpolator v_t_spline(a.GetSpline(velocity, 0, 1));
	Func1D fvel(v_t_spline.GetInterpolationFunction());
	fvel.Draw("v(t);t;v","Prob3_vel.pdf");

	cout << "Terminal velocity: "<< fvel.Eval(120) << " m/s" << endl;

	Spline3Interpolator z_t_spline(a.GetSpline(velocity, 0, 3));
	Func1D fpos(z_t_spline.GetInterpolationFunction());
	fpos.Draw("z(t);t;z","Prob3_pos.pdf");

	double t = 0.;
	while(fpos.Eval(t)>0 && t<MaxTime)
		t+=step;

	if (t>MaxTime)
	{
		cout << "Did not hit the ground! It needs more time." << endl;
		return -1;
	}
	else
		cout << "Time to hit the ground: "<< t << " s" << endl;

	return 0;	
}